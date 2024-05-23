#define _CRT_SECURE_NO_WARNINGS 
#include "String.h"
#include <iostream>
#include <string.h>
    // Konstruktor
    String::String() : m_data(nullptr), m_size(0) {}

    // Konstruktor z jednym argumentem
    String::String(const char* str) {
        m_size = strlen(str);
        m_data = new char[m_size + 1];
        strcpy(m_data, str);
    }

    // Konstruktor kopiuj�cy
    String::String(const String& other) {
        m_size = other.m_size;
        m_data = new char[m_size + 1];
        strcpy(m_data, other.m_data);
    }

    // Destruktor
    String::~String() {
        delete[] m_data;
    }

    // Funkcja zwracaj�ca rozmiar stringa
    size_t String::size() const {
        return m_size;
    }

    // Funkcja zwracaj�ca wska�nik do danych stringa
    const char* String::c_str() const {
        return m_data;
    }

    // Operator przypisania
    String& String::operator=(const String& other) {
        if (this != &other) {//sprawdzam czy wskasuja na ten sam obiekt w pamieci
            delete[] m_data;
            m_size = other.m_size;
            m_data = new char[m_size + 1];
            strcpy(m_data, other.m_data);
        }
        return *this;
    }

    // Operator dodawania string�w
    String operator+(char c, const String& str) {
        size_t new_size = str.m_size + 1;
        char* new_data = new char[new_size + 1];
        new_data[0] = c;
        strcpy(new_data + 1, str.m_data);
        String new_string(new_data);
        delete[] new_data;
        return new_string;
    }

    String String::operator+(const String& other) const {
        size_t new_size = m_size + other.m_size;
        char* new_data = new char[new_size + 1];
        strcpy(new_data, m_data);
        strcat(new_data, other.m_data);//dziala tak ze dopisuje na koniec
        String new_string(new_data);
        delete[] new_data;
        return new_string;
    }

    String String::operator+(const char& c) const {
        size_t new_size = m_size + 1;
        char* new_data = new char[new_size + 1];
        strcpy(new_data, m_data);
        new_data[m_size] = c;
        new_data[new_size] = '\0';
        String new_string(new_data);
        delete[] new_data;
        return new_string;
    }


    // Operator por�wnania string�w
    bool String::operator==(const String& other) const {
        return strcmp(m_data, other.m_data) == 0;
    }

    // Operator nier�wno�ci string�w
    bool String::operator!=(const String& other) const {
        return !(*this == other);
    }

    // Operator mniejszo�ci string�w
    bool String::operator<(const String& other) const {
        return strcmp(m_data, other.m_data) < 0;
    }

    // Operator wi�kszo�ci string�w
    bool String::operator>(const String& other) const {
        return strcmp(m_data, other.m_data) > 0;
    }

    // Operator mniejszo�ci lub r�wno�ci string�w
    bool String::operator<=(const String& other) const {
        return strcmp(m_data, other.m_data) <= 0;
    }

    // Operator wi�kszo�ci lub r�wno�ci string�w
    bool String::operator>=(const String& other) const {
        return strcmp(m_data, other.m_data) >= 0;
    }

    // Operator indeksowania
    char& String::operator[](size_t index) {
        return m_data[index];
    }

    // Funkcja zwracaj�ca znak na podanej pozycji
    char& String::at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range.");
        }
        return m_data[index];
    }

    // Funkcja przekszta�caj�ca string na liczbe calkowita
    int String::to_int() const {
        return std::atoi(m_data);
    }

    std::istream& operator>>(std::istream& in, String& str) {//czyta ci�g znak�w z wej�cia, a nast�pnie tworzy nowy obiekt klasy String na podstawie tego ci�gu za pomoc� konstruktora z jednym argumentem. zwracany jest strumie� wej�ciowy
        char buffer[4096];
        in >> buffer;
        str = String(buffer);
        return in;
    }
    std::ostream& operator<<(std::ostream& out, const String& str) {//wypisuje zawarto�� stringa na strumie� wyj�ciowy (std::ostream)
        out << str.m_data;
        return out;
    }

    

    void String::erase(size_t pos, size_t count) {
        if (pos >= m_size) {
            throw std::out_of_range("Index out of range.");
        }
        // Je�li count jest wi�ksze od liczby pozosta�ych znak�w po pozycji pos,
        // to usuwamy tylko tyle znak�w, ile jest pozosta�ych po pozycji pos.
        if (count > m_size - pos) {
            count = m_size - pos;
        }
        // Przesuwamy znaki od pozycji pos + count do pozycji pos
        for (size_t i = pos + count; i <= m_size; i++) {
            m_data[i - count] = m_data[i];
        }
        m_size -= count;
        m_data[m_size] = '\0';
    }

    String String::substr(size_t pos, size_t count) const {
        if (pos >= m_size) {
            //throw std::out_of_range("Index out of range.");
            return "";
        }
        // Je�li count jest wi�ksze od liczby pozosta�ych znak�w po pozycji pos,
        // to zwracamy tylko tyle znak�w, ile jest pozosta�ych po pozycji pos.
        if (count > m_size - pos) {
            count = m_size - pos;
        }
        // Tworzymy nowy string zawieraj�cy podci�g
        char* new_data = new char[count + 1];
        strncpy(new_data, m_data + pos, count);
        new_data[count] = '\0';
        String new_string(new_data);
        delete[] new_data;
        return new_string;
    }

    size_t String::find(const String& substr) const {
        const char* result = strstr(m_data, substr.m_data);//strstr, kt�ra zwraca wska�nik na pierwsze wyst�pienie pod�a�cucha w ci�gu. Funkcja find zwraca pozycj� pierwszego wyst�pienia pod�a�cucha, lub std::string::npos
        if (result == nullptr) {
            return std::string::npos;
        }
        return result - m_data;
    }

    bool String::empty() const {
        return m_size == 0;
    }

    size_t String::find_first_of(const char* chars) const {//Ta funkcja wyszukuje pierwsze wyst�pienie jednego z znak�w podanych w �a�cuchu chars w obiekcie String. Do tego celu wykorzystywana jest funkcja strpbrk, kt�ra zwraca wska�nik na pierwsze wyst�pienie dowolnego znaku z �a�cucha chars w ci�gu
        const char* result = strpbrk(m_data, chars);
        if (result == nullptr) {
            return std::string::npos;
        }
        return result - m_data;
    }

    size_t String::find_first_not_of(const char* charsToSkip) const {//wyszukuje pierwsze wyst�pienie znaku, kt�ry nie nale�y do podanego jako argument charsToSkip �a�cucha w obiekcie String. Algorytm iteruje po kolejnych znakach �a�cucha, sprawdzaj�c czy ka�dy z nich znajduje si� w charsToSkip. Je�li znak nie nale�y do charsToSkip, to jego pozycja zostaje zwr�cona. Gdy wszystkie znaki s� elementami charsToSkip, zwracana jest warto�� std::string::npos
        size_t i = 0;
        while (i < m_size) {
            bool skipChar = false;
            for (size_t j = 0; charsToSkip[j] != '\0'; j++) {
                if (m_data[i] == charsToSkip[j]) {
                    skipChar = true;
                    break;
                }
            }
            if (!skipChar) {
                return i;
            }
            i++;
        }
        return npos;
    }

    size_t String::find_last_not_of(const char* chars) const {//Funkcja przechodzi przez ci�g znak�w w odwrotnej kolejno�ci, a� znajdzie pierwszy znak, kt�ry nie jest obecny w ci�gu chars, lub dojdzie do pocz�tku ci�gu. Je�li znak zostanie znaleziony, funkcja zwraca jego pozycj�, a w przeciwnym przypadku zwraca npos
        if (m_data == nullptr) {
            return npos;
        }

        size_t pos = m_size;
        bool found = false;
        while (pos > 0 && !found) {
            pos--;
            found = true;
            for (size_t i = 0; chars[i] != '\0'; i++) {
                if (m_data[pos] == chars[i]) {
                    found = false;
                    break;
                }
            }
        }

        return found ? pos : npos;
    }

    size_t String::find_first_of(const char* chars, size_t pos) const {//szuka pierwszego znaku w ci�gu, kt�ry znajduje si� w podanym ci�gu znak�w chars. Funkcja rozpoczyna szukanie od pozycji pos i przeszukuje ci�g znak�w w poszukiwaniu pierwszego znaku, kt�ry znajduje si� w ci�gu chars. Je�li taki znak zostanie znaleziony, funkcja zwraca jego pozycj�, a w przeciwnym przypadku zwraca npos.
        if (pos >= m_size) {
            throw std::out_of_range("Starting position out of range.");
        }
        const char* result = std::strpbrk(m_data + pos, chars);
        if (result == nullptr) {
            return std::string::npos;
        }
        return result - m_data;
    }

    size_t String::find_last_of(const char c) const {//szuka ostatniego wyst�pienia danego znaku c w ci�gu. Funkcja przeszukuje ci�g znak�w od ko�ca i zwraca pozycj� ostatniego wyst�pienia danego znaku c
        char* p = strrchr(m_data, c);
        if (p == nullptr) {
            return std::string::npos;
        }
        return p - m_data;
    }
 

