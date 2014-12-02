#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <time.h> //Ne pas oublier d'inclure le fichier time.h

int const tailleTableau(10);

using namespace std;

void afficherTab(int tab[][tailleTableau], int nbColonne){
	for (int i = 0; i < nbColonne; i++){
		for (int j = 0; j < 10; j++){
			cout << tab[i][j];
		}
		cout << " ";
	}
}
void generer(int tab[][tailleTableau]){
	
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 10; j++){
			tab[i][j] = rand() % 9 + 1;
		}
	}
}
int evaluer(int tab[][tailleTableau], int colonne){
	int resultat = 0;

	for (int i = 0; i < 10; i++){
		
		resultat += tab[colonne][i];
		
	}
	return resultat;
}
void croisement(int tab[][tailleTableau]){
	srand(time(NULL)); // initialisation de rand
	int c = rand() % 9 + 1;

	/*cout << endl;
	cout << "c: " << c;
	cout << endl;*/

	for (int i = 0; i < c; i++){
		tab[2][i] = tab[0][i];
		tab[3][i] = tab[1][i];
	}
	for (int i = c; i < tailleTableau; i++){
		tab[2][i] = tab[1][i];
		tab[3][i] = tab[0][i];
	}
}
void mutation(int tab[][tailleTableau]){
	//srand(time(NULL)); // initialisation de rand
	int m = rand() % 9 + 1;
	int enfant = rand() % 2 + 2;

	tab[enfant][m] = rand() % 9;

	//cout << "mutation (enfant, lopus, valeur): " << enfant << " " << m << " " << tab[enfant][m] << endl;
}
void remplacement(int tab[][tailleTableau]){
	int p1 = evaluer(tab, 0);
	int p2 = evaluer(tab, 1);
	int e1 = evaluer(tab, 2);
	int e2 = evaluer(tab, 3);

	if (p1 - e1 >= 0){
		if (p2 - e1 >= 0){
			if (p1 - e1 >= p2 - e1){
				for (int i = 0; i < tailleTableau; i++){
					tab[0][i] = tab[2][i];
				}
			}
			else{
				for (int i = 0; i < tailleTableau; i++){
					tab[1][i] = tab[2][i];
				}
			}
		}
		else{
			for (int i = 0; i < tailleTableau; i++){
				tab[0][i] = tab[2][i];
			}
		}
	}

	if (p1 - e2 >= 0){
		if (p2 - e2 >= 0){
			if (p1 - e2 >= p2 - e2){
				for (int i = 0; i < tailleTableau; i++){
					tab[0][i] = tab[3][i];
				}
			}
			else{
				for (int i = 0; i < tailleTableau; i++){
					tab[1][i] = tab[3][i];
				}
			}
		}
		else{
			for (int i = 0; i < tailleTableau; i++){
				tab[0][i] = tab[3][i];
			}
		}
	}

}
int lancer(int tab[][tailleTableau]){
	int generation = 0;
	do{
		croisement(tab);
		mutation(tab);
		remplacement(tab);

		cout << evaluer(tab, 0) << " " << evaluer(tab, 1) << " ";
		afficherTab(tab, 2);

		cout << endl;

		generation++;
		Sleep(1000);
	} while (evaluer(tab, 0) >= 20 && evaluer(tab, 1) >= 20);
	return generation;
}
int main(){
	char toto = 'r';
	srand(time(NULL)); // initialisation de rand

	int population[4][tailleTableau];
	while (toto != 's' && toto == 'r'){
		generer(population);
		afficherTab(population, 2);

		cout << endl;
		cout << endl;

		for (int i = 0; i < 2; i++){
			cout << evaluer(population, i);
			cout << " ";
		}
		cout << endl;


	
		cout << endl;
		cout << "generation: " << lancer(population) << endl;
		afficherTab(population, 2);

		cout << endl;
		cout << "s: stop, r: relancer" << endl;

		cin >> toto;
	}
		


	return 0;
}