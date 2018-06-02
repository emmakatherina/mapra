// Spielbrett.cpp by Jaquline Reuter and Emma Ahrens
// used in Aufgabe4, mathematisches Praktikum

#include "Spielbrett.h"

Spielbrett::Spielbrett(size_t Hoehe, size_t Breite) {                   //Konstruktor
    vector<char>  d;
    if (Hoehe <= 0 || Breite <= 0 ) {
        std::cout << "Fehler: Ungültige Spielbrettgroeße" << std::endl;
        return;
    }
    else {
        (*this).Hoehe = Hoehe;
        (*this).Breite = Breite;

        d.resize(Hoehe,'N');
        Brett.resize(Breite,d); 
    }
}

char& Spielbrett::operator () (size_t Spalte, size_t Zeile) {
    if (Spalte >= Breite || Zeile >= Hoehe) {
        cout << "Fehler: Ungültiger Index" << endl;
        
    }
    
    return Brett[Spalte][Zeile];
}

void Spielbrett::print () {
    for (int i = 0; i < Breite; i++) {
        for (int j = Hoehe-1; j >= 0; j--)
            cout << (*this)(i,j) << " ";
        cout << endl;
    }
}

void Spielbrett::Set (bool Spieler, size_t Spalte){     //Stein in Spalte werfen, Ich:Rot/True, Anderer:Gelb/False
    vector<char> c = Brett[Spalte];
    size_t l = c.size();

    if (Spieler) {
        for (int i = 0; i < l; i++){
            if (c[i] == 'N') {
                c[i] = 'R';
                break;
            }
        }
    }
    else {
        for (int i = 0; i < l; i++){
            if (c[i] == 'N') {
                c[i] = 'G';
                break;
            }
        }
    }
}

void Spielbrett::Unset (bool Spieler, size_t Spalte) { //Stein aus Spalte rausholen, Ich:Rot/True, Anderer:Gelb/False
    int l = Hoehe;

    for (int i = 0; i < Hoehe; i++)
        if ((i > 0) && ((*this)(Spalte,i) == 'N'))
            (*this)(Spalte, i-1) = 'N';
}

int Spielbrett::MaxLineEnemy (size_t Spalte, size_t Zeile){
    int dor = 0;
    int dol = 0;
    int re = 0;
    int li = 0;
    int dur = 0;
    int dul = 0;
    int u = 0;
    size_t b = Brett.size();
    size_t l = Hoehe;
    
    for (int i = Zeile + 1; i < l; i++) {                               // Diagonale oben rechts
        for(int j = Spalte + 1; j < b; j++)
            if ((*this)(j,i)=='G')
                dor+=1;
    }
    for (int i = Zeile + 1; i < l; i++) {                               // Diagonale oben links
        for(int j = Spalte - 1; j > 0; j--)
            if ((*this)(j,i)=='G')
                dol+=1;
    }
    
    for(int j = Spalte + 1; j < b; j++) {                                // rechts
        if ((*this)(j,Zeile)=='G')
            re+=1;
    }
    for(int j = Spalte - 1; j > 0; j--) {                                // links
        if ((*this)(j,Zeile)=='G')
            li+=1;
    }
    for (int i = Zeile - 1; i > 0; i--) {                               // Diagonale unten rechts
        for(int j = Spalte + 1; j < b; j++)
            if ((*this)(j,i)=='G')
                dur+=1;
    }
    for (int i = Zeile - 1; i > 0; i--) {                               // Diagonale unten links
        for(int j = Spalte - 1; j > 0; j--)
            if ((*this)(j,i)=='G')
                dul+=1;
    }
    for(int j = Zeile - 1; j > 0; j--) {                                // unten
        if ((*this)(Spalte,j)=='G')
            u+=1;
    }
    vector<int> c = {dor, dol, re, li, dur, dul, u};
    int x = dor;
    for (int i = 1; i < 7; i++) {
        if (x < c[i])
            x = c[i];
    }
    
    return x;
}

void Spielbrett::Fehler(const char* meldung) {
  std::cerr << "\nVektorfehler: " << meldung<< '\n' << std::endl;
  exit(1);
}
