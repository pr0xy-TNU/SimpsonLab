/** lab1
//  setw(9) - dlina polya
//  setprwcision(3) - kol-vo znakov posle zapyatoi
**/
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <string.h>
#include <iomanip>

using namespace std;

double f(double x)
{
  //return 1;
  return cos(x);
  //return x;
}

double ff(double x){return x*x*x*x;}

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
    cout << "n = " << n << endl;
    return S;
}



int main()
{
    cout << setiosflags(ios::uppercase);
    setlocale(LC_ALL, "Russian");

    double A2[2] = {0.853553, 0.146447};
    double A3[3] = {0.711093, 0.278518, 0.0103893};
    double A4[4] = {0.603154, 0.357419, 0.0388879, 0.000539295};
    double A5[5] = {0.521756, 0.398667, 0.0759424, 0.00361176, 0.00002337};

    double X2[2] = {0.585786, 3.414214};
    double X3[3] = {0.415775, 2.294280, 6.289945};
    double X4[4] = {0.322548, 1.745761, 4.536620, 9.395071};
    double X5[5] = {0.263560, 1.413403, 3.596426, 7.085810, 12.640801};

    double res2 = 0, res3 = 0, res4 = 0, res5 =0;

    //vichislenie besk integrala s pomosh koeff Lagerra
    cout << "------------------------------------------" << endl;
    cout << "\n  n = 2" << endl;

    for(int k = 0; k < 2; k++){res2 += f(X2[k])*A2[k];}
    cout << setprecision(9) << res2 << endl;

    cout << "------------------------------------------" << endl;
    cout << "\n  n = 3" << endl;

    for(int k = 0; k < 3; k++){res3 += f(X3[k])*A3[k];}
    cout << setprecision(9) << res3 << endl;

    cout << "------------------------------------------" << endl;
    cout << "\n  n = 4" << endl;

    for(int k = 0; k < 4; k++){res4 += f(X4[k])*A4[k];}
    cout << setprecision(9) << res4 << endl;

    cout << "------------------------------------------" << endl;
    cout << "\n  n = 5" << endl;

    for(int k = 0; k < 5; k++){res5 += f(X5[k])*A5[k];}

    cout << setprecision(9) << res5 << endl;
    cout << "------------------------------------------" << endl;

    //cout << "Proverochnaya Formula Simpsona" << endl;
    double EPS = 1e-7;
    double a = 0.0, b = 1.0;
    double S;

    //S = Simpson(a,b,EPS);
    //cout << "S = " << S << endl;
    //cout << "------------------------------------------" << endl;

    //vichislim beskonechnii integral s pom v-li Simpsona
    cout << "\nPromezhetochie viachisleniya f-li Simpsona\n\n";
    double I = 0.0;
    do{
        S = Simpson(a,b,EPS);
        I += S;
        a = b; b += 1.0;
        cout << "I = " << I << ";    b = " << b << endl;
    }while(fabs(S) < EPS);

    cout << "\n\nAnswer--------------------------------------" << endl;
    cout << "I = " << I << endl;
    cout << "b = " << b << "   (A)" << endl;
    return 0;
}
