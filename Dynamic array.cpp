#include "pch.h"
#include <iostream>
#include <time.h>
#include <sstream>
#include <cstdlib> 
using namespace std;

template <class T>
class Dynamo
{
private:
	T* tablica;															// %%%%%%%%%% Przy dodawaniu z nową tablicą
	unsigned int size;
	unsigned int maxsize;
	unsigned int count = 0;
	const static int multiplier = 2;
public:
	Dynamo() {};
	~Dynamo() {};
	//T operator [] (unsigned int index);
	Dynamo(const unsigned int D_size) {
		maxsize = D_size;
		tablica = new T[maxsize];
		size = 0;
	}
	void Dodaj(const T& data) {											// -A
		if (size == maxsize) {
			maxsize = maxsize * multiplier;
			T* tab = new T[maxsize];
			for (int i = 0; i < size; i++) {
				tab[i] = tablica[i];
			}
			delete[] tablica;
			tablica = tab;
			count++;
			
			// %%%%%%%%%% Z Reallocem
			/*
			maxsize = maxsize * multiplier;
			tablica = (T*)realloc(tablica, maxsize * sizeof(T));
			count++;
			*/
		}
		size++;
		tablica[size - 1] = data;
	}
	T& Indeks_w(const unsigned int index) {										// -B
		if (index >= size) abort();
		return tablica[index];
	}
	void Indeks_z(const unsigned int index, T new_data) {				// -C
		if (index >= size) abort();
		else tablica[index] = new_data;
	}
	void Czysc() {														// -D
																		// Zerowanie tablicy do stanu poczatkowego
		delete[] tablica;
		size = 0, count = 0, maxsize = 1;
		tablica = new T[maxsize];
																		// Samo usuwanie elementow tablicy
	}
	string Reprezentacja() {											// -E
		string info = "Dane w tablicy: " + to_string(size) +
			"\nRozmiar tablicy: " + to_string(maxsize) +
			"\nTablica zostala powiekszona " + to_string(count) + " razy";
		return info;
	}
	void Bubble() {														// -F
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size-1; j++) {
				if (tablica[j] > tablica[j+1]) swap(tablica[j], tablica[j+1]);
			}
		}
	}
	void Wyswietl() {													// WYSWIETLANIE
		for (unsigned int i = 0; i < size; i++) cout << tablica[i] << " ";
		cout << endl;
	}
};
int main()
{
	Dynamo<unsigned int>* array = new Dynamo<unsigned int>(1);
	srand(time(NULL));
	clock_t time1, time2, elem1, elem2;
	const double rzad = 7;
	const double rozmiar = pow(10, rzad);

	time1 = clock();
	double max_elem = 0.0, amortized = 0.0, n = 0;
	for (int i = 0; i < rozmiar; i++) {
		int random = rand() % 1000;
		elem1 = clock();
		array->Dodaj(random);
		elem2 = clock();
		double elem_time = elem2 - elem1;
		if (elem_time > max_elem) {
			max_elem = elem_time;
			amortized += max_elem;
			cout << "Nowy najgorszy czas " << max_elem << " ms, dla elementu o indeksie: " << i << endl;
			n++;
		}
	}
	time2 = clock();
	cout << endl << array->Reprezentacja() << endl;
	double result = time2 - time1;
	cout << "Calkowity czas dodawania elementow: " << result / 1000 << " s" << endl;
	cout << "Zamortyzowany czas pesymistyczny: " << (amortized / n) / 1000 << " s" << endl;
	array->Czysc();
	delete array;
	return 0;
}
