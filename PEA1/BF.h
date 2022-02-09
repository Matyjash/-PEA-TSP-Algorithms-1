#pragma once
#include "Graph.h"
static class BF
{
private:
	/// <summary>
	/// Metoda licz¹ca silniê
	/// </summary>
	/// <param name="n">Liczba do poddania silni</param>
	/// <returns>Wynik w postaci inta</returns>
	static int factorial(int n);

public:
	/// <summary>
	/// Szukanie optymalnej drogi metod¹ BF
	/// </summary>
	/// <param name="graph">Graf z odelg³oœciami</param>
	static void findPath(Graph* graph);
};

