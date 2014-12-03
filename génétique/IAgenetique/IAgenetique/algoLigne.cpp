#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int const tailleTableau(10);
int const taillePopulation(10);
int const tailleSelection(10);
int const nbMaxGeneration(10);

using namespace std;

void afficherTab(int tab[][tailleTableau], int nbColonne){
	for (int i = 0; i < nbColonne; i++){
		for (int j = 0; j < tailleTableau; j++){
			cout << tab[i][j];
		}
		cout << " ";
	}
}
void afficherTab(int tab[]){
	for (int i = 0; i < tailleTableau; i++){
			cout << tab[i];
	}
}
void generer(int tabPopulation[][tailleTableau]){
	
	for (int i = 0; i < taillePopulation; i++){
		for (int j = 0; j < tailleTableau; j++){
			tabPopulation[i][j] = rand() % 9 + 1;
		}
	}
}
int evaluer(int tab[][tailleTableau], int colonne){
	int resultat = 0;

	for (int i = 0; i < tailleTableau; i++){

		resultat += tab[colonne][i];

	}
	return resultat;
}
int evaluer(int tab[]){
	int resultat = 0;

	for (int i = 0; i < tailleTableau; i++){
		resultat += tab[i];
	}

	return resultat;
}
void selection(int tabPopu[][tailleTableau], int tabPar[][tailleTableau], int parentsChoisis[]){
	int x;
	for (int i = 0; i < tailleSelection; i++){
		x = rand() % taillePopulation;
		parentsChoisis[i] = x;
		for (int j = 0; j < tailleTableau; j++){
			tabPar[i][j] = tabPopu[x][j];
		}
	}
}
void croisement(int tabPar[][tailleTableau], int tabEnf[][tailleTableau]){
	int c = rand() % 9 + 1;

	//cout << endl;
	//cout << "c: " << c;
	//cout << endl;
	for (int k = 0; k < tailleSelection; k = k + 2){
		for (int i = 0; i < c; i++){
			tabEnf[k][i] = tabPar[k][i];
			tabEnf[k+1][i] = tabPar[k+1][i];
		}
		for (int i = c; i < tailleTableau; i++){
			tabEnf[k][i] = tabPar[k+1][i];
			tabEnf[k+1][i] = tabPar[k][i];
		}
	}
	
}
void mutation(int tab[][tailleTableau]){
	//srand(time(NULL)); // initialisation de rand
	int m = rand() % 8 + 1;
	int enfant = rand() % 2 + 2;

	tab[enfant][m] = rand() % 9;

	//cout << "mutation (enfant, lopus, valeur): " << enfant << " " << m << " " << tab[enfant][m] << endl;
}
void remplacement(int tabPopulation[][tailleTableau], int tabPar[][tailleTableau], int tabEnf[][tailleTableau], int parentsChoisis[]){
	cout << endl;	
	// on remplace les parents par les enfants

	//for (int i = 0; i < tailleSelection; i++){
	//	for (int j = 0; j < tailleTableau; j++){
	//		tabPopulation[parentsChoisis[i]][j] = tabEnf[i][j];
	//	}
	//	//cout << "parentsChoisis: " << parentsChoisis[i] << endl;
	//
	// on garde les 2 meilleurs des 4 (2 parents, 2 enfants)

	int p1;
	int p2;
	int e1;
	int e2;

	for (int k = 0; k < tailleSelection; k = k + 2){
		int p1 = evaluer(tabPar, k);
		int p2 = evaluer(tabPar, k+1);
		int e1 = evaluer(tabEnf, k);
		int e2 = evaluer(tabEnf, k+1);

		if (p1 - e1 >= 0){
			if (p2 - e1 >= 0){
				if (p1 - e1 >= p2 - e1){
					for (int i = 0; i < tailleTableau; i++){
						tabPopulation[parentsChoisis[k]][i] = tabEnf[k][i];
					}
				}
				else{
					for (int i = 0; i < tailleTableau; i++){
						tabPar[k+1][i] = tabEnf[k][i];
					}
				}
			}
			else{
				for (int i = 0; i < tailleTableau; i++){
					tabPar[k][i] = tabEnf[k][i];
				}
			}
		}
		if (p1 - e2 >= 0){
			if (p2 - e2 >= 0){
				if (p1 - e2 >= p2 - e2){
					for (int i = 0; i < tailleTableau; i++){
						tabPar[k][i] = tabEnf[k+1][i];
					}
				}
				else{
					for (int i = 0; i < tailleTableau; i++){
						tabPar[k+1][i] = tabEnf[k+1][i];
					}
				}
			}
			else{
				for (int i = 0; i < tailleTableau; i++){
					tabPar[k][i] = tabEnf[k+1][i];
				}
			}
		}
	}
}
int lancer(int tabPopulation[][tailleTableau], int tabParents[][tailleTableau], int tabEnfants[][tailleTableau], int tabMeilleur[]){
	int generation = 0;
	int parentsChoisis[tailleSelection];
	int min = 100;
	int valeur;
	do{
		cout << endl;
		cout << "Valeur:" << endl;
		for (int i = 0; i < taillePopulation; i++){
			valeur = evaluer(tabPopulation, i);
			cout << valeur << " ";
			if (valeur <= min){
				min = valeur;
				for (int j = 0; j < tailleTableau; j++){
					tabMeilleur[j] = tabPopulation[i][j];
				}
			}
		}
		cout << endl;
		cout << "----------------------------------------------------";


		/*cout << "Generation en cours: " << generation << endl;
		for (int i = 0; i < taillePopulation; i++){
			valeur = evaluer(tabPopulation, i);
			cout << valeur << " ";
		}
*/
		//tabParents = tabPopulation;
		selection(tabPopulation, tabParents, parentsChoisis);
		/*cout << endl;
		cout << endl;
		cout << "selection: " << generation << endl;
		for (int i = 0; i < taillePopulation; i++){
			valeur = evaluer(tabPopulation, i);
			cout << valeur << " ";
		}*/

		croisement(tabParents, tabEnfants);
		/*cout << endl;
		cout << endl;
		cout << "croisement: " << generation << endl; 
		for (int i = 0; i < taillePopulation; i++){
			valeur = evaluer(tabPopulation, i);
			cout << valeur << " ";
		}*/

		mutation(tabEnfants);
		/*cout << endl;
		cout << endl;
		cout << "mutation: " << generation << endl;
		for (int i = 0; i < taillePopulation; i++){
			valeur = evaluer(tabPopulation, i);
			cout << valeur << " ";
		}*/

		remplacement(tabPopulation, tabParents, tabEnfants, parentsChoisis);
		/*cout << endl;
		cout << endl;
		cout << "Remplacement: " << generation << endl;
		for (int i = 0; i < taillePopulation; i++){
			valeur = evaluer(tabPopulation, i);
			cout << valeur << " ";
		}*/

		//cout << endl;

		generation++;
		Sleep(1000);
	} while (min >=30);//generation<nbMaxGeneration);
	return generation;
}
int main(){
	char toto = 'r';
	srand(time(NULL)); // initialisation de rand

	int population[taillePopulation][tailleTableau];
	int parents[tailleSelection][tailleTableau];
	int enfants[tailleSelection][tailleTableau];
	int scorePopulation[taillePopulation];

	int meilleur[tailleTableau];
	int nbgeneration;
	while (toto != 's' && toto == 'r'){
		generer(population);
		afficherTab(population, taillePopulation);

		cout << endl;

		for (int i = 0; i < taillePopulation; i++){
			cout << evaluer(population, i);
			cout << " ";
		}
		nbgeneration = lancer(population, parents, enfants, meilleur);
		cout << endl;
		cout << "generation: " << nbgeneration << endl;
		cout << "meilleur: ";
		afficherTab(meilleur);

		cout << endl;
		cout << "valeur meilleur: " << evaluer(meilleur);

		cout << endl;
		cout << "s: stop, r: relancer" << endl;

		cin >> toto;
	}
		
	return 0;
}