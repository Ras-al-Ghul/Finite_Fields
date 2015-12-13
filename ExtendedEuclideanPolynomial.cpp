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

void polynomialdiv(int arrg[],int degk,int arrh[],int degl,int arrq[],int &degquo,int arrr[],int &degrem,int p){
    int i,j;

    int t = findinverse(arrh[degl-1],p);

    for(i=0; i<degk; i++){
        arrr[i] = arrg[i];
    }
    for(i=degk - degl; i>=0; i--){
        arrq[i] = t*arrr[i+degl-1];
        for(j=0; j<degl; j++)
            arrr[i+j] = arrr[i+j] - (arrq[i] * arrh[j]);
    }

    for(i=0; i<=(degk - degl); i++)
        arrq[i] = mod(arrq[i], p);

    for(i=0; i<=(degl - 2); i++)
        arrr[i] = mod(arrr[i], p); //arrr[i] % p;

    degquo = degk - degl + 1;
    degrem = (degl - 2 + 1);
    return;
}

void multiply(int A[], int B[], int m, int n,int prod[], int p)
{
   //int *prod = new int[m+n-1];

   // Initialize the porduct polynomial
   for (int i = 0; i<m+n-1; i++)
     prod[i] = 0;

   // Multiply two polynomials term by term

   // Take ever term of first polynomial
   for (int i=0; i<m; i++)
   {
     // Multiply the current term of first polynomial
     // with every term of second polynomial.
     for (int j=0; j<n; j++)
         prod[i+j] += A[i]*B[j];
   }

   for (int i = 0; i<m+n-1; i++)
     prod[i] = mod(prod[i], p);

   return;
}

int main(int argc,char *argv[]){
    int degg,degh,p,i,j;
    cout<<"Enter value of p in Z sub p where p is prime"<<endl;
    cin>>p;
    cout<<"Will not work if GCD is 1 - check it from previous program ie Euclidean algo for Polynomials"<<endl;
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

    int arroldolds[MAXDEG],arrolds[MAXDEG],arroldoldt[MAXDEG],arroldt[MAXDEG];
    int degoldolds = 1,degolds = 1,degoldoldt = 1,degoldt = 1;

    for(i=0; i<MAXDEG; i++){
        arroldolds[i] = 0;
        arroldoldt[i] = 0;
    }

    for(i=0;i<degoldolds;i++){
        arroldolds[0] = 1;
        arrolds[0] = 0;
        arroldoldt[0] = 0;
        arroldt[0] = 1;
    }

    int s[MAXDEG],t[MAXDEG],prod1[MAXDEG],prod2[MAXDEG];
    int degs=0,degt=0,degprod1=0,degprod2=0;

    int quo[MAXDEG],rem[MAXDEG],degquo = 0,degrem = 0;

    while((arrh[0]%p) != 0){
        polynomialdiv(arrg,degg,arrh,degh,quo,degquo,rem,degrem,p);

        for(i=0 ; i<degh; i++)
            arrg[i] = arrh[i];

        degg = degh;

        for(i=0; i<degrem; i++)
            arrh[i] = rem[i];

        degh = degrem;

        multiply(quo, arrolds, degquo, degolds, prod1, p);
        degprod1 = degquo + degolds - 1;
        multiply(quo, arroldt, degquo, degoldt, prod2, p);
        degprod2 = degquo + degoldt - 1;

        for(i=0; i<max(degoldolds,degprod1); i++)
            s[i] = arroldolds[i] - prod1[i];

        degs = max(degoldolds,degprod1);

        for(i=0; i<max(degoldoldt,degprod2); i++)
            t[i] = arroldoldt[i] - prod2[i];

        degt = max(degoldoldt,degprod2);

        for(i=0; i<MAXDEG; i++){
            arroldolds[i] = 0;
            arroldoldt[i] = 0;
            prod1[i] = 0;
            prod2[i] = 0;
        }

        for(i=0; i<degolds; i++)
            arroldolds[i] = arrolds[i];
        degoldolds = degolds;

        for(i=0; i<degoldt; i++)
            arroldoldt[i] = arroldt[i];
        degoldoldt = degoldt;

        for(i=0; i<degs; i++)
            arrolds[i] = s[i];
        degolds = degs;

        for(i=0; i<degt; i++)
            arroldt[i] = t[i];
        degoldt = degt;

    }

    int temp = findinverse(arrg[degg-1],p);

    for(i=0; i<degg; i++){
        arrg[i] = arrg[i]*temp;
        arrg[i] = mod(arrg[i], p);
    }

    for(i=0; i<degoldolds; i++){
        arroldolds[i] = arroldolds[i]*temp;
        arroldolds[i] = mod(arroldolds[i], p);
    }

    for(i=0; i<degoldoldt; i++){
        arroldoldt[i] = arroldoldt[i]*temp;
        arroldoldt[i] = mod(arroldoldt[i], p);
    }

    cout<<"d = gs + ht and d,s and t are"<<endl;
    for(i=0; i<degg; i++)
        if(i == degg-1)
            cout<<arrg[i]<<"x^"<<i<<endl;
        else if(i == 0)
            cout<<arrg[i]<<" + ";
        else
            cout<<arrg[i]<<"x^"<<i<<" + ";
    for(i=0; i<degoldolds; i++)
        if(i == degoldolds-1)
            cout<<arroldolds[i]<<"x^"<<i<<endl;
        else if(i == 0)
            cout<<arroldolds[i]<<" + ";
        else
            cout<<arroldolds[i]<<"x^"<<i<<" + ";
    for(i=0; i<degoldoldt; i++)
        if(i == degoldoldt-1)
            cout<<arroldoldt[i]<<"x^"<<i<<endl;
        else if(i == 0)
            cout<<arroldoldt[i]<<" + ";
        else
            cout<<arroldoldt[i]<<"x^"<<i<<" + ";

    return 0;
}
