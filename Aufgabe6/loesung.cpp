//By Jaqueline Reuter and Emma Ahrens
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>

using std::cout, std::endl;

typedef double (*function)(double);

class FunctionWrapper {
    private:
        function f;
        std::map<double, double> map;

    public:
        FunctionWrapper(function f) {
            this->f = f;
        }

        double operator() (double x) {
            std::map<double, double>::iterator it;
            it = map.find(x);
            if (it != map.end()) {
                return it->second;
            } else {
                double y = f(x);
                map.insert( std::pair<double, double>(x,y) );
                return y;
            }
        }

        int calculatedValues() {
            return map.size();
        }
};

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

double mittelpunktsregel(FunctionWrapper& f, double a, double b) {
    return (b-a)*f((a+b)/2);
}

double trapezregel(FunctionWrapper& f, double a, double b) {
    return (b-a)*(0.5*f(a) + 0.5*f(b));
}

double simpsonregel(FunctionWrapper& f, double a, double b) {
    return (b-a)*((1./6)*f(a) + (2./3)*f((a+b)/2) + (1./6)*f(b));
}

double integrate(FunctionWrapper& f, double a, double b, double epsilon, int currentDepth, int & depth) {
    cout << mittelpunktsregel(f, a, b) << " - " << trapezregel(f, a, b) << " = " <<
        mittelpunktsregel(f, a, b) - trapezregel(f, a, b) << endl;
    if (abs(mittelpunktsregel(f, a, b) - trapezregel(f, a, b)) > epsilon) {
        currentDepth++;
        return integrate(f, a, (a+b)/2, epsilon/2, currentDepth, depth) + integrate(f, (a+b)/2, b, epsilon/2, currentDepth, depth);
    } else {
        if (depth < currentDepth)
            depth = currentDepth;
        return simpsonregel(f, a, b);
    }
}
    
int main() {
    int Bsp;
	cout << "Berechne Integral von Beispiel: ";
    std::cin >> Bsp;

    double a = 0.01, b = 10., epsilon = 1e-10;
    int depth = 0;
    //Start(Bsp, a, b, epsilon);

    FunctionWrapper wrapperf = FunctionWrapper(f1);
    double integral = integrate(wrapperf, a, b, epsilon, 0, depth);
    cout << "Integral: " << integral << endl << endl;

    cout << "Bei einer äquidistanten Verteilung müssen " << pow(2, depth) << " Funktionswerte übergeben werden, wohingegen bei einer adaptiven Zerlegung nur " << wrapperf.calculatedValues() << " Funktionswerte nötig sind." << endl;

    //Ergebnis(integral);
	return 0;
}
