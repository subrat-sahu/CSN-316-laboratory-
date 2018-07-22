
#include <iostream>
#include  <sys/types.h>
using namespace std;

int  main()
{
     pid_t  pid;

     fork();
     pid = getpid();
	cout << pid << endl;
	cout << "yo";
}
