//
//  matrix.cpp
//  
//
//  By jaqueline Reuter and Emma Ahrens
//

#include "matrix.h"
#include <iomanip>

// std::vektor<Vektor> Matx;

// ----- Konstruktor -----
Matrix::Matrix(size_t hoehe, size_t breite) {
#ifndef NDEBUG
  if ((hoehe <= 0) && (breite <= 0))
    MatFehler("Nur Matrizen mit positiver Laenge und Breite!");
#endif

    Vektor dummy (1);
    (*this).Matx.resize(breite, dummy);
    for (size_t i = 0; i < Spalten(); i++) {
        Matx[i].ReDim(hoehe);
    }
    
    this->ReDim(hoehe, breite);
}

Matrix::Matrix(const Matrix& M) : Matx(M.Matx) {
    for (int i = 0; i < Zeilen(); i++) {
        for (int j = 0; j < Spalten(); j++) {
            (*this)(i,j) = M(i,j);
        }
    }
}

// ----- Schreib- und Lesezugriff auf Vektorelemente -----

double& Matrix::operator () (size_t vert, size_t horiz) {
#ifndef NDEBUG
    if (vert >= (*this).Zeilen())
        MatFehler("Ungueltiger Index!");
    if (horiz >= (*this).Spalten())
        MatFehler("Ungueltiger Index!");
#endif

  return (*this).Matx[horiz](vert);
}
  
double Matrix::operator () (size_t vert, size_t horiz) const {
#ifndef NDEBUG
    if (vert >= Zeilen())
        MatFehler("Ungueltiger Index!");
    if (horiz >= (*this).Spalten())
        MatFehler("Ungueltiger Index!");
#endif

  return (*this).Matx[horiz](vert);
}

// ------ Zuweisung -------
Matrix& Matrix::operator = (const Matrix& M) {
#ifndef NDEBUG
    if ((Zeilen() != M.Zeilen()) || (Spalten() != M.Spalten()))
        MatFehler("Inkompatible Dimension für 'Matrix = Matrix'!");
#endif
    
    for (int i = 0; i < Zeilen(); i++)
        for (int j = 0; j < Spalten(); j++)
            (*this)(i,j) = M(i,j);
}

Matrix& Matrix::operator += (const Matrix& M) {
#ifndef NDEBUG
    if ((Zeilen() != M.Zeilen()) || (Spalten() != M.Spalten()))
        MatFehler("Inkompatible Dimension für 'Matrix += Matrix'!");
#endif
    
    for (int i = 0; i < Zeilen(); i++)
        for (int j = 0; j < Spalten(); j++)
            (*this)(i,j) += M(i,j);
            
    return (*this);
}

Matrix& Matrix::operator -= (const Matrix& M) {
#ifndef NDEBUG
    if ((Zeilen() != M.Zeilen()) || (Spalten() != M.Spalten()))
        MatFehler("Inkompatible Dimension für 'Matrix -= Matrix'!");
#endif

    for (int i = 0; i < Zeilen(); i++)
        for (int j = 0; j < Spalten(); j++)
            (*this)(i,j) -= M(i,j);
            
    return (*this);
}

Matrix& Matrix::operator *= (const Matrix& M) {
#ifndef NDEBUG
    if (Spalten() != M.Zeilen())
        MatFehler("Inkompatible Dimension für 'Matrix *= Matrix'!");
#endif

    Matrix * result = new Matrix (Zeilen(), M.Spalten());
    for (int i = 0; i < (*result).Zeilen(); i++)
        for (int j = 0; j < (*result).Spalten(); j++)
            (*result)(i,j) = dot(Zeile(i), M.Spalte(j)); //TODO TODO TODO TODO TODO TODO
            
    return (*result);
}

Matrix& Matrix::operator *= (const double s) {
    for (int i = 0; i < Zeilen(); i++)
        for (int j = 0; j < Spalten(); j++)
            (*this)(i,j) *= s;
            
    return (*this);
}

Vektor& Matrix::operator *= (const Vektor& v) {
#ifndef NDEBUG
    if (Spalten() != v.Laenge())
        MatFehler("Inkompatible Dimension für 'Matrix *= Vektor'!");
#endif

    Vektor * result = new Vektor (Zeilen());
    for (int i = 0; i < (*result).Laenge(); i++)
        (*result)(i) = dot(Zeile(i), v);
        
    return (*result);
}

Matrix& Matrix::operator /= (const double s) {
    for (int i = 0; i < Zeilen(); i++)
        for (int j = 0; j < Spalten(); j++)
            (*this)(i,j) /= s;
            
    return (*this);
}

Matrix& Matrix::ReDim(size_t hoehe, size_t breite) {
    Vektor dummy (hoehe);
    Matx.resize(breite, dummy);

    for (int i = 0; i < breite; i++) {
        Vektor dummy2 (hoehe);
        Matx[i] = dummy2;
    }

    std::cout << "ich bin hier \n";
    return (*this);
}

