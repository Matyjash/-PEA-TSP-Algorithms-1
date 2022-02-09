#include "BF.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>

int BF::factorial(int n) {
	if ((n == 0) || (n == 1))
		return 1;
	else return n*factorial(n - 1);
}

void BF::findPath(Graph* graph) {
	
	std::vector <int> finalPath;
	int minimumDistance = INT_MAX;
	bool skip = false;
	//wektor do tworzenia permutacji zawieraj�cy wszystkie miasta z wyj�tkiem 0 (startowe)
	std::vector <int> cities;
	for (int i = 1; i < graph->getSize(); i++) {
		cities.push_back(i);
	}

	finalPath = cities;
	//liczba �cie�ek, (n-1)! permutacji
	int numberOfPaths = factorial(graph->getSize() - 1);
	do {
		int totalDistance = 0;
		/*for (int i = 0; i < cities.size(); i++) {
			std::cout << cities[i];
		}
		std::cout << "\n";
		*/

		//liczymy droge wygenerowanej permutacji
		//do drogi dodajemy odcinek z miasta o id 0 do pierwszego w permutacji
		totalDistance += graph->getMatrix()[0][cities[0]];
		//dodajemy kolejne drogi z permutacji
		for (int i = 0; i < (int)cities.size()-1; i++) {
			totalDistance += graph->getMatrix()[cities[i]][cities[i+1]];
			//jezeli droga jest ju� wi�ksza ni� ta minimalna to nie kontynuujemy dalszego liczenia
			if (totalDistance < minimumDistance) {
				skip = true;
				break;
			}
		}
		if (skip == true) {
			skip = false;
			continue;
		}
		//dodajemy drog� z ostatniego miasta w permutacji o pierwszego
		totalDistance += graph->getMatrix()[cities[cities.size()-1]][0];
		//je�eli rozpatrywana permutacja oka�e si� t� bardziej optymaln� to aktualizujemy najlepsz� tras� i minimaln� drog�
		if (totalDistance < minimumDistance) {
			finalPath = cities;
			minimumDistance = totalDistance;
		}
		
	} while (std::next_permutation(cities.begin(), cities.end()));
	
	std::cout << "Odnaleziona sciezka to: 0->";
	for (int i = 0; i < (int)finalPath.size(); i++) {
		std::cout << finalPath[i] << "->";
	}
	std::cout << "0\n";

	std::cout << "Jej laczna dlugosc/waga to: " << minimumDistance<<"\n";
	

}