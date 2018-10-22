#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in htonl INADDR_ANY 
#include <unistd.h> // read and write
#include <pthread.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_CLIENTS 10

int client_num=0;

struct client_data{
	int sockfd;
	string group_id;
	int cl_id;
	string name;
};

client_data *all_clients[MAX_CLIENTS];

unordered_map<string, vector<int>> cl_room;

int add_to_list(int fd, client_data* &data){
	for(int i=0; i<MAX_CLIENTS; i++){
		if(!all_clients[i]){
			client_data* cl = new client_data;
			cl->cl_id = i;
			cl->sockfd = fd;
			cl->group_id = "";
			cl->name = "";
			
			all_clients[i] = cl;
			data = cl;
			return 1;
		}
	}
	return 0;
}

void send_to_all(char* message, int id, string group){
	std::vector<int> list = cl_room[group];
	cout<<"Debug: Sending msg to clients: "<<list.size()<<endl;
	for(int i=0; i<list.size(); i++){
		if(list[i]!=id){
			char mess[100];
			strcpy(mess, all_clients[id]->name.c_str());
			mess[strlen(mess)-1] = '\0';
			strcat(mess, " : ");
			write(all_clients[list[i]]->sockfd, mess, strlen(mess));
			write(all_clients[list[i]]->sockfd, message, strlen(message));
		}
	}
}

void client_left(client_data *data){
	all_clients[data->cl_id] = NULL;
	vector<int> p = cl_room[data->group_id];
	auto it = find(p.begin(), p.end(), data->cl_id);
	p.erase(it);
	cl_room[data->group_id] = p;
	if(p.size()==0){
		cl_room.erase(data->group_id);
	}
}

void *client_handler(void *arg){
	client_data *new_client = (client_data*) arg;
	cout<<"Debug: Client thread created ID: "<<new_client->cl_id<<endl;
	
	char bufferin[1024];
	char bufferout[1024];
	char* message="Enter the room id";
	write(new_client->sockfd, message, strlen(message));
	
	int nbytes = read(new_client->sockfd, bufferin, 1023);
	bufferin[nbytes] = '\0';
	cout<<"Debug: Client sent: "<<bufferin<<endl;
	//////////////////////////////////////////////
	
	if(nbytes==0){
		cout<<"Debug: Client left"<<endl;
		client_left(new_client);
	}
	//////////////////////////////////////////////
	string group = bufferin;
	
	cout<<"Debug: Client entered group no: "<<group<<endl;
	
	if(cl_room.find(group)!=cl_room.end()){
		cl_room[group].push_back(new_client->cl_id);
	}
	else{
		vector<int> p{new_client->cl_id};
		cl_room[group] = p;
	}
	
	new_client->group_id = group;
	cout<<"Debug: Client group info updated."<<endl;
	
	message = "Enter your nickname";
	write(new_client->sockfd, message, strlen(message));
	nbytes = read(new_client->sockfd, bufferin, 1023);
	bufferin[nbytes] = '\0';

	//////////////////////////////////////////////
	if(nbytes==0){
		client_left(new_client);
	}	
	//////////////////////////////////////////////
	
	new_client->name = bufferin;
	cout<<"Debug: Client nickname info updated. "<<bufferin<<endl;
	
	message = "Welcome ";
	
	write(new_client->sockfd, message, strlen(message));
	message = bufferin;
	write(new_client->sockfd, message, strlen(message));
	
	while(1){
		nbytes = read(new_client->sockfd, bufferin, 1023);
		bufferin[nbytes] = '\0';
		cout<<bufferin<<endl;
		//////////////////////////////////////////////
		if(nbytes==0){
			client_left(new_client);
			break;
		}
		//////////////////////////////////////////////
		send_to_all(bufferin, new_client->cl_id, group);
	}
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	pthread_t tid;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000); 

	if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
		perror("Socket binding failed");
		return 1;
	}

	if(listen(listenfd, 10) < 0){
		perror("Socket listening failed");
		return 1;
	}

	for(int i=0; i<MAX_CLIENTS; i++){
		all_clients[i] = NULL;
	}

	while(1){
		sockaddr_in newsockaddr;
		socklen_t newsocklen = sizeof(newsockaddr);
		int newsockfd = accept(listenfd, (sockaddr *)&newsockaddr, &newsocklen);

		if(newsockfd<0){
			perror("Accept failed");
			return 1;
		}
		client_data *data=NULL;
		if(!add_to_list(newsockfd, data)){
			char* message = "Cannot accept conections: Client limit reached";
			int flag=write(newsockfd, message, strlen(message));
			if(flag<0){
				perror("Write failed");
				return 1;
			}
			continue;
		}
		cout<<"Debug: Socket added to list"<<endl;
		pthread_t tid;
		pthread_create(&tid, NULL, client_handler, (void*)data);
	}
	return 0;
}