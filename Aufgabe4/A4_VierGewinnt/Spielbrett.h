// Spielbrett.h by Jaquline Reuter and Emma Ahrens
// used in Aufgabe4, mathematisches Praktikum

#include  <cmath>
#include  <iostream>
#include  <vector>

using namespace std;

class Spielbrett
{
	private:
		std::vector<vector<char>> Brett;
        size_t Hoehe, Breite;

	public:
    explicit Spielbrett (size_t Laenge = 1, size_t Breite = 1);          //Konstruktor
    ~Spielbrett () {};                                                      //Destruktor
    
    void print ();
    char& operator () (size_t Spalte, size_t Zeile);                       //Zugriff auf Einträge der Spalten
    void Fehler(const char* Meldung);
    
    void Set (bool Spieler, size_t Spalte);
    void Unset (bool Spieler, size_t Spalte);
    int MaxLineEnemy (size_t Spalte, size_t Zeile);
};
