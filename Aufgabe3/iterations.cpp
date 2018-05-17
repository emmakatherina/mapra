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
    
    while ((Iterationen <= maxiter) && (r >= tol)) {
        for (int i = 0; i < x0.Laenge(); i++){
            x(i) = (1/A(i,i)) * (b(i) - dot(A.Zeile(i), x0) + A(i,i)*x0(i));
        }
        x0 = x;
        Iterationen++;
        r = Residuum(x0, b, A);
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

        if (argc > 0) {
            if (argv[1] == "0") {
                //Jacobi    
                std::cout << "Jacobi";
            }
            else if (argv[1] == "1"){
                //GS
                std::cout << "GS";
            }
            else if (argv[1] == "2") {
                //CG
                std::cout << "CG";
            }
        }
        
        Ergebnis(x0, Iterationen, ((int) argv[1][0]));
    }

    return 0;
}
