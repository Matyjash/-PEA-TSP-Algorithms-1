#pragma once
#include "Graph.h"
#include <vector>
#include <queue>
#include "Node.h"
static class BB
{
public:
	Graph* graph;

	/// <summary>
	/// Szukanie optymalnej drogi metod� B & B
	/// </summary>
	/// <param name="graph">Graf z odleg�o�ciami</param>
	void findPath(Graph* graph);

	/// <summary>
	/// Generowanie n sciezek w grafie i wybor najlepszej w celu ustalenia granicy do por�wnania 
	/// w pozniejszym algorytmie
	/// </summary>
	/// <param name="n">Ilo�� scie�ek do wygenerowania</param>
	/// <param name="graph">Graf z miastami</param>
	int getUpperBound(int n);
};

