// Mapra 2018 by Jaqueline Reuter and Emma Ahrens

#include <cmath>
#include <iostream>
#include <random>
#include "unit.h"
#include "Spielbrett.h"

const unsigned int Schwierigkeitsgrad = 4;

int main()
{
    int Zug, Gegenzug;

    Start(Schwierigkeitsgrad);

    for(unsigned int Spiel = 1; Spiel <= AnzahlSpiele; Spiel++)
    {
		Spielbrett Brett (((size_t) AnzahlZeilen), ((size_t) AnzahlSpalten));
		if (Spiel % 2 == 0) {
			Gegenzug = NaechsterZug(-1);
			Brett.Set(false, Gegenzug);
		}
		while (true) {
			Zug = Brett.BestNextStep();
			Brett.Set(true, Zug);
			Gegenzug = NaechsterZug(Zug);
			if (Gegenzug < 0) {
				break;
			}
			Brett.Set(false, Gegenzug);
		}
    }

    return 0;
}
