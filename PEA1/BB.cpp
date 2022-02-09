#include "BB.h"
#include <queue>
#include <vector>
#include <iostream>

int BB::getUpperBound(int n) {
	//algorytm opisany w metodzie BF
	int minimumDistance = INT_MAX;
	std::vector <int> cities;
	for (int i = 1; i < graph->getSize(); i++) {
		cities.push_back(i);
	}
	do {
		int totalDistance = 0;
		totalDistance += graph->getMatrix()[0][cities[0]];
		for (int i = 0; i < (int)cities.size() - 1; i++) {
			totalDistance += graph->getMatrix()[cities[i]][cities[i + 1]];
		}
		totalDistance += graph->getMatrix()[cities[cities.size() - 1]][0];
		if (totalDistance < minimumDistance) {
			minimumDistance = totalDistance;
		}
		n--;

	} while (std::next_permutation(cities.begin(), cities.end()) && (n != 0));

	return minimumDistance;
}


void printVector(std::vector<int> vector) {
	for (int i = 0; i < vector.size(); i++) {
		std::cout << vector[i] << " ";
	}
}
template<class T>
void printQueue(T q)
{
	while (!q.empty())
	{
		std::cout << q.top().cost << "\n";
		q.pop();
	}
}

void BB::findPath(Graph* graph) {
	this->graph = graph;
	//Obiekt na koncowy wierzcholek wraz z droga do niego
	Node finalNode;
	finalNode.cost = INT_MAX;
	//wektor przecowujacy wskazniki grafow ktore trzeba bedzie usunac
	std::vector<Graph*> graphsToClean;
	//porownanie elementow w kolejce priorytetowej
	auto compare = [](Node l, Node r)
	{
		return l.cost > r.cost;
	};

	//Obiekt przechowujacy poprzednika rozpatrywanych rozgalezien
	Node parentNode;
	parentNode.level = 0;
	Graph* startGraph = new Graph(0, 0, 0);
	//ustawiamy graf dla wierzcholka poczatkowego kopiujac ten podany na wejsciu
	startGraph->clone(graph);
	startGraph->setDiagonalValue(INT_MAX);
	parentNode.vertexNumber = 0;
	//redukujemy macierz
	parentNode.cost = startGraph->reduceMatrix();
	parentNode.graph = startGraph;
	parentNode.road.push_back(0);
	//wyznaczamy gorna granice generujac pewna ilosc permutacji drogi i wyznaczajac z nich minimum
	int upperBound;
	if (graph->getSize() > 15) {
		upperBound = getUpperBound(1000);
	}
	else if (graph->getSize() > 10) {
		upperBound = getUpperBound(100);
	}
	else if(graph->getSize()>5){
		upperBound = getUpperBound(10);
	}
	else {
		upperBound = getUpperBound(1);
	}
	//kolejka priorytetowa na rozgalezienia
	std::priority_queue<Node, std::vector<Node>, decltype(compare)> q(compare);

	bool end = false;

	while (!end) {
		//wektor na numery wierzch. potencjalnych rozgalezien
		std::vector <int> childNodes;
		//znajdujemy s¹siadów do których jest droga i którzy nie zostali jeszcze odwiedzeni

		//sprawdzamy mozliwe rozgalezienia
		for (int i = 0; i < graph->getSize(); i++) {
			if (parentNode.graph->getMatrix()[parentNode.vertexNumber][i] != INT_MAX) {
				childNodes.push_back(i);
			}
		}
		//dla kazdego ze znalezionych potencjalnych rozgalezien
		for (int i = 0; i < childNodes.size(); i++) {
			//tworzymy nowy obiekt na wierzcholek
			Node node;
			//rozpatrywany s¹siad (numer wierzcho³ka)
			node.vertexNumber = childNodes[i];
			node.level = parentNode.level + 1;
			//przepisujemy droge od rodzica i dodajemy aktualny wierzcholek
			node.road = parentNode.road;
			node.road.push_back(node.vertexNumber);
			//tworzymy dla niego graf oparty na g³ównym grafie
			Graph* workGraph = new Graph(0, 0, 0);
			workGraph->clone(parentNode.graph);
			//ustawiamy odpowiednie wartosci na INF 
			workGraph->reduceColumnsAndRows(parentNode.vertexNumber, node.vertexNumber);
			//ustawiamy droge na INF na wierzcholkow juz wczesniej odwiedzonych
			workGraph->setInfToVectorOfNodes(node.road, node.vertexNumber);
			//redukujemy macierz i zapisujemy koszt tej redukcji
			int reductionCost = workGraph->reduceMatrix();
			node.graph = workGraph;

			node.cost = parentNode.cost + parentNode.graph->getMatrix()[parentNode.vertexNumber][node.vertexNumber] + reductionCost;
			if (node.cost > upperBound) {
				workGraph->deleteMatrix();
				continue;
			}
			q.push(node);
		}
		//dodajemy wskaznik na graf rodzica do listy wierzch. do wyczyszczenia 
		graphsToClean.push_back(parentNode.graph);
		//pobieramy wierzcholek ktory ma nalepsz¹ drogê i usuwamy go z kolejki
		parentNode = q.top();
		q.pop();
		//je¿eli pobrany wierzcholek jest na przedostatnim poziomie to obliczamy jego koncowa wartosc i dodajemy do kolejki
		//po czym pobieramy kolejne minimum
		if (parentNode.level == startGraph->getSize() - 1) {
			int toZeroCost = parentNode.graph->getMatrix()[parentNode.vertexNumber][0];
			if (toZeroCost != INT_MAX) {
				parentNode.cost += toZeroCost;
			}
			parentNode.level++;
			parentNode.road.push_back(0);
			q.push(parentNode);
			parentNode = q.top();
			q.pop();
		}
		//jezeli pobrany wierzcholek jest na najnizszym poziomie i zzostal wybrany z listy prio. (ma naleszpa droge)
		//to jest to wierzch. koñcowy
		if (parentNode.level == startGraph->getSize()) {
			/*if (upperBound > prevNode.cost) {
				upperBound = prevNode.cost;
				finalNode = prevNode;
			}*/
			end = true;
			finalNode = parentNode;
		}
		/*
		if (finalNode.cost < q.top().cost) {
			end = true;
		}*/
	};

	
	std::cout << "Optymalna sciezka to:";
	for (int i = 0; i < finalNode.road.size(); i++) {
		std::cout << finalNode.road[i] << "->";
	}
	std::cout << "\nJej dlugosc/waga to: " << finalNode.cost << "\n";
	

	//czyszczenie 
	for (int i = 0; i < graphsToClean.size(); i++) {
		graphsToClean[i]->deleteMatrix();
	}
	while (!q.empty())
	{
		q.top().graph->deleteMatrix();
		q.pop();
	}
}