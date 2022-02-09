#include "DP.h"
#include <iostream>

void DP::printPath(int set, int node) {
	//na podobnej zasadzie jak wyszukiwanie sciezki teraz przechodzimy po niej jeszcze raz
	//ale z gotow¹ ju¿ tablic¹ wybieraj¹c najlepsze wierzcho³ki i odtwarzaj¹c w ten sposób drogê
	if (set == 0) return;
	int bestCost = INT_MAX;
	int bestNode = 0;

	for (int i = 0; i < graph->getSize(); i++) {
		int newSet = set & (((1 << graph->getSize()) - 1) - (1 << i));

		if (newSet!=set) {

			int cost = graph->getMatrix()[node][i] + matrix[newSet][i];
			if (cost < bestCost) {
				bestCost = cost;
				bestNode = i;
			}
		}

	}
	int nextSet = set & (((1 << graph->getSize()) - 1) - (1 << bestNode));
	std::cout << bestNode << "->"; 
	printPath(nextSet, bestNode);
}

void DP::printMatrix() {
	for (int i = 0; i < combNumber; i++) {
		for (int j = 0; j < graph->getSize(); j++) {
			std::cout << matrix[i][j] << "\t\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void DP::findPath(Graph* graph) {

	this->graph = graph;
	combNumber = 1 << graph->getSize();
	int startSet = (1 << graph->getSize()) - 2;

	//inicjalizacja macierzy
	matrix = new int* [combNumber];
	for (int i = 0; i < combNumber; i++) {
		matrix[i] = new int[graph->getSize()];
	}

	//pierwszy rz¹d wype³niamy wartoœciamy dróg do 0
	for (int i = 0; i < graph->getSize();i++) {
		matrix[0][i] = graph->getMatrix()[i][0];
	}

	//wype³enienie jej wartosciami INT_MAX (umownie nieskonczonosc)
	for (int i = 1; i < combNumber; i++) {
		for (int j = 0; j < graph->getSize(); j++) {
			matrix[i][j] = INT_MAX;
		}
	}
	
	std::cout << "\n";
	std::cout<<"Dlugosc optymalnej sciezki:"<<DPRec(startSet, 0);
	std::cout << "\n";
	std::cout << "0->"; printPath(startSet, 0); std::cout << "0\n";
	
	//czyszczenie macierzy
	for (int i = 0; i < combNumber; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

int DP::DPRec(int set, int node) {
	

	//je¿eli znamy ju¿ drogê to pobieramy j¹ bezpoœrednio z tablicy
	if (matrix[set][node]!=INT_MAX) {
		return matrix[set][node];
	}
	//je¿eli nie to sprawdzamy kolejne opcje przechodz¹c przez mo¿liwe wierzcho³ki
	else {
		for (int i = 0; i < graph->getSize(); i++) {
			//usuwamy z zestawu wierzcholkow ten dla ktorego droge bedziemy liczyc
			//najpierw od pelnego zestawu (1111...) odejmujemy rozpatrywany wierzcholek i wykonujemy koniunkcje 
			//ze starym zestawem w ten sposób uzyskuj¹c ten sam zestaw ale pozbawiony rozpatrywanego wierzcholka
			int newSet = set&(((1<<graph->getSize())-1)-(1 << i));
			if (newSet != set) {
				//obliczamy rekurencyjnie koszt uwzgledniajac przejscie z node do i
				int cost = DPRec(newSet, i) + graph->getMatrix()[node][i];
				//jezeli jest to najlepsze polaczenie to ustawiamy je jako minimum i zapisujemy w tablicy
				if (cost < matrix[set][node]) {
					matrix[set][node] = cost;
				}
			}
		}
		//zwracamy otrzymany koszt
		return matrix[set][node];
	}
}


DP::~DP() {

	for (int i = 0; i < combNumber; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}