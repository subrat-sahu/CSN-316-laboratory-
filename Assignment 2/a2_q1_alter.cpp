#include <bits/stdc++.h>
using namespace std;

int main (int argc, char * argv[]) {
  string first = "";
  cin>>first;
  if(first.length()-1 >= stoi(argv[1])){
   char i= first[stoi(argv[1])];
if(i == '0') {
first[stoi(argv[1])] = '1';

}
else {
first[stoi(argv[1])] = '0';
}
  }else {
cout<<"error";
return 0;
}
  string sec = "",output = "";
  cin>>sec;
cout<<first<<endl;
cout<<sec<<endl;
  return 0;
}
