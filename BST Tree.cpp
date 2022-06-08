#include "pch.h"
#include <time.h>
#include <sstream>
#include <iostream>
using namespace std;
template <typename T>
class Drzewko
{
private:
	unsigned int licz = 0;
public:
	struct BST_Bush {
		T leaf;
		unsigned int index;
		BST_Bush* left, * right;
	};
	BST_Bush* BST_root = nullptr;
	/*									[A]									*/
	void Dodaj(T wartosc) { 
		Dodaj(&BST_root, wartosc);
	}
	void Dodaj(BST_Bush** root,const T& wartosc) {
		if (*root == nullptr) {
			BST_Bush* temp = new BST_Bush();
			temp->leaf = wartosc;
			temp->left = nullptr;
			temp->right = nullptr;
			temp->index = licz;
			licz++;
			*root = temp;
		}
		else {
			if (wartosc > (*root)->leaf) Dodaj(&(*root)->right, wartosc);
			else Dodaj(&(*root)->left, wartosc);
		}
	}
	/*									[B]									*/
	BST_Bush* Znajdz(T szukany) {
	return Znajdz(BST_root, szukany);
	}
	BST_Bush* Znajdz(BST_Bush* root, T szukany) {
		if (root == nullptr) return nullptr;
		else {
			if (szukany == root->leaf) return root; 
			else if (szukany > root->leaf) return Znajdz(root->right, szukany); 
			else return Znajdz(root->left, szukany); 
		}
	}
	/*									[C]									*/
	//////////////////////////////////////////////////////////////////////////
	/*									[D]									*/
	void preorder() {
		if (BST_root != nullptr) preorder(BST_root);
		else cout << "Drzewo jest puste.";
	}
	void preorder(BST_Bush* root) {
		if (root != nullptr) {
			cout << root->leaf << " ";
			preorder(root->left);
			preorder(root->right);
		}
	}
	/*									[E]									*/
	void inorder() {
		if (BST_root != nullptr) inorder(BST_root);
		else cout << "Drzewo jest puste.";
	}
	void inorder(BST_Bush* root) {
		if (root != nullptr) {
			inorder(root->left);
			cout << root->leaf << " ";
			inorder(root->right);
		}
	}
	/*									[F]									*/
	void Usun() {
		if (BST_root != nullptr) Usun(BST_root);
		else cout << "Drzewo juz bylo puste.";
	}
	void Usun(BST_Bush* root) {
		if (root == nullptr) return;
		else if(root != nullptr){
			Usun(root->left);
			Usun(root->right);
			delete root;
		}
		BST_root = nullptr;
		licz = 0;
	}
	/*									[G]									*/
	int Wysokosc() {
		if (BST_root != nullptr) return Wysokosc(BST_root);
		else return 0;
	}
	int Wysokosc(BST_Bush* root) {
		if (!root) return 0;
		else {
			int LewaW = Wysokosc(root->left);
			int PrawaW = Wysokosc(root->right);
			if (LewaW >= PrawaW) return LewaW + 1;
			else return PrawaW + 1;
		}
	}
	/*									[H]									*/
	void info(unsigned int ilosc) {
		string repr = "Ilosc elementow: " + to_string(licz) +
			" Wysokosc drzewa: " + to_string(Wysokosc()) + "\n";
		cout << endl << repr;
		if (BST_root != nullptr) info(BST_root, ilosc);
		else cout << "Drzewo jest puste.";
	}
	void info(BST_Bush* root,unsigned int ilosc) {
			if (root != nullptr && ilosc != 0) {
				BST_Bush* temp = new BST_Bush();
				cout << endl <<"I:("<<root->index<<")-Wartosc: " << root->leaf << " ";
				if (root->left != nullptr && root->right != nullptr) {
					cout << "L=(" << root->left->leaf << ") P=(" << root->right->leaf << ")";
				}
				else if (root->left != nullptr && root->right == nullptr) {
					cout << "L=(" << root->left->leaf << ") P=(NULL)";
				}
				else if (root->left != nullptr && root->right == nullptr) {
					cout << "L=(NULL) P=(" << root->right->leaf << ")";
				}
				else {
				cout << "L=(NULL) P=(NULL)";
				}
				ilosc--;
				info(root->left, ilosc);
				info(root->right, ilosc);
		}
	}
};
struct object {
private:
	int field_1;
	char field_2;
public:
	object() {
		field_1 = 0;
		field_2 = 0;
	};
	object(const int& I_field_1, const char& C_field_2) {
		field_1 = I_field_1;
		field_2 = C_field_2;
	}
	friend ostream& operator<<(ostream& result, const object& data) {
		result << "[" << data.field_1 << " - " << data.field_2 << "]";
		return result;
	}
	friend bool& operator >(const object& d1, const object& d2) {
		bool check = (d1.field_1 > d2.field_1);
		return check;
	}
	friend bool& operator <(const object& d1, const object& d2) {
		bool check = (d1.field_1 < d2.field_1);
		return check;
	}
	friend bool& operator ==(const object& d1, const object& d2) {
		bool check = (d1.field_1 == d2.field_1);
		return check;
	}
};
double timer(clock_t time1, clock_t time2)
{
	double difference = (time2 - time1) / (double)CLOCKS_PER_SEC * 1000;
	return difference;
}
	/*								   [MAIN]								*/
int main() {
	clock_t time1, time2;
	srand(time(NULL));
	const int MO = 7;
	for (int i = 1; i <= MO; i++) {
		//Drzewko<int>* tree = new Drzewko<int>;
		Drzewko<object>* tree = new Drzewko<object>;
		const double rzad = pow(10, i);
		time1 = clock();
		for (int i = 0; i < rzad; i++) {
			int t1 = rand() % 100000;
			char t2 = 'a' + rand() % 26;
			tree->Dodaj(object(t1, t2));
			//tree->Dodaj(t1);
		}
		time2 = clock();
		cout << "|||||||||||||||||||||||||||||||||||||||||||-Lista: " << i << "-" << endl;
		cout << "Wykonanie dodawania: " << timer(time1, time2) << " milisekund." << endl;
		cout <<endl<< "Reprezentacja BST [15 Wezlow Pre-Order]: "; tree->info(4);

		const double rzad2 = pow(10, 4);
		int hits = 0;
		time1 = clock();
		for (int i = 0; i < rzad2; i++) {
			int t1 = rand() % 100000;
			char t2 = 'a' + rand() % 26;
			if (tree->Znajdz(object(t1, t2)) != nullptr) {
				hits++;
			}
			/*
			if (tree->Znajdz(t1) != nullptr) {
				hits++;
			}
			*/
		}
		time2 = clock();
		cout <<endl<<endl<< "Wykonanie wyszukiwania: " << timer(time1, time2) << " milisekund." << endl;
		cout << "Ilosc trafien: " << hits << endl;
		cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
		tree->Usun();
		delete tree;
	}
	getchar();
	return 0;
}
