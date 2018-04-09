/** lab1
//  setw(9) - dlina polya
//  setprecision(3) - kol-vo znakov posle zapyatoi
**/
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <string.h>
#include <iomanip>

using namespace std;

double lyambda = 0.5;
double xx;

double f(double u)
{
  if (u==0){return 1/(2*lyambda*lyambda);}
    else {
        double temp = 2*(sinh(u)+u*cosh(u))/(2*u+sinh(2*u));
        return temp*(1-cos(u/lyambda))*cos(u*xx/lyambda)/(u*u);}
}
double Simpson(double a, double b, double EPS)
{
    int n = 1;
    double S1, SP, S;
    double h, r;

    S1 = f(a) + f(b);
    S = (S1 + 4*f((a+b)/2.0)) / 6.0;

    do{
    SP = S;
    n = 2 * n;
    h = (b - a) / (2*n);
    S = S1;
    for(int i = 1; i < n; i++){ S += 4 * f(a+(2*i-1)*h) + 2 * f(a+2*i*h);}

    S = h * (S + 4 * f(b-h)) / 3.0;

    r = fabs(S-SP)/15.0;

    }while(r > EPS);
    //cout << "n = " << n << endl;
    return S;
}


int main()
{
    cout << setiosflags(ios::uppercase);
    setlocale(LC_ALL, "Russian");

    //cout << "Proverochnaya Formula Simpsona" << endl;
    double EPS = 1e-4;
    double a,b,I;
    double S;
    int i;

    /*S = Simpson1(a,b,EPS);
    cout << "S = " << S << endl;
    cout << "------------------------------------------" << endl;*/

    //vichislim beskonechnii integral s pom v-li Simpsona
    cout << "\nPromezhetochie viachisleniya f-li Simpsona\n\n" << endl;
    cout << "Pri lambda = " << lyambda << endl << endl;
    for (i = 0; i<15; i++)
    { xx = i*0.25; 
     I = 0.0;
     a = 0.0, b = 1.0;
     S = 1.0;
    while(fabs(S) > EPS){
        S = Simpson(a,b,EPS);
        I += S;
        //cout << "I = " << I << ";    b = " << b << endl;
        a = b; b += 1.0;
    }

    //cout << "\n\nAnswer--------------------------------------" << endl;
    cout <<"xx=  " << xx << "  I = " << I << "  b = " << b << endl;
    }
    return 0;
}

