// solve.cpp
// By Jaqueline Reuter and Emma Ahrens
// May 2018

#include "matrix.h"
#include "vektor.h"
#include "unit.h"

double Residuum (Vektor x, Vektor b, Matrix A) {
    return (A*x - b).Norm2() / b.Norm2();
}

void Jacobi (Vektor &x0, Vektor b, Matrix A, int &Iterationen, int maxiter, double tol) {
    Iterationen = 0;
    double r = Residuum(x0, b, A);
    Vektor x (x0.Laenge());
    
    while ((Iterationen < maxiter) && (r >= tol)) { //TODO Ohne Residuum?
        for (int i = 0; i < x0.Laenge(); i++){
            x(i) = (1/A(i,i)) * (b(i) - dot(A.Zeile(i), x0) + A(i,i)*x0(i));
        }
        x0 = x;
        Iterationen++;
        r = Residuum(x0, b, A);
    }
}

void GS (Vektor &x0, Vektor b, Matrix A, int &Iterationen, int maxiter, double tol) {
	Iterationen = 0;
	double r = Residuum(x0, b, A);
	Vektor x (x0.Laenge());

	while ((Iterationen < maxiter) && (r >= tol)) { //TODO Ohne Residuum?
		for (int i = 0; i < x0.Laenge(); i++) {
			double first = 0, second = 0;

			for (int j = 0; j < i; j++) {
				first += A(i,j)*x(j);
			}

			for (int j = i+1; j < x0.Laenge(); j++) {
				second += A(i,j)*x0(j);
			}

			x(i) = (1/A(i,i)) * (b(i) - first - second);
		}

		x0 = x;
		Iterationen++;
		r = Residuum(x0, b, A);
	}
}

void CG (Vektor &x0, Vektor b, Matrix A, int &Iterationen, int maxiter, double tol) {
	Iterationen = 0;
	Vektor r0 = b - A*x0;
	Vektor p0 = r0;
	double gamma0 = dot(r0, r0);
	double res = r0.Norm2() / b.Norm2();

	while ((Iterationen < maxiter) && (res > tol)) {
		Vektor q = A*p0;
		double alpha = gamma0 / dot(q,p0);
		Vektor x = x0 + alpha*p0;
		Vektor r = r0 - alpha*q;
		double gamma = dot(r,r);
		Vektor p = r + (gamma/gamma0)*p0;

		r0 = r;
		p0 = p;
		x0 = x;
		gamma0 = gamma;

		Iterationen++;
		res = r0.Norm2() / b.Norm2();
	}
}

int main (int argc, char * argv[]) {
    for (int i = 1; i <= AnzahlBeispiele; i++) {
        Matrix A;
        Vektor x0, b;
        double tol = 0.5;
        int maxiter = 10;
        int Iterationen = 0;

        Start(i, A, x0, b, tol, maxiter);

		int Methode = 0;
		if (argc > 1)
			Methode = ((int) argv[1][0]) - 48;

        if (Methode == 0) {
			Jacobi(x0, b, A, Iterationen, maxiter, tol);
        }
        else if (Methode == 1) {
			GS(x0, b, A, Iterationen, maxiter, tol);
        }
        else if (Methode == 2) {
			CG(x0, b, A, Iterationen, maxiter, tol);
        }
        
        Ergebnis(x0, Iterationen, Methode);
    }

    return 0;
}
