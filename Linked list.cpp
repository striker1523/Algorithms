//ALGO2 IS1 222B LAB01
//Bartosz Sobański
//sb49402@zut.edu.pl

// https://wikizmsi.zut.edu.pl/uploads/2/22/Pklesk_linked_list.pdf
#include "pch.h"
#include <time.h>
#include <sstream>
#include <iostream>
using namespace std;
template <typename T>
class List
{
public:
	struct SNode
	{
		T data;
		SNode* next;
		SNode* prev;
	};
	void Dodaj_tail(const T& data) { // a#
		SNode* temp = new SNode();
		temp->data = data;
		temp->next = nullptr;
		if (tail == nullptr)
		{
			temp->prev = nullptr;
			tail = head = temp;
		}
		else
		{
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
		size++;
	}
	void Dodaj_head(const T& data) { // b#
		SNode* temp = new SNode();
		temp->data = data;
		temp->next = head;
		temp->next = nullptr;
		if (head == nullptr)
		{
			temp->next = nullptr;
			tail = head = temp;
		}
		else
		{
			temp->next = head;
			head->prev = temp;
			head = temp;
		}
		size++;
	}
	void usun_tail() { // c#
		SNode* temp = tail;
		if (tail == nullptr) {
			return;
		}
		else if (size == 1) {
			head = tail = nullptr;
			delete temp;
			size--;
		}
		else {
			tail = tail->prev;
			delete temp;
			size--;
			if (tail != nullptr) {
				tail->next = nullptr;
			}
		}
	}
	void usun_head() { // d#
		SNode* temp = head;
		if (head == nullptr) {
			return;
		}
		else if (size == 1) {
			head = tail = nullptr;
			delete temp;
			size--;
		}
		else {
			head = head->next;
			delete temp;
			size--;
			if (head != nullptr) {
				head->prev = nullptr;
			}
		}
	}
	SNode* Wyswietl_index(const unsigned int& index) { // e#
		SNode* temp = new SNode();
		temp = head;
		if (head == nullptr) {
			cout << "Lista jest pusta!" << endl;
		}
		else if (index >= size || index < 0) {
			cout << "Wskazany indeks jest poza lista!" << endl;
		}
		else if (index == 0) {

			//cout << temp->data;
			return head;
		}
		else {
			for (int i = 0; i < index; i++) {
				temp = temp->next;
			}
			//cout << temp->data;
			return temp;
		}
	}
	void Zamien_index(const unsigned int& index, T change) { // f#
		if (index >= size) {
			return;
		}
		else {
			SNode* temp = Wyswietl_index(index);
			if (temp) temp->data = change;
			else return;
		}
	}
	SNode* Znajdz(const T& data) // g# 
	{
		SNode* temp = head;
		while (data != temp->data) {
			if (temp == tail) {
				//cout << "Tego elementu nie ma na liscie: " << data;
				return nullptr;
			}
			else temp = temp->next;
		}
		if (temp->data == data) {
			return temp;
		}
		else return nullptr;
	}
	bool Znajdz_usun(const T& data) // h#
	{
		SNode* temp = head;
		while (temp->data != data) {
			if (temp == tail) {
				return false;
			}
			temp = temp->next;
		}
		if (temp->data == data) {
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			size--;
			return true;
		}
	}
	void usun() { // j#
		SNode* temp = head;
		if (head == nullptr) {
			return;
		}
		else if (size == 1) {
			head = tail = nullptr;
			delete temp;
			size--;
		}
		else {
			while (head != nullptr) {
				head = head->next;
				size--;
			}
			if (head != nullptr) {
				head->prev = nullptr;
			}
		}
		delete temp;
	}
	string Informacja() { // k#
		string info = "Ilosc obiektow w liscie : " + to_string(size);
		return info;
	}
	void Wyswietl() {
		SNode* node = head;
		while (node != nullptr) {
			cout << "[ " << node->data.field_1 << " - " << node->data.field_2 << " ]";
			node = node->next;
		}
	}
private:
	SNode* head;
	SNode* tail;
	unsigned int size;
};

struct object {
	int field_1;
	char field_2;
	object() {};
	object(const int& I_field_1, const char& C_field_2) {
		field_1 = I_field_1;
		field_2 = C_field_2;
	}
	friend ostream& operator<<(ostream& out, const object& data);
};
ostream& operator<<(ostream& result, const object& data) {
	result << "[ " << data.field_1 << " - " << data.field_2 << " ]" << endl;
	return result;
}
bool& operator!=(const object& dane_1, const object& dane_2) {
	bool check = (dane_1.field_1 != dane_2.field_1 || dane_1.field_2 != dane_2.field_2);
	return check;
}

bool& operator==(const object& dane_1, const object& dane_2) {
	bool check = dane_1.field_1 == dane_2.field_1 && dane_1.field_2 == dane_2.field_2;
	return check;
}

double timer(clock_t time1, clock_t time2)
{
	double difference = (time2 - time1) / (double)CLOCKS_PER_SEC*1000;
	return difference;
}

int main()
{
	List<object>* obj = new List<object>();
	srand(time(NULL));
	clock_t time1, time2;
	const int Exec = 6;
	for (int i = 1; i <= Exec;i++) {
		const int n = pow(10, i); 

		cout << "Dodaje " << n << " obiektow." << endl;

		time1 = clock();
		for (int i = 0; i < n; i++) {
			int t1 = rand() % 10000;
			char t2 = 'a' + rand() % 26;
			obj->Dodaj_tail(object(t1, t2));
		}
		time2 = clock();
		cout << "Wykonanie: " << timer(time1, time2) << " milisekund." << endl;
		cout << "Sredni czas wykonania: " << timer(time1, time2)/n << " milisekund." << endl;
		cout << obj->Informacja() << endl << endl;


		const int m = pow(10, 3);
		cout << "Szukam i usuwam " << m << " losowych obiektow." << endl;
		time1 = clock();
		for (int i = 0; i < m; i++) {
			int t1 = rand() % 10000;
			char t2 = 'a' + rand() % 26;
			obj->Znajdz_usun(object(t1, t2));
		}
		time2 = clock();
		cout << "Wykonanie: " << timer(time1, time2) << " milisekund." << endl;
		cout << "Sredni czas wykonania: " << timer(time1, time2) / m << " milisekund." << endl;
		cout << obj->Informacja() << endl << endl << endl << endl;

	}
	time1 = clock();
	cout << "Kasuje wszystkie obiekty z listy." << endl;							// CZYSZCZENIE LISTY
	obj->usun();
	time2 = clock();
	cout << "Wykonanie: " << timer(time1, time2) << " milisekund." << endl;
	cout << obj->Informacja() << endl << endl << endl;

	delete obj;
	return 0;
}