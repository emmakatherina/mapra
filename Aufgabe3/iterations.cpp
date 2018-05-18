// solve.cpp
// By Jaqueline Reuter and Emma Ahrens
// May 2018

#include "matrix.h"
#include "vektor.h"
#include "unit.h"
#include <vector>
#include <string>
#include <fstream>

#define NDEBUG

using std::vector;

double Residuum (Vektor x, Vektor b, Matrix A) {
    return (A*x - b).Norm2() / b.Norm2();
}

void Jacobi (Vektor &x0, Vektor b, Matrix A, int &Iterationen, int maxiter, double tol, vector<double> &res) {
	res.resize(0);
    Iterationen = 0;
    double r = Residuum(x0, b, A);
	res.push_back(r);
    Vektor x (x0.Laenge());
    
    while ((Iterationen < maxiter) && (r >= tol)) { //TODO Ohne Residuum?
        for (size_t i = 0; i < x0.Laenge(); i++){
            x(i) = (1/A(i,i)) * (b(i) - dot(A.Zeile(i), x0) + A(i,i)*x0(i));
        }
        x0 = x;
        Iterationen++;
        r = Residuum(x0, b, A);
		res.push_back(r);
    }
}

void GS (Vektor &x0, Vektor b, Matrix A, int &Iterationen, int maxiter, double tol, vector<double> &res) {
	res.resize(0);
	Iterationen = 0;
	double r = Residuum(x0, b, A);
	res.push_back(r);
	Vektor x (x0.Laenge());

	while ((Iterationen < maxiter) && (r >= tol)) { //TODO Ohne Residuum?
		for (size_t i = 0; i < x0.Laenge(); i++) {
			double first = 0, second = 0;

			for (size_t j = 0; j < i; j++) {
				first += A(i,j)*x(j);
			}

			for (size_t j = i+1; j < x0.Laenge(); j++) {
				second += A(i,j)*x0(j);
			}

			x(i) = (1/A(i,i)) * (b(i) - first - second);
		}

		x0 = x;
		Iterationen++;
		r = Residuum(x0, b, A);
		res.push_back(r);
	}
}

void CG (Vektor &x0, Vektor b, Matrix A, int &Iterationen, int maxiter, double tol, vector<double> &res) {
	res.resize(0);
	Iterationen = 0;
	Vektor r0 = b - A*x0;
	Vektor p0 = r0;
	double gamma0 = dot(r0, r0);
	double residuum = r0.Norm2() / b.Norm2();
	res.push_back(residuum);

	while ((Iterationen < maxiter) && (residuum > tol)) {
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
		residuum = r0.Norm2() / b.Norm2();
		res.push_back(residuum);
	}
}

void WriteResiduum(vector<double> res, const char * filename) {
	std::ofstream ofs (filename);
	for (size_t i = 0; i < res.size(); i++) {
		ofs << res[i] << "\n";
	}
	ofs.close();
}

int main (int argc, char * argv[]) {
	Matrix A;
	Vektor x0, b;
	double tol = 0.5;
	int maxiter = 10;
	int Iterationen = 0;

	vector<double> res (0);

	int Beispiel = 1;
	if (argc > 1)
		Beispiel = ((int) argv[1][0]) - 48;

	Start(Beispiel, A, x0, b, tol, maxiter);
	Jacobi(x0, b, A, Iterationen, maxiter, tol, res);
	WriteResiduum(res, "Jacobi.txt");
	Ergebnis(x0, Iterationen, 0);

	Start(Beispiel, A, x0, b, tol, maxiter);
	GS(x0, b, A, Iterationen, maxiter, tol, res);
	WriteResiduum(res, "GS.txt");
	Ergebnis(x0, Iterationen, 1);

	Start(Beispiel, A, x0, b, tol, maxiter);
	CG(x0, b, A, Iterationen, maxiter, tol, res);
	WriteResiduum(res, "CG.txt");
	Ergebnis(x0, Iterationen, 2);

    return 0;
}
