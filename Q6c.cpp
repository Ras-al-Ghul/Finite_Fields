#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define MAX5 6
#define ALPHASIZE 5
#define FTWOSIZE 243
#define MAXSIZE 20

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

void multiply(int mul1[], int mul2[], int m, int n,int prod[], int &proddeg, int p)
{
   //int *prod = new int[m+n-1];

   // Initialize the porduct polynomial
   int i;
   int A[MAXSIZE],B[MAXSIZE];

   for(i = 0;i < m; i++)
        A[i] = mul1[i];
   for(i = 0;i < n; i++)
        B[i] = mul2[i];

   for (i = 0; i<m+n-1; i++)
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

    proddeg = m+n-1;

   return;
}

void polynomialdiv(int arrg[],int &degk,int arrh[],int degl,int p){

    int i,j;

    int arrq[MAX5],arrr[MAX5];

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
        arrr[i] = mod(arrr[i], p);

    int degquo = degk - degl + 1;
    int degrem = (degl - 2 + 1);

    degk = degrem;
    for(i=0; i<degrem; i++)
        arrg[i] = arrr[i];

    return;
}

int main(int argc, char *argv[]){
    int arrfield[FTWOSIZE][MAX5-1];
    int irrred[MAX5],tempirrred[MAX5],i,j,k,l,m,n,counts,flag,auxflag = 0,chkcount = 0;
    int gencan[ALPHASIZE];
    int prod[MAXSIZE],proddeg;
    srand(time(NULL));

    cout<<"To find three pairs of distinct polynomials and their inverses from F2"<<endl;
    cout<<"The prime number p is 3 and r value is 5"<<endl;
    cout<<"Enter the coefficients of the irreducible polynomial you get from case 2 of Q6a starting from the lowest degree term"<<endl;
    cout<<"Eg: input 1 2 1 0 1 2 for 1 + 2x + x^2 + x^4 + 2x^5 Press enter after entering each coefficient"<<endl;
    for(i=0; i<MAX5; i++){
        cin>>irrred[i];
        tempirrred[i] = irrred[i];
    }

    n=0;
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            for(k=0; k<3; k++)
                for(l=0; l<3; l++)
                    for(m=0; m<3; m++){
                        arrfield[n][0] = m;arrfield[n][1] = l;arrfield[n][2] = k;arrfield[n][3] = j;arrfield[n][4] = i;
                        n++;
                    }

    for(counts=0; counts<3; counts++){

        while(1){
            for(i=0; i<ALPHASIZE; i++)
                gencan[i] = rand()%3;
            if(!((gencan[0] == 0 || gencan[0] == 1) && (gencan[1] == 0 && gencan[2] == 0 && gencan[3] == 0 && gencan[4] == 0)))
                break;
        }

        cout<<endl<<"The chosen polynomial is "<<endl;
        cout<<gencan[4]<<"x^4 + "<<gencan[3]<<"x^3 + "<<gencan[2]<<"x^2 + "<<gencan[1]<<"x + "<<gencan[0]<<endl;

        flag = 1;

        for(i=0; i<FTWOSIZE; i++){
            flag = 1;
            int temparrfield[MAX5 - 1];
            for(k = 0; k<MAX5 - 1; k++)
                temparrfield[k] = arrfield[i][k];
            multiply(gencan,temparrfield,5,5,prod,proddeg,3);

            for(j=0; j<MAX5; j++)
                tempirrred[j] = irrred[j];

            polynomialdiv(prod,proddeg,tempirrred,6,3);

            for(j=0; j<proddeg; j++){
                if(j == 0)
                    if(prod[j] == 1){
                        continue;
                    }
                    else{
                        flag = 0;
                        break;
                    }
                else
                    if(prod[j] == 0){
                        continue;
                    }
                    else{
                        flag = 0;
                        break;
                    }
            }
            if(flag == 1){
                break;
            }
        }
        cout<<endl<<"The inverse of the chosen polynomial is "<<endl;
        cout<<arrfield[i][4]<<"x^4 + "<<arrfield[i][3]<<"x^3 + "<<arrfield[i][2]<<"x^2 + "<<arrfield[i][1]<<"x + "<<arrfield[i][0]<<endl;

    }

    return 0;
}
