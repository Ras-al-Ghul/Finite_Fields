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
        if(( mod((tempinv * num), p)) == 1)
            return tempinv;
        else
            tempinv++;
    }
    return 0;
}


int polynomialdiv(int arrg[],int degk,int arrh[],int degl,int arrr[],int p){
    int i,j;

    int t = findinverse(arrh[degl-1],p);

    int arrq[MAXDEG];
    for(i=0; i<degk; i++){
        arrr[i] = arrg[i];
    }
    for(i=degk - degl; i>=0; i--){
        arrq[i] = t*arrr[i+degl-1];
        for(j=0; j<degl; j++)
            arrr[i+j] = arrr[i+j] - (arrq[i] * arrh[j]);
    }

    for(i=0; i<=(degl - 2); i++)
        arrr[i] = mod(arrr[i], p);

    return (degl - 2 + 1);
}

int main(int argc,char *argv[]){
    int degg,degh,p,i,j;
    cout<<"Enter value of p in Z sub p where p is prime"<<endl;
    cin>>p;
    cout<<"Enter the degrees of the two polynomials with the degree of the first polynomial being >= degree of the second and second polynomial not zero"<<endl;
    cin>>degg>>degh;
    degg++;
    degh++;

    int arrg[MAXDEG],arrh[MAXDEG];
    cout<<"Enter the coefficients of the first polynomial starting from lowest degree term (ie the constant term) and coefficients coming from Z sub p"<<endl;
    for(i=0; i<degg; i++)
        cin>>arrg[i];
    cout<<"Enter the coefficients of the second polynomial starting from lowest degree term (ie the constant term) and coefficients coming from Z sub p"<<endl;
    for(i=0; i<degh; i++)
        cin>>arrh[i];

    cout<<"The entered polynomials are"<<endl;
    for(i=0; i<degg; i++)
        if(i == degg-1)
            cout<<arrg[i]<<"x^"<<i<<endl;
        else if(i == 0)
            cout<<arrg[i]<<" + ";
        else
            cout<<arrg[i]<<"x^"<<i<<" + ";

    for(i=0; i<degh; i++)
        if(i == degh-1)
            cout<<arrh[i]<<"x^"<<i<<endl;
        else if(i == 0)
            cout<<arrh[i]<<" + ";
        else
            cout<<arrh[i]<<"x^"<<i<<" + ";

    int rdoubledash[MAXDEG], degrdoubledash=0;
    int old;
    while((arrh[0]%p) != 0){
        old = arrh[0]%p;
        degrdoubledash=polynomialdiv(arrg,degg,arrh,degh,rdoubledash,p);
        for(i=0; i<degh; i++)
            arrg[i] = arrh[i];
        degg = degh;
        for(i=0; i<degrdoubledash; i++)
            arrh[i] = rdoubledash[i];
        degh = degrdoubledash;
        if(old == (arrh[0]%p)){
            //cout<<"Not terminating"<<arrh[0]%p<<endl;
            cout<<"The gcd is 1"<<endl;
            exit(EXIT_FAILURE);
        }
    }

    int temp = findinverse(arrg[degg - 1],p);
    for(i=0; i<degg; i++){
        arrg[i] = arrg[i]*temp;
        arrg[i] = mod(arrg[i], p);
    }

    cout<<"The gcd is"<<endl;
    for(i=0; i<degg; i++)
        if(i == degg-1)
            cout<<arrg[i]<<"x^"<<i<<endl;
        else if(i == 0)
            cout<<arrg[i]<<" + ";
        else
            cout<<arrg[i]<<"x^"<<i<<" + ";

    return 0;
}
