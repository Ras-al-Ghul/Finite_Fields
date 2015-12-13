#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc,char *argv[]){
    int r,rdash;
    cout<<"Enter two numbers greater than or equal to 0"<<endl;
    cin>>r>>rdash;
    if(rdash > r)
        swap(r,rdash);
    cout<<"The entered numbers a and b are"<<endl;
    cout<<r<<" "<<rdash<<endl;
    int s = 1,sdash = 0,t = 0,tdash = 1;
    int q,rdoubledash,sdoubledash,tdoubledash;

    while(rdash != 0){
        q = r / rdash;
        rdoubledash = r % rdash;
        r = rdash;
        rdash = rdoubledash;
        sdoubledash = s - (sdash * q);
        tdoubledash = t - (tdash * q);
        s = sdash;
        t = tdash;
        sdash = sdoubledash;
        tdash = tdoubledash;
    }

    cout<<"The numbers r, s and t such that r = as + bt where r is GCD of a,b are "<<r<<", "<<s<<" and "<<t<<endl;
    return 0;
}
