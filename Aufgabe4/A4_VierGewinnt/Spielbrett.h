// Spielbrett.h by Jaquline Reuter and Emma Ahrens
// used in Aufgabe4, mathematisches Praktikum

#include  <iostream>
#include  <vector>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <cfloat>

using namespace std;

class Spielbrett
{
	private:
		std::vector<vector<char>> Brett;
        size_t Hoehe, Breite;

	public:
    explicit Spielbrett (size_t Hoehe = 1, size_t Breite = 1);          //Konstruktor
    ~Spielbrett () {};                                                      //Destruktor
    
    char& operator () (size_t Spalte, size_t Zeile);                       //Zugriff auf Einträge der Spalten
    void Fehler(const char* Meldung);
	void print ();
    
    bool Set (bool Spieler, size_t Spalte);
    bool Unset (size_t Spalte);
	size_t Height (size_t Spalte);
	int BewerteVierer(int, int);
	int Bewertung();
	bool VollesBrett();
	int Spielende();

	int BestNextStep ();
	int BestNextStep (int, bool);
	int TestStep( int spalte);
};
