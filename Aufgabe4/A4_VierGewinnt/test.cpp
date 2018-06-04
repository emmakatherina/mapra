#include "Spielbrett.h"

int main () {
	Spielbrett Brett (5, 7);

	Brett.Set(true, 1);
	Brett.Set(false, 2);

	Brett.Unset(2);
	Brett.Unset(1);

	cout << "Should be all N:\n";
	Brett.print();

	Brett.Set(true, 1);
	Brett.Set(true, 2);
	Brett.Set(true, 3);
	Brett.Set(true, 4);

	Brett.Set(true, 5);
	Brett.Set(true, 6);
	Brett.Set(true, 6);
	
	Brett.print();

	Brett.Unset(3);

	Brett.print();
	cout << "Bester naechster Zug: " << Brett.BestNextStep() << endl;

	Brett.Set(false, 0);
	Brett.Set(false, 1);
	Brett.Set(false, 2);
	Brett.Set(false, 2);
	Brett.Set(false, 3);
	Brett.Set(false, 3);
	Brett.Set(false, 3);

	Brett.print();
	
	Brett.Set(false, 3);
	Brett.print();
	
	int heights[] = {1, 2, 3, 4, 1, 1, 2};
	for(int i = 0; i < 7; i++) {
		if(Brett.Height(i) != heights[i]) {
			cerr << "Height is incorrect on column " << i << endl;
			exit(-1);
		}
	}

	return 0;
}
