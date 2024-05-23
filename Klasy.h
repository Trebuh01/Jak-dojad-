#pragma once
#include "String.h"
#include "Vector.h"

class Pair
{
public:
    Pair() : first(0), second(0) {}
    //Pair(int first, int second): first(first), second(second) {}
    Pair(int _first, int _second)
    {
        first = _first;
        second = _second;
    }

    ~Pair() {}

    int first;
    int second;
};

class Flight
{
public:
    Flight() : destination(""), time(0) {}
    //Flight(String destination, int time) : destination(destination), time(time) {}
    Flight(String _destination, int _time)
    {
        destination = _destination;
        time = _time;
    }
    ~Flight() {}

    String destination;
    int time;
};

class Wierzcholek
{
public:
    Wierzcholek() : nazwa(""), pair(), flights() {}
    ~Wierzcholek() {}

    Wierzcholek& operator=(const Wierzcholek& other) {
        if (this != &other) {//sprawzam czy wskasuja na ten sam obiekt w pamieci

            nazwa = other.nazwa;
            pair = other.pair;
            flights = other.flights;

        }
        return *this;
    }

    String nazwa;
    Vector<Pair> pair;
    Vector<Flight> flights;
};