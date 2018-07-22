#include<iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

/* main
 * params : argc ( No. of command line arguments )
 * argv[] : array of strings ( arguments )
 */
int main(int argc, char *argv[]) {
   cout << "No. of arguments : " << argc << endl;
	int a = std::atoi(argv[1]);
	int b = std::atoi(argv[3]);
	string op = argv[2]; 
	cout << a << " " << b << endl;
   int i;
   for ( i = 0; i < argc; i++ ) {
      cout << "argv[" << i << "] = " << argv[i] << endl;
   }
	//switch(argv[2]){
	//	case '-' return 
	
	//}
	double c;
	if(op == "+") c = a+b;
	else if(op == "-") c = a-b;
	else if(op == "/") c = (a/b);
	else if(op == "*") c = a*b;
	cout << "RESULT: " << c << endl;
   return 0;
}
