//ALGO2 IS1 222B LAB06
//Bartosz Sobański
//sb49402@zut.edu.pl

//#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

template <class T>
class Heap {
private:
	vector<T> array;
	size_t parent(size_t i) { 
		return (i - 1) / 2; 
	};
	size_t l_child(size_t i) { 
		return (i * 2) + 1; 
	};
	size_t r_child(size_t i) { 
		return (i * 2) + 2; 
	};
	void dig_up(size_t index) {
		if (index == 0) {
			return;
		}
		if (array[index] > array[parent(index)]) {
			swap(array[parent(index)], array[index]);
		}
		else return;
		dig_up(parent(index));
	}
	void dig_down(size_t index) {
		if (index > array.size()) {
			return;
		}
		size_t temp_digger = index;
		if (l_child(index) < array.size() && array[index] <= array[l_child(index)]) {
			temp_digger = l_child(index);
		}
		if (r_child(index) < array.size() && array[temp_digger] <= array[r_child(index)]) {
			temp_digger = r_child(index);
		}
		if (temp_digger != index) {
			swap(array[index], array[temp_digger]);
			dig_down(temp_digger);
		}
		return;
	}
public:
	void add(const T& data) {
		size_t temp_size = array.size();
		array.push_back(data);
		dig_up(temp_size);
		return;
	}
	T g_root() {
		if (array.size() >= 1) { 
			return array[0]; 
		}
	}
	void d_root() {
		iter_swap(array.begin(), (array.end() - 1));
		array.erase(array.end() - 1);
		dig_down(0);
	}
	void clear() {
		array.clear();
	}
	void show() {
		if (array.size() == 0) {
			cout << "Kopiec jest pusty." << endl;
			return;
		}
		else {
			for (int i = 0; i < 10; i++) {
				if (i == array.size()) {
					cout << endl << "Kopiec posiadal tylko " << i <<" elementow." << endl;
					return;
				}
				cout << "" << array[i] << ", ";
			}
			cout << endl;
		}
	}
};
double timer(clock_t time1, clock_t time2)
{
	double difference = (time2 - time1) / (double)CLOCKS_PER_SEC * 1000;
	return difference;
}
int main() {
	Heap<int>* obj = new Heap<int>();
	clock_t time1, time2;
	srand(time(NULL));
	const int MO = 7;
	for (int i = 1; i <= MO; i++) {

		const double p1 = pow(10, i);
		time1 = clock();
		for (int i = 0; i < p1; i++) {
			int t1 = rand() % 100000;
			obj->add(t1);
		}
		time2 = clock();
		obj->show();
		cout << "Wykonanie dodawania dla " << p1 << " danych = " << timer(time1, time2) << " milisekund." << endl;

		time1 = clock();
		for (int i = 0; i < p1; i++) {
			obj->d_root();
		}
		time2 = clock();
		obj->show();
		cout << "Wykonanie szukania dla " << p1 << " danych = " << timer(time1, time2) << " milisekund." << endl;

		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		obj->clear();
	}
	delete obj;
	return 0;
}