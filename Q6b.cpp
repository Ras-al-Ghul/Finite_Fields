#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define MAX3 4
#define GENSIZE 3
#define FSTARSIZE 26
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

    int arrq[MAX3],arrr[MAX3];

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
    int arrfield[FSTARSIZE][MAX3];//0th entry is bool value
    int irrred[MAX3],i,j,k,l,counts,flag,tempirrred[MAX3],auxflag = 0,chkcount = 0;
    int gencan[GENSIZE];
    srand(time(NULL));

    cout<<"To find generator of multiplicative group F1* that is case 1 of Q6a"<<endl;
    cout<<"Enter the coefficients of the irreducible polynomial you get from case 1 of Q6a starting from the lowest degree term"<<endl;
    cout<<"Example 2 2 2 1 for 2 + 2x + 2x^2 + x^3"<<endl;
    for(i=0; i<MAX3; i++){
        cin>>irrred[i];
        tempirrred[i] = irrred[i];
    }

    l=0;
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            for(k=0; k<3; k++){
                arrfield[l][0] = 0;//done bool field
                arrfield[l][1] = i;arrfield[l][2] = j;arrfield[l][3] = k;
                l++;
            }

    int prod[MAXSIZE],proddeg = 0,tempprod[MAXSIZE], tempproddeg = proddeg;

    int maxcount = 0;

    while(1){
        //Generate gencan

        for(i=0; i<FSTARSIZE; i++){
            arrfield[i][0] = 0;
        }

        while(1){

            for(i=0; i<GENSIZE; i++){
                gencan[i] = rand()%3;
                //tempgencan[i] = gencan[i];
            }
            if(gencan[1] == 0 && gencan[2] == 0)
                continue;
            else
                break;
        }

        //Tick itself
        for(i=0; i<FSTARSIZE; i++){
            if(arrfield[i][1] == gencan[0] && arrfield[i][2] == gencan[1] && arrfield[i][3] == gencan[2]){
                    arrfield[i][0] = 1;
                    break;
            }
        }

        for(i=0; i<GENSIZE; i++)
            prod[i] = gencan[i];
        proddeg = GENSIZE;

        flag = 1;counts = 0;//Initialize counter
        while(1){
            if(counts == 0){
                counts++;
                continue;
            }
            multiply(gencan,prod,3,proddeg,prod,proddeg,3);

            for(i=0 ;i<proddeg; i++)
                tempprod[i] = prod[i];
            tempproddeg = proddeg;

            polynomialdiv(prod,proddeg,tempirrred,MAX3,3);

            for(i = 0; i<MAX3; i++)
                tempirrred[i] = irrred[i];

            for(i=0; i<FSTARSIZE; i++){
                if(arrfield[i][1] == prod[0] && arrfield[i][2] == prod[1] && arrfield[i][3] == prod[2]){
                    if(arrfield[i][0] == 1){
                        flag = 0;
                        //cout<<"here";
                        break;
                    }
                    else{
                        //cout<<counts<<" ";
                        arrfield[i][0] = 1;
                        counts++;
                        if(counts > maxcount){
                            maxcount = counts;
                            //cout<<maxcount;
                        }
                        //cout<<"here";
                        if(counts == FSTARSIZE){
                            flag = 1;
                            auxflag = 1;
                            break;
                        }
                    }
                }
            }
            if(flag == 0 || auxflag == 1)
                break;
        }
        if(flag == 1){
            //Print generator

            //cout<<maxcount;
            cout<<endl<<"The generator is"<<endl;
            cout<<gencan[2]<<"x^2 + "<<gencan[1]<<"x + "<<gencan[0]<<endl;

            chkcount++;
            maxcount = 0;
            auxflag = 0;
            if(chkcount == 1)
                break;
        }
    }

    return 0;
}
