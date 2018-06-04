// Spielbrett.cpp by Jaquline Reuter and Emma Ahrens
// used in Aufgabe4, mathematisches Praktikum

#include "Spielbrett.h"
#include <cstdlib>
#include <climits>

Spielbrett::Spielbrett(size_t Hoehe, size_t Breite) {                   //Konstruktor
    vector<char>  d;
    if (Hoehe <= 0 || Breite <= 0 ) {
		Fehler("Ungueltige Spielbrettgroesse.");
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
        Fehler("operator (): Ungültiger Index");
    }
    
    return Brett[Spalte][Zeile];
}

bool Spielbrett::Set (bool Spieler, size_t Spalte){     //Stein in Spalte werfen, Ich:Geld/True, Anderer:Rot/False
	size_t Zeile = Height(Spalte);
	if (Zeile < Hoehe) {
		if (Spieler) {
			(*this)(Spalte, Zeile) = 'G';
		} else {
			(*this)(Spalte, Zeile) = 'R';
		}
		return true;
	} else {
		cout << "Fehler: Set auf voller Spalte!" << endl;
		print();
		exit(-1);
		return false;
	}
}

bool Spielbrett::Unset (size_t Spalte) { //Stein aus Spalte rausholen
	int h = Height(Spalte);
	if(h != 0) {
		(*this)(Spalte, h-1) = 'N';
	}
}

void Spielbrett::Fehler(const char* meldung) {
  std::cerr << meldung<< '\n' << std::endl;
  exit(1);
}

void Spielbrett::print () {
	cout << "Bewertung: " << Bewertung() << endl;
	for (int j = Hoehe-1; j > -1; j--) {
		cout << "|";
		for (int i = 0; i < Breite; i++) {
			char c = (*this)(i,j);
			if(c != 'N')
				cout << c << ' ';
			else
				cout << "  ";
		}
		cout << "|" << endl;
	}
	cout << endl;
}

int Spielbrett::BestNextStep(int depth, bool unserZug) {	
	int BesterWert = unserZug ? INT_MIN : INT_MAX;
	if (depth > 0) {
		for (int i = 0; i < Breite; i++) {
			if (Height(i) < Hoehe) {
				Set(unserZug, i);
				int Wert = BestNextStep(depth-1, !unserZug);
				if(unserZug) {
					if(Wert > BesterWert) {
						BesterWert = Wert;
					}
				} else {
					if(Wert < BesterWert) {
						BesterWert = Wert;
					}
				}
				Unset(i);
			}
		}
		return BesterWert;
	} else {
		return Bewertung();
	}
}

int Spielbrett::BestNextStep () {
	vector<int> BesteSpalten;
	int BesteSpalte = INT_MIN;

	for (int i = 0; i < Breite; i++) {
		if (Height(i) < Hoehe) {
			Set(true, i);
			int nextStep = BestNextStep(5, false);
			if (nextStep > BesteSpalte) {
				BesteSpalte = nextStep;
				BesteSpalten.clear();
			}
			if (nextStep == BesteSpalte) {
				BesteSpalten.push_back(i);
			}
			Unset(i);
		}
	}

	return BesteSpalten[rand() % BesteSpalten.size()]; 
}

int Spielbrett::TestStep (int spalte) {
	if ((spalte < Breite) && (spalte > -1)) {
		return spalte;
	} else {
		return -1;
	}
}

size_t Spielbrett::Height (size_t Spalte) {
	if (Spalte < Breite) {
		for (int i = 0; i < Hoehe; i++) {
			if ((*this)(Spalte,i) == 'N') {
				return i;
			}
		}
	} else {
		Fehler("In Height: Spalte liegt nicht auf Brett");
	}
	return Hoehe;
}


int Spielbrett::BewerteVierer(int Gelbe, int Rote) {
	if(Rote == 0) {
		switch(Gelbe) {
			case 0:
				return 0;
			case 1:
				return 1;
			case 2:
				return 10;
			case 3:
				return 10000;
			case 4:
				return 1000000; 
			default:
				Fehler("Ungueltiger Wert in BewerteVierer!");	
		}
	} else if(Gelbe == 0) {
		switch(Rote) {
			case 0:
				return 0;
			case 1:
				return -1;
			case 2:
				return -10;
			case 3:
				return -10000;
			case 4:
				return -1000000; 
			default:
				Fehler("Ungueltiger Wert in BewerteVierer!");	
		}
	}
	return 0;
}

