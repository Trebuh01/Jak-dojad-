#pragma once
#include <iostream>
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>
#include "String.h"

#include "Kolejka_P.h"
#include "Klasy.h"

using namespace std;
class Graph {
private:
    Vector<Wierzcholek> wierzcholki; //lista wierzcholkow
public:
    Graph() {
    }
    // Dodanie nowego wierzcho³ka o podanej nazwie
    void addVertex(String name) {
        Wierzcholek w;
        w.nazwa = name;
        wierzcholki.push(w);
    }
    // Dodanie nowej krawêdzi pomiêdzy wierzcho³kami o podanych nazwach i czasie
    void addEdge(String source, String dest, int time) {
        int u = findVertexIndex(source);
        int v = findVertexIndex(dest);
        wierzcholki[u].pair.push({ v, time });
    }
    // Dodanie nowego lotu pomiêdzy wierzcho³kami o podanych nazwach i czasie lotu
    void addFlight(String source, String dest, int time) {
        int u = findVertexIndex(source);
        int v = findVertexIndex(dest);
        Flight f = { wierzcholki[v].nazwa, time };
        wierzcholki[u].flights.push(f);
    }
    // Wyszukanie indeksu wierzcho³ka o podanej nazwie
    int findVertexIndex(String name) {
        for (int i = 0; i < wierzcholki.size(); i++) {
            if (wierzcholki[i].nazwa==name) {
                return i;
            }
        }
        return -1;
    }
    
    Vector<std::pair<String, int>> shortestPath(String source, String dest) {
        int n = wierzcholki.size();
        Vector<int> distance(n, std::numeric_limits<int>::max());
        Vector<int> prev(n, -1);
        PriorityQueue<std::pair<int, int>, std::greater<>> pq;
        //std::priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        int srcIndex = findVertexIndex(source);
        int destIndex = findVertexIndex(dest);
        distance[srcIndex] = 0;
        pq.push({ 0, srcIndex });
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            for (auto& p : wierzcholki[u].pair) {
                int v = p.first;
                int w = p.second;
                if (distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    prev[v] = u;
                    pq.push({ distance[v], v });
                }
            }
            for (auto& f : wierzcholki[u].flights) {
                int v = findVertexIndex(f.destination);
                int w = f.time;
                if (distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    prev[v] = u;
                    pq.push({ distance[v], v });
                }
            }
        }
        Vector<std::pair<String, int>> path;
        if (distance[destIndex] < std::numeric_limits<int>::max()) {
            for (int v = destIndex; v != -1; v = prev[v]) {
                path.push({ wierzcholki[v].nazwa, distance[v] });
            }
            std::reverse(path.begin(), path.end());
        }
        return path;
    }
    void printGraph() {
        for (int i = 0; i < wierzcholki.size(); i++) {
            std::cout << "Wierzcholek " << wierzcholki[i].nazwa << ":\n";
            for (int j = 0; j < wierzcholki[i].pair.size(); j++) {
                cout << " " << wierzcholki[i].nazwa << " -> ";
                cout << wierzcholki[wierzcholki[i].pair[j].first].nazwa << " (";
                //cout << wierzcholki[i].pair[j].first << ")\n";
                cout<< wierzcholki[i].pair[j].second << ")\n";
            }
        }
    }
    ~Graph() {}
};


