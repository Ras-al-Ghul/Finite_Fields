#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc,char *argv[]){
    int a,b;
    cout<<"Enter two numbers greater than or equal to 0"<<endl;
    cin>>a>>b;
    int c;
    if(b > a)
        swap(a,b);
    while(b != 0){
        c = a % b;
        a = b;
        b = c;
    }
    cout<<"The GCD is "<<a<<endl;
    return 0;
}
