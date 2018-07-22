#include "bits/stdc++.h"
#include "unistd.h"
using namespace std;

int main(){
	cout<<"pid "<<getpid()<<endl;fflush(stdout);
	for(int i =0;i<5;i++){
		int a = fork();
		if(a==0)cout<<"pid "<<getpid()<<endl;fflush(stdout);
	}
}