size_t Matrix::Zeilen() const {
    if (Spalten() > 0) {
        return Matx[0].Laenge();
    } else {
        return 0;
    }
}

Vektor Matrix::Zeile (size_t i) const {
#ifndef NDEBUG
    if (i >= Zeilen())
        MatFehler("Inkompatible Dimension für Zeile()");
#endif

    Vektor * result = new Vektor (Spalten());
    for (int j = 0; j < (*result).Laenge(); j++) 
        (*result)(j) = (*this)(i,j);
    return * result;
}

Vektor Matrix::Spalte (size_t j) const {
#ifndef NDEBUG
    if (j >= Spalten())
        MatFehler("Inkompatible Dimension für Zeile()");
#endif
    
    return Vektor (Matx[j]);
}
    
//double Matrix::Norm2 () const; // TODO TODO TODO TODO TODO TODO

double Matrix::NormMax() const { // TODO TODO TODO TODO TODO TODO
    double result = 0;
    
    for (int i = 0; i < Spalten(); i++) {
        double zeilensumme = 0;
        for (int j = 0; j < Zeilen(); j++)
            zeilensumme += (*this)(i,j);
        if (zeilensumme > result)
            result = zeilensumme;
    }
    
    return result;
}
    
void Matrix::MatFehler(const std::string& str) {
    std::cerr << "\nMatrixfehler: " << str << '\n' << std::endl;
    exit(1);
}

// friends methods

Matrix operator + (const Matrix& A, const Matrix& B) {
#ifndef NDEBUG
    if ((A.Zeilen() != B.Zeilen()) || (A.Spalten() != B.Spalten()))
        Matrix::MatFehler("Inkompatible Dimension für 'Matrix + Matrix'!");
#endif
    
    Matrix result = A;
    return (result += B);
}

Matrix operator - (const Matrix& A, const Matrix& B) {
#ifndef NDEBUG
    if ((A.Zeilen() != B.Zeilen()) || (A.Spalten() != B.Spalten()))
        Matrix::MatFehler("Inkompatible Dimension für 'Matrix - Matrix'!");
#endif
    
    Matrix result = A;
    return (result -= B);
}

Matrix operator -  (const Matrix& M) {
    Matrix result (M.Zeilen(), M.Spalten());
    return (result - M);
}

Matrix operator * (const double s, const Matrix& M) {
    Matrix result = M;
    return result *= s;
}

Matrix operator * (const Matrix& M, const double s) {
    Matrix result = M;
    return result *= s;
}

Matrix operator * (const Matrix& A, const Matrix& B) {
#ifndef NDEBUG
    if (A.Spalten() != B.Zeilen())
        Matrix::MatFehler("Inkompatible Dimension für 'Matrix * Matrix'!");
#endif
    
    Matrix result = A;
    return (result *= B);
}
    
Vektor operator * (const Matrix& M, const Vektor& v) {
#ifndef NDEBUG
    if (M.Spalten() != v.Laenge())
        Matrix::MatFehler("Inkompatible Dimension für 'Matrix * Vektor'!");
#endif
    
    Matrix result = M;
    return result *= v;
}

Vektor operator * (const Vektor& v, const Matrix& M) {
#ifndef NDEBUG
    if (M.Spalten() != v.Laenge())
        Matrix::MatFehler("Inkompatible Dimension für 'Matrix * Vektor'!");
#endif
    
    Matrix result = M;
    return result *= v;
}

Matrix operator / (const Matrix& M, const double s) {
    Matrix result = M;
    return result /= s;
}

bool operator == (const Matrix& A, const Matrix& B) {
    if ((A.Spalten() != B.Spalten()) || (A.Zeilen() != B.Zeilen()))
        return false;
    
    for (int i = 0; i < A.Zeilen(); i++)
        for (int j = 0; j < A.Spalten(); j++)
            if (A(i,j) != B(i,j))
                return false;
    
    return true;
}
    
bool operator != (const Matrix& A, const Matrix& B) {
    return !(A == B);
}

std::ostream& operator << (std::ostream& out, Matrix& M) {
    out << std::setiosflags(std::ios::right);
    out << "# Hoehe: " << M.Zeilen() << std::endl;
    out << "# Breite: " << M.Spalten() << std::endl;
    
    for (int i = 0; i < M.Zeilen(); i++) {
        for (int j = 0; j < M.Spalten(); j++)
            out << M(i,j) << " ";
        out << std::endl;
    }
    
    out << std::endl;
    return out;
}

std::istream& operator >> (std::istream& in, Matrix& M) {
    int hoehe = 0, breite = 0;
    in >> hoehe >> breite;
    M = Matrix(hoehe, breite);
    
    for (int i = 0; i < hoehe; i++)
        for (int j = 0; j < breite; j++)
            in >> M(i,j);
            
    return in;
}
