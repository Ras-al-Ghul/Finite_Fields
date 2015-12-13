#include <iostream>
#include <cstdlib>

#define MAXDEG 20
using namespace std;

int mod (int a, int b)
{
   if(b < 0) //you can check for b == 0 separately and do what you want
     return mod(-a, -b);
   int ret = a % b;
   if(ret < 0)
     ret+=b;
   return ret;
}

int findinverse(int num, int p){
    int tempinv = 1;
    while(tempinv < p){
        if(mod((tempinv * num), p) == 1)
            return tempinv;
        else
            tempinv++;
    }
    return 0;
}

int main(int argc,char *argv[]){
    int degk,degl,p,i,j;
    cout<<"Enter value of p in Z sub p where p is prime"<<endl;
    cin>>p;
    cout<<"Enter the degrees of the two polynomials with the degree of the first polynomial being >= degree of the second"<<endl;
    cin>>degk>>degl;
    degk++;
    degl++;
    int arrg[MAXDEG],arrh[MAXDEG];
    cout<<"Enter the coefficients of the first polynomial starting from lowest degree term (ie the constant term) and coefficients coming from Z sub p"<<endl;
    for(i=0; i<degk; i++)
        cin>>arrg[i];
    cout<<"Enter the coefficients of the second polynomial starting from lowest degree term (ie the constant term) and coefficients coming from Z sub p"<<endl;
    for(i=0; i<degl; i++)
        cin>>arrh[i];

    cout<<"The entered polynomials are"<<endl;
    for(i=0; i<degk; i++)
        if(i == degk-1)
            cout<<arrg[i]<<"x^"<<i<<endl;
        else if(i == 0)
            cout<<arrg[i]<<" + ";
        else
            cout<<arrg[i]<<"x^"<<i<<" + ";

    for(i=0; i<degl; i++)
        if(i == degl-1)
            cout<<arrh[i]<<"x^"<<i<<endl;
        else if(i == 0)
            cout<<arrh[i]<<" + ";
        else
            cout<<arrh[i]<<"x^"<<i<<" + ";

    int t = findinverse(arrh[degl-1],p);
    //cout<<"The inverse of "<<arrh[degl-1]<<" in Z sub "<<p<<" is "<<t<<endl;

    int arrr[MAXDEG],arrq[MAXDEG];
    for(i=0; i<degk; i++){
        arrr[i] = arrg[i];
    }
    for(i=degk - degl; i>=0; i--){
        arrq[i] = t*arrr[i+degl-1];
        for(j=0; j<degl; j++)
            arrr[i+j] = arrr[i+j] - (arrq[i] * arrh[j]);
    }

    cout<<"The polynomials q,r such that g = hq + r are"<<endl;

    for(i=0; i<=(degk - degl); i++)
        arrq[i] = mod(arrq[i], p);

    for(i=0; i<=(degl - 2); i++)
        arrr[i] = mod(arrr[i], p);

    for(i=0; i<=(degk - degl); i++)
        if(i == (degk-degl))
            cout<<arrq[i]<<"x^"<<i<<endl;
        else if(i == 0)
            cout<<arrq[i]<<" + ";
        else
            cout<<arrq[i]<<"x^"<<i<<" + ";

    for(i=0; i<=(degl - 2); i++)
        if(i == degl-2)
            cout<<arrr[i]<<"x^"<<i<<endl;
        else if(i == 0)
            cout<<arrr[i]<<" + ";
        else
            cout<<arrr[i]<<"x^"<<i<<" + ";


    return 0;
}
