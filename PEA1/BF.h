#pragma once
#include "Graph.h"
static class BF
{
private:
	/// <summary>
	/// Metoda licz�ca silni�
	/// </summary>
	/// <param name="n">Liczba do poddania silni</param>
	/// <returns>Wynik w postaci inta</returns>
	static int factorial(int n);

public:
	/// <summary>
	/// Szukanie optymalnej drogi metod� BF
	/// </summary>
	/// <param name="graph">Graf z odelg�o�ciami</param>
	static void findPath(Graph* graph);
};

