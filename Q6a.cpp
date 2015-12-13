#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define MAX3 4
#define MAX5 6

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

int polynomialdiv(int arrg[],int degk,int arrh[],int degl,int p){
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

    for(i=0; i<degrem; i++){
        if(arrr[i] != 0)
            return 1;
    }
    return 0;
}

int main(int argc, char *argv[]){
    int i,j,k,l,m,n,flag,counts=0;
    srand(time(NULL));
    cout<<"Roll number 201503003, so prime p is 3"<<endl;
    cout<<"r is case 1: 3 and case 2: 5"<<endl;
    cout<<"Have to find finite field of order case 1: 3^3 = 27 elements and case 2: 3^5 = 243 elements"<<endl<<endl;

    cout<<"Answer of case 1"<<endl;
    cout<<"Z sub p is {0, 1, 2} in this case"<<endl;
    cout<<"The finite field F of order 27 : (Z sub 3[X])/<f(x)> = { g(x) + <f(x)> | deg (g(x)) <= 2 } . Here g(x) belongs to 'Z sub 3[X]' and is of the\
    form ax^2 + bx + c where a,b,c come from {0, 1, 2} and F contains all possible permutations of a,b,c"<<endl;
    cout<<"Now we have to find f(x) which is an irreducible polynomial  belonging to Z sub 3[X] and of degree 3"<<endl;

    int irredp3[MAX3],polynomialeval;

    while(1){
        for(i=0; i<MAX3; i++){
            if(i==(MAX3-1))
                while((irredp3[i] = rand() % 3) == 0);
            else
                irredp3[i] = rand() % 3;
        }

        flag = 1;
        for(i=0; i<3; i++){//Try all values of x in 0,1,2
            polynomialeval = 0;
            for(j=0; j<MAX3; j++){
                polynomialeval += (irredp3[j] * (int)pow(i,j));//coeff * (i^j)
            }
            if(mod(polynomialeval,3) == 0){
                flag = 0;
                break;
            }
        }
        if(flag == 1){
            cout<<"The polynomial f(x) is"<<endl;
            for(i=0; i<MAX3; i++)
                if(i == MAX3-1)
                    cout<<irredp3[i]<<"x^"<<i<<endl;
                else if(i == 0)
                    cout<<irredp3[i]<<" + ";
                else
                    cout<<irredp3[i]<<"x^"<<i<<" + ";
            cout<<endl;

            counts++;
            if(counts == 1)
                break;
            else
                continue;
        }
    }

    cout<<endl;
    cout<<"Answer of case 2"<<endl;
    cout<<"Z sub p is {0, 1, 2, 3, 4} in this case"<<endl;
    cout<<"The finite field F of order 243 : (Z sub 5[X])/<f(x)> = { g(x) + <f(x)> | deg (g(x)) <= 4 } . Here g(x) belongs to 'Z sub 5[X]' and is of the \
    form ax^4 + bx^3 + cx^2 + dx + e where a,b,c,d,e come from {0, 1, 2, 3, 4} and F contains all possible permutations of a,b,c,d,e"<<endl;
    cout<<"Now we have to find f(x) is an irreducible polynomial  belonging to Z sub 5[X] and of degree 5"<<endl;

    counts = 0;
    int irredp5[MAX5],divisorp[MAX5],tempirredp5[MAX5];
    while(1){
        for(i=0; i<MAX5; i++){
            if(i==(MAX5-1))
                while((irredp5[i] = rand() % 3) == 0);
            else
                irredp5[i] = rand() % 3;
        }
        flag = 1;
        //degree 1 polynomials
        for(i=0 ;i<5 ;i++){
            for(j=1; j<5 ;j++){
                divisorp[0] = i;divisorp[1] = j;
                for(k=0; k<MAX5; k++)
                    tempirredp5[k] = irredp5[k];

                int ans = polynomialdiv(tempirredp5,MAX5,divisorp,2,3);
                if(ans == 0)
                    flag = 0;
            }
        }
        //degree 2 polynomials
        for(i=0 ;i<5 ;i++){
            for(j=0; j<5 ;j++){
                for(k=1; k<5 ;k++){
                    divisorp[0] = i;divisorp[1] = j;divisorp[2] = k;
                    for(k=0; k<MAX5; k++)
                        tempirredp5[k] = irredp5[k];

                    int ans = polynomialdiv(tempirredp5,MAX5,divisorp,3,3);
                    if(ans == 0)
                        flag = 0;
                }
            }
        }

        //Printing
        if(flag == 1){
            cout<<"The polynomial f(x) is"<<endl;
            for(i=0; i<MAX5; i++)
                if(i == MAX5-1)
                    cout<<irredp5[i]<<"x^"<<i<<endl;
                else if(i == 0)
                    cout<<irredp5[i]<<" + ";
                else
                    cout<<irredp5[i]<<"x^"<<i<<" + ";

            cout<<endl;

            counts++;
            if(counts == 1)
                break;
            else
                continue;
        }
    }

    int ans;
    cout<<endl<<"Enter 1 if you want to see the complete set g(x) else enter 0"<<endl;
    cin>>ans;
    if(ans == 0)
        return 0;
    else{
        cout<<"Showing all 27 polynomials from Z sub 3"<<endl;
        for(i=0; i<3; i++)
            for(j=0; j<3; j++)
                for(k=0; k<3; k++)
                    cout<<i<<"x^0 + "<<j<<"x^1 + "<<k<<"x^2"<<endl;

        cout<<endl<<"Showing all 243 polynomials from z sub 3"<<endl;
        for(i=0; i<3; i++)
            for(j=0; j<3; j++)
                for(k=0; k<3; k++)
                    for(l=0; l<3; l++)
                        for(m=0; m<3; m++)
                                cout<<i<<"x^0 + "<<j<<"x^1 + "<<k<<"x^2 + "<<l<<"x^3 + "<<m<<"x^4"<<endl;
    }

    return 0;
}