int Spielbrett::Bewertung() {
	int Result = 0;
	for(size_t i = 0; i < Breite; i++) {
		for(size_t j = 0; j < Hoehe; j++) {
			// Horizontale Vierer	
			if(i <= Breite - 4) {
				int Rote = 0;	
				int Gelbe = 0;
				for(size_t k = 0; k < 4; k++) {
					char Farbe = (*this)(i+k, j);
					if(Farbe == 'R')
						Rote++;
					else if (Farbe == 'G')
						Gelbe++;
				}
				Result += BewerteVierer(Gelbe, Rote);
			}

			// Vertikale Vierer	
			if(j <= Hoehe - 4) {
				int Rote = 0;	
				int Gelbe = 0;
				for(size_t k = 0; k < 4; k++) {
					char Farbe = (*this)(i, j+k);
					if(Farbe == 'R')
						Rote++;
					else if (Farbe == 'G')
						Gelbe++;
				}
				Result += BewerteVierer(Gelbe, Rote);
			}
			
			// Diagonale nach rechts oben
			if(i <= Breite - 4 && j <= Hoehe - 4) {
				int Rote = 0;	
				int Gelbe = 0;
				for(size_t k = 0; k < 4; k++) {
					char Farbe = (*this)(i+k, j+k);
					if(Farbe == 'R')
						Rote++;
					else if (Farbe == 'G')
						Gelbe++;
				}
				Result += BewerteVierer(Gelbe, Rote);
			}

			// Diagonale nach rechts unten
			if(i <= Breite - 4 && j >= 3) {
				int Rote = 0;	
				int Gelbe = 0;
				for(size_t k = 0; k < 4; k++) {
					char Farbe = (*this)(i+k, j-k);
					if(Farbe == 'R')
						Rote++;
					else if (Farbe == 'G')
						Gelbe++;
				}
				Result += BewerteVierer(Gelbe, Rote);
			}
		}
	}
	return Result;
}

bool Spielbrett::VollesBrett() {
	for (int i = 0; i < Breite; i++) {
		for (int j = 0; j < Hoehe; j++) {
			if ((*this)(i,j) == 'N')
				return false;
		}
	}
	return true;
}

int Spielbrett::Spielende() {

	for(size_t i = 0; i < Breite; i++) {
		for(size_t j = 0; j < Hoehe; j++) {
			// Horizontale Vierer	
			if(i <= Breite - 4) {
				int Rote = 0;	
				int Gelbe = 0;
				for(size_t k = 0; k < 4; k++) {
					char Farbe = (*this)(i+k, j);
					if(Farbe == 'R')
						Rote++;
					else if (Farbe == 'G')
						Gelbe++;
				}
				int vierer = BewerteVierer(Gelbe, Rote);
				switch (vierer) {
					case 1000000:
						return 1; //Wir haben gewonnen! :)
						break;
					case -1000000: //Die anderen haben gewonnen. :(
					default:
						return -1;
						break;
				}
			}

			// Vertikale Vierer	
			if(j <= Hoehe - 4) {
				int Rote = 0;	
				int Gelbe = 0;
				for(size_t k = 0; k < 4; k++) {
					char Farbe = (*this)(i, j+k);
					if(Farbe == 'R')
						Rote++;
					else if (Farbe == 'G')
						Gelbe++;
				}
				int vierer = BewerteVierer(Gelbe, Rote);
				switch (vierer) {
					case 1000000:
						return 1;
						break;
					case -1000000:
					default:
						return -1;
						break;
				}
			}
			
			// Diagonale nach rechts oben
			if(i <= Breite - 4 && j <= Hoehe - 4) {
				int Rote = 0;	
				int Gelbe = 0;
				for(size_t k = 0; k < 4; k++) {
					char Farbe = (*this)(i+k, j+k);
					if(Farbe == 'R')
						Rote++;
					else if (Farbe == 'G')
						Gelbe++;
				}
				int vierer = BewerteVierer(Gelbe, Rote);
				switch (vierer) {
					case 1000000:
						return 1;
						break;
					case -1000000:
					default:
						return -1;
						break;
				}
			}

			// Diagonale nach rechts unten
			if(i <= Breite - 4 && j >= 3) {
				int Rote = 0;	
				int Gelbe = 0;
				for(size_t k = 0; k < 4; k++) {
					char Farbe = (*this)(i+k, j-k);
					if(Farbe == 'R')
						Rote++;
					else if (Farbe == 'G')
						Gelbe++;
				}
				int vierer = BewerteVierer(Gelbe, Rote);
				switch (vierer) {
					case 1000000:
						return 1;
						break;
					case -1000000:
					default:
						return -1;
						break;
				}
			}
		}
	}
	if (VollesBrett())
		return 0; //Gleichstand

	return 2; //Weiterspielen! :)
}
