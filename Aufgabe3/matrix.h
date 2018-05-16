/***********************************************
 *  Name        : matrix.h                      *
 *  Verwendung  : Header zu Matrixklasse        *
 *  Autor       : Emma Ahrens, Jaqueline Reuter *
 *  Datum       : Nov '96 - Mai '00             *
 *  Aktualisiert: K. Brix, Apr '07              *
 *                Y. Zhang, Feb '14             *
 *                F. Gruber, Apr '16            *
 ***********************************************/


#ifndef matrix_h
#define matrix_h

#include <iostream>
#include <vector>
#include <string>

#include "vektor.h"

class Vektor;

class Matrix
{
  private:
    std::vector<Vektor> Matx;                            // vektor=Breite, Vektor=Laenge //Daten
    
  public:
    explicit Matrix (size_t hoehe = 1, size_t breite = 1); //Konstruktor mit Laenge und Breite
    ~Matrix () {};                                       //Destruktor
    Matrix (const Matrix&);                              //Kopierkonstruktor
    
    double& operator () (size_t, size_t);                // Zugriff auf Einträge der Matrix
    double operator () (size_t, size_t) const;           // Zugriff falls Matrix const
    
    Matrix& operator = (const Matrix&);                  // Zuweisung
    Matrix& operator += (const Matrix&);                 // arithmetische Operationen
    Matrix& operator -= (const Matrix&);
    Matrix& operator *= (const Matrix&);
    Matrix& operator *= (const double);
    Vektor& operator *= (const Vektor&);
    Matrix& operator /= (const double);
    
    Matrix& ReDim (size_t, size_t);                      // Getter und Setter
    size_t Zeilen () const ;
    size_t Spalten () const { return Matx.size(); }
    Vektor Zeile (size_t) const;
    Vektor Spalte (size_t) const;
    
    //double Norm2 () const;
    double NormMax() const;
    
    static void MatFehler (const std::string& str);     // Fehler
    
    friend class Vektor;
    
    friend Matrix operator + (const Matrix&, const Matrix&); // Arithmetik
    friend Matrix operator - (const Matrix&, const Matrix&);
    friend Matrix operator -  (const Matrix&);                // Vorzeichen
    friend Matrix operator * (const double, const Matrix&);
    friend Matrix operator * (const Matrix&, const double);
    friend Matrix operator * (const Matrix&, const Matrix&);
    friend Vektor operator * (const Matrix&, const Vektor&);
    friend Vektor operator * (const Vektor&, const Matrix&);
    friend Matrix operator / (const Matrix&, const double);
    
    friend bool operator == (const Matrix&, const Matrix&); // Vergleiche
    friend bool operator != (const Matrix&, const Matrix&);
    
    friend std::istream& operator >> (std::istream&, Vektor&);       // Eingabe
    friend std::ostream& operator << (std::ostream&, const Vektor&); // Ausgabe
};

#endif /* matrix_h */
