#include <iostream>
#include <windows.h>
#include <string>
#include <random>
#include <iomanip>
#include "Graph.h"
#include "BF.h"
#include "BB.h"
#include "DP.h"

#define MAX_VALUE 1000000


void makeGraphRandom(Graph* graph);
/// <summary>
/// Ustawianie nazwy pliku
/// </summary>
/// <returns>Wprowadzona nazwa</returns>
std::string setFileName() {
    system("CLS");
    std::string fileName;
    std::cout << "Podaj nazwe pliku do zaladowania wraz z jego rozszerzeniem:";
    std::cin >> fileName;
    return fileName;
}

bool isChoiceValid(int choice, int n1, int n2) {
    if (choice >= n1 && choice <= n2) return true;
    else return false;
}

void menu() {
    int choice = 0;
    std::string fileName;
    Graph graph(0,0,0);
    //TODO: sprawdzenie czy struktury nie sa puste przed wykonaniem na nich algorytmu
    while (choice != 8) {
        system("CLS");
        std::cout << "Wybierz opcje:\n";
        std::cout << "1.Wczytaj graf miast z pliku\n";
        std::cout << "2.Wyswietl graf miast\n";
        std::cout << "3.Znajdz optymalna sciezke metoda BF\n";
        std::cout << "4.DP\n";
        std::cout << "5.BB [TEST]\n";
        std::cout << "6.Losuj graf\n";
        std::cout << "7.-\n";
        std::cout << "8.Wyjscie\n";
        std::cout << "Wybor:";
        std::cin >> choice;
        std::cin.clear();							//resetujemy status strumienia wejść
        if (isChoiceValid(choice, 1, 8)) {
            switch (choice) {
            case 1: {
                fileName = setFileName();
                graph.loadGraphFromFile(fileName);
                std::cout << "\nGraf zostal zaladowany!\n";
                system("PAUSE");
                break;
            }
            case 2: {
                graph.printGraphMatrix();
                system("PAUSE");
                break;
            }
            case 3: {
                system("CLS");
                BF::findPath(&graph);
                system("PAUSE");
                break;
            }
            case 4: {
                system("cls");
                DP* dp = new DP();
                dp->findPath(&graph);
                //DP::findPath(&graph);
                system("PAUSE");
                break;
            }
            case 5: {
                system("CLS");
                BB* bb = new BB();
                bb->findPath(&graph);
                system("PAUSE");
                break;
            }
            case 6: {
                system("CLS");
                int size;
                std::cout << "Podaj rozmiar grafu do wylosowania";
                std::cin >> size;
                graph.resizeMatrix(size);
                makeGraphRandom(&graph);
                std::cout << "Wylosowano graf!";
                system("PAUSE");
                break;
            }
            case 7: {

            }
            case 8: {
                break;
            }
            }
        }
        else {
            std::cout << "Podano liczba spoza zakresu! Podaj liczbe jeszcze raz!";
            system("PAUSE");
        }
    }
    return;
}


long long int read_QPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

void makeGraphRandom(Graph* graph) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, MAX_VALUE);

    for (int i = 0; i < graph->getSize(); i++) {
        for (int j = 0; j < graph->getSize(); j++) {
            if (i != j)
                graph->addEdge(i, j, dist(gen)+1);
            else
                graph->addEdge(i, j, 0);
        }
    }
    
    return;
}

#pragma optimize("", off)
int main()
{
    menu();
    /*
    int testGraphSize = 27;

    long float totalTime = 0;

    long long int frequency, start, elapsed;
    srand(time(NULL));
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

    for (int i = 0; i < 10; i++) {
        Graph* testGraph = new Graph(testGraphSize, 0, 0);
        makeGraphRandom(testGraph);

        start = read_QPC();//
        DP* dp = new DP();
        dp->findPath(testGraph);
        elapsed = read_QPC() - start;//

        std::cout << "Time [us] = " << (1000000.0 * elapsed) /
            frequency << "\n";
        totalTime += (1000000.0 * elapsed) /
            frequency;
    }
    std::cout << "Srednia:" << totalTime / 10000<< "[ms]\n";
    system("PAUSE");
    
 
    return 0;
    */
}
#pragma optimize("", on)
