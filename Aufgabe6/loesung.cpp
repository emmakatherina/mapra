//By Jaqueline Reuter and Emma Ahrens
#include <iostream>
#include <cmath>
#include <cstdlib>

using std::cout, std::endl;

typedef double (*function)(double);

double f1(double x) {
    return pow(exp(1.),(-x*x));
}

double f2(double x) {
    return pow(log(x),2);
}

double f4(double x) {
    return 1./x;
}

double f5(double x) {
    return 1./(1 + x*x);
}

double mittelpunktsregel(function f, double a, double b) {
    return (b-a)*f((a+b)/2);
}

double trapezregel(function f, double a, double b) {
    return (b-a)*(0.5*f(a) + 0.5*f(b));
}

double simpsonregel(function f, double a, double b) {
    return (b-a)*((1./6)*f(a) + (2./3)*f((a+b)/2) + (1./6)*f(b));
}

double integrate(function f, double a, double b, double epsilon) {
    cout << mittelpunktsregel(f, a, b) << " - " << trapezregel(f, a, b) << " = " <<
        mittelpunktsregel(f, a, b) - trapezregel(f, a, b) << endl;
    if (abs(mittelpunktsregel(f, a, b) - trapezregel(f, a, b)) > epsilon) {
        return integrate(f, a, (a+b)/2, epsilon/2) + integrate(f, (a+b)/2, b, epsilon/2);
    } else {
        return simpsonregel(f, a, b);
    }
}
    
int main() {
    int Bsp;
	cout << "Berechne Integral von Beispiel: ";
    std::cin >> Bsp;

    double a = 0.01, b = 10., epsilon = 1e-10;
    //Start(Bsp, a, b, epsilon);

    double integral = integrate(f2, a, b, epsilon);
    cout << "Integral: " << integral << endl;

    //Ergebnis(integral);
	return 0;
}
