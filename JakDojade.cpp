#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Vector.h"
#include "Kolejka.h"
#include "String.h"
#include "Kolejka.h"
#include "Graf.h"
#include "Klasy.h"

using namespace std;
struct Dane
{
	String miasto;
	int lokalizacja[2];
};
void bfs(int tabX, int tabY, char** board, int wysokosc, int szerokosc, Vector<int>& dlugosci, Vector<String>& _miasta, Vector<Dane>& miasta);
String odczytanie_miasta(Vector<String>& _miasta, Vector <Dane>& miasta, int x, int y);
void wczytywanie_mapy(char** mapa, int wysokosc, int szerokosc);
void dodanie_miasta(Vector <Dane> &miasta, char** mapa, int wysokosc, int szerokosc);
void operacje(Graph& g);
int main() {

	Vector <Dane> miasta;
	int szerokosc,wysokosc;
	cin >> szerokosc;
	cin >> wysokosc;
	getchar();
	char** mapa = new char* [wysokosc];
	//char** mapa_2 = new char* [wysokosc];
	wczytywanie_mapy(mapa,wysokosc,szerokosc);
	dodanie_miasta(miasta, mapa, wysokosc, szerokosc);;
	Graph g;
	for (int i = 0; i < miasta.size(); ++i)
	{
		g.addVertex(miasta[i].miasto);
	}
	for (int i = 0; i < miasta.size(); ++i)
	{
		int ile = 0, ile2 = 0;
		Vector<int>dlugosci;
		Vector<String>_miasta;
		bfs(miasta[i].lokalizacja[1], miasta[i].lokalizacja[0], mapa, wysokosc, szerokosc, dlugosci,_miasta,miasta);
		for (int j = 0; j < dlugosci.size(); ++j)
		{
			g.addEdge(miasta[i].miasto, _miasta[j], dlugosci[j]);
		}
		
	}
	operacje(g);
	


	for (int i = 0; i < wysokosc; i++) {
		delete[] mapa[i];
		//delete[] mapa_2[i];
	}
	delete[] mapa;
	//delete[] mapa_2;
}
void operacje(Graph& g)
{
	int licza_pol_lot, liczba_zapytan;
	cin >> licza_pol_lot;
	for (int i = 0; i < licza_pol_lot; ++i)
	{
		int czas;
		String miasto1, miasto2;
		cin >> miasto1 >> miasto2 >> czas;
		g.addFlight(miasto1, miasto2, czas);
	}
	cin >> liczba_zapytan;
	for (int i = 0; i < liczba_zapytan; ++i)
	{
		int typ;
		String miasto1, miasto2;
		cin >> miasto1 >> miasto2 >> typ;
		Vector<pair<String, int>> path = g.shortestPath(miasto1, miasto2);
		if(typ==0)cout << path[path.size() - 1].second << endl;
		else
		{
			cout << path[path.size() - 1].second << " ";
			for (int j = 1; j < path.size() - 1; ++j)
			{
				cout << path[j].first << " ";
			}
			cout << endl;
		}
	}
}
void wczytywanie_mapy(char** mapa, int wysokosc, int szerokosc)
{

	// Alokacja pamięci dla kolumn
	for (int i = 0; i < wysokosc; i++) {
		mapa[i] = new char[szerokosc];
	}
	for (int i = 0; i < wysokosc; i++) {
		for (int j = 0; j < szerokosc; j++) {
			mapa[i][j] = getchar();
		}
		getchar(); // usuwanie znaku konca linii
	}
}
void dodanie_miasta(Vector <Dane> &miasta, char** mapa,int wysokosc, int szerokosc)
{
	for (int i = 0; i < wysokosc; i++) {
		for (int j = 0; j < szerokosc; j++) {
			if (mapa[i][j] == '*')
			{
				Dane dane;
				dane.lokalizacja[0] = i;
				dane.lokalizacja[1] = j;

				if ((j-1>0&& isalpha(mapa[i][j-1]) != 0)||(j - 1 > 0 && isdigit(mapa[i][j - 1])))// w lewo
				{
					String znalezione_miasto = "";
					int pom = j-1;
					while (pom >= 0 && mapa[i][pom] != '.' && mapa[i][pom] != '#')
					{
						znalezione_miasto =  mapa[i][pom] + znalezione_miasto;
						--pom;
					}
					dane.miasto= znalezione_miasto;
				}
				else if (j< szerokosc-1 && isalpha(mapa[i][j +1]) != 0 || (j < szerokosc - 1 && isdigit(mapa[i][j + 1])))// w prawo
				{
					String znalezione_miasto = "";
					int pom = j + 1;
					while (pom <= szerokosc-1 && mapa[i][pom] != '.' && mapa[i][pom] != '#')
					{
						znalezione_miasto = znalezione_miasto+ mapa[i][pom];
						++pom;
					}
					dane.miasto = znalezione_miasto;
				}
				else if (i >0 && isalpha(mapa[i-1][j]) != 0 || (i > 0 && isdigit(mapa[i-1][j])))// w gore
				{
					String znalezione_miasto = "";
					int pom = j;
					while (pom >= 0 && mapa[i-1][pom] != '.' && mapa[i-1][pom] != '#')
					{
						--pom;
					}
					pom++;
					while (pom <= szerokosc - 1 && mapa[i-1][pom] != '.' && mapa[i-1][pom] != '#')
					{
						znalezione_miasto = znalezione_miasto + mapa[i-1][pom];
						++pom;
					}
					dane.miasto = znalezione_miasto;
				}
				else if (i < wysokosc-1 && isalpha(mapa[i + 1][j]) != 0 || (i < wysokosc - 1 && isdigit(mapa[i + 1][j])))// w dol
				{
					String znalezione_miasto = "";
					int pom = j;
					while (pom >= 0 && mapa[i +1][pom] != '.' && mapa[i + 1][pom] != '#')
					{
						--pom;
					}
					pom++;
					while (pom <= szerokosc - 1 && mapa[i + 1][pom] != '.' && mapa[i + 1][pom] != '#')
					{
						znalezione_miasto = znalezione_miasto + mapa[i + 1][pom];
						++pom;
					}
					dane.miasto = znalezione_miasto;
				}
				else if (i > 0 && j>0 && isalpha(mapa[i - 1][j-1]) != 0 || (i > 0 && j > 0 && isdigit(mapa[i - 1][j-1])))// gora-lewo
				{
					String znalezione_miasto = "";
					int pom = j;
					while (pom >= 0 && mapa[i - 1][pom-1] != '.' && mapa[i - 1][pom-1] != '#')
					{
						znalezione_miasto = mapa[i - 1][pom-1] + znalezione_miasto;
						--pom;
					}
					dane.miasto = znalezione_miasto;
				}
				else if (i < wysokosc-1 && j > 0 && isalpha(mapa[i + 1][j - 1]) != 0 || (i < wysokosc - 1 && j > 0 && isdigit(mapa[i + 1][j - 1])))// dol-lewo
				{
					String znalezione_miasto = "";
					int pom = j;
					while (pom >= 0 && mapa[i + 1][pom - 1] != '.' && mapa[i + 1][pom - 1] != '#')
					{
						znalezione_miasto = mapa[i + 1][pom - 1] + znalezione_miasto;
						--pom;
					}
					dane.miasto = znalezione_miasto;
				}
				else if (i > 0 && j < szerokosc-1 && isalpha(mapa[i - 1][j + 1]) != 0 || (i > 0 && j < szerokosc - 1 && isdigit(mapa[i - 1][j + 1])))// gora-prawo
				{
					String znalezione_miasto = "";
					int pom = j;
					while (pom >= 0 && mapa[i - 1][pom + 1] != '.' && mapa[i - 1][pom + 1] != '#')
					{
						znalezione_miasto =  znalezione_miasto+ mapa[i - 1][pom + 1];
						++pom;
					}
					dane.miasto = znalezione_miasto;
				}
				else if (i < wysokosc-1 && j < szerokosc - 1 && isalpha(mapa[i + 1][j + 1]) != 0 || (i < wysokosc - 1 && j < szerokosc - 1 && isdigit(mapa[i + 1][j + 1])))// dol-prawo
				{
					String znalezione_miasto = "";
					int pom = j;
					while (pom >= 0 && mapa[i + 1][pom + 1] != '.' && mapa[i + 1][pom + 1] != '#')
					{
						znalezione_miasto = znalezione_miasto + mapa[i + 1][pom + 1];
						++pom;
					}
					dane.miasto = znalezione_miasto;
				}
				miasta.push(dane);
			}
		}
	}
}
struct Punkt {
	int x, y,odleglosc;
};
void bfs(int tabX, int tabY, char** board, int wysokosc, int szerokosc, Vector<int>& dlugosci, Vector<String>& _miasta, Vector<Dane>& miasta) {
	
	Punkt start;
	start.x = tabX;
	start.y = tabY;
	start.odleglosc = 0;
	Queue<Punkt>Q;
	Q.push(start);
	bool** visited = new bool* [wysokosc];
	for (int i = 0; i < wysokosc; i++) {
		visited[i] = new bool[szerokosc];
		for (int j = 0; j < szerokosc; ++j)
		{
			visited[i][j] = false;
		}
	}
	visited[start.y][start.x] = true;

	while (Q.empty() == false)
	{
		Punkt pot;
		pot = Q.front();
		Q.pop();
		if (board[pot.y][pot.x] == '*'&&(pot.x!=start.x||pot.y!=start.y))
		{
			_miasta.push(odczytanie_miasta(_miasta, miasta, pot.x, pot.y));
			dlugosci.push(pot.odleglosc);
		}
		else
		{
			if (pot.y > 0 && visited[pot.y - 1][pot.x] == false && (board[pot.y - 1][pot.x] == '#'|| board[pot.y - 1][pot.x] == '*'))
			{
				Punkt pot2;
				pot2.y = pot.y - 1;
				pot2.x = pot.x;
				pot2.odleglosc = pot.odleglosc + 1;
				Q.push(pot2);
				visited[pot.y - 1][pot.x] = true;
				
			}
			if (pot.y < wysokosc - 1 && visited[pot.y + 1][pot.x] == false && (board[pot.y + 1][pot.x] == '#'|| board[pot.y + 1][pot.x] == '*'))
			{
				Punkt pot2;
				pot2.y = pot.y + 1;
				pot2.x = pot.x;
				pot2.odleglosc = pot.odleglosc + 1;
				Q.push(pot2);
				visited[pot.y + 1][pot.x] = true;
				;
			}
			if (pot.x > 0 && visited[pot.y][pot.x - 1] == false && (board[pot.y][pot.x - 1] == '#'|| board[pot.y][pot.x - 1] == '*'))
			{
				Punkt pot2;
				pot2.y = pot.y;
				pot2.x = pot.x - 1;
				pot2.odleglosc = pot.odleglosc + 1;
				Q.push(pot2);
				visited[pot.y][pot.x - 1] = true;
				
			}
			if (pot.x < szerokosc - 1 && visited[pot.y][pot.x + 1] == false && (board[pot.y][pot.x + 1] == '#'|| board[pot.y][pot.x + 1] == '*'))
			{
				Punkt pot2;
				pot2.y = pot.y;
				pot2.x = pot.x + 1;
				pot2.odleglosc = pot.odleglosc + 1;
				Q.push(pot2);
				visited[pot.y][pot.x + 1] = true;
				
			}
		}
		
		
	}
}

String odczytanie_miasta(Vector<String>& _miasta, Vector <Dane>& miasta,int x, int y)
{
	for (int i = 0; i < miasta.size(); ++i)
	{
		if (miasta[i].lokalizacja[0] == y && miasta[i].lokalizacja[1] == x)return miasta[i].miasto;
	}
	return "";
}



