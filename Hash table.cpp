#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
class item {
public:
    string key;
    T value;
    item() {};
    ~item() {};
    friend bool& operator==(const item<T>& dane_1, const item<T>& dane_2);
};
template <typename T>
bool& operator==(const item<T>& dane_1, const item<T>& dane_2) {
    bool check = dane_1.key == dane_2.key;
    return check;
}
template <typename T>
class HashMap {
private:
    vector<item<T>>** array;
    vector<item<T>>** arr;
    unsigned int maxsize;
    unsigned int size;
    unsigned int l_size = 0;
    unsigned int Max_l_size = 0;
    int hash(string key) {
        size_t h = 0;
        for (int i = 0; i < key.length(); i++) {
            //h += int(key.at(i)) * pow(31, (6 - i + 1));
            h = h * 31 + key.at(i);
        }
        return h % maxsize;
    }
    void rehash() {
        unsigned int tmp_s = size;
        maxsize = maxsize * 2;
        arr = new vector<item<T>>*[maxsize];
        for (unsigned int i = 0; i < size; i++) arr[i] = array[i];
        for (tmp_s; tmp_s < maxsize; tmp_s++) arr[tmp_s] = nullptr;
        delete[] array;
        array = arr;
        /*
        auto temp = array;
        unsigned int tmp_s = maxsize;
        size = 0, maxsize = maxsize * 2;
        for (unsigned int i = 0; i < maxsize; i++) array[i] = nullptr;
        for (unsigned int i = 0; i < tmp_s; i++) {
            if (temp[i] != nullptr) for (auto v : *temp[i]) Dodaj(v.key, v.value);
        }
        */
        /*
        arr = new vector<item<T>>*[maxsize];
        for (unsigned int i = 0; i < maxsize; i++) arr[i] = nullptr;
        for (int i = 0; i < maxsize; i++) {
            if (array[i] != nullptr) arr[i] = array[i];
        }
        size = 0;
        delete[] array;
        for (unsigned int i = 0; i < t; i++) {
            if (arr[i] != nullptr) for (auto v : *arr[i]) Dodaj(v.key, v.value);
        }
        array = arr;
        */
        /*
        maxsize = maxsize * 2;
        delete[] array;
        size = 0;
        array = new vector<item<T>>*[maxsize];
        for (unsigned int i = 0; i < maxsize; i++) array[i] = nullptr;
        for (unsigned int i = 0; i < size; i++) { 
            for (auto& v : *array[i]) Dodaj(v.key, v.value);
        }
        */
    }
    void l_sizes(int index) {
        l_size = array[index]->size();
        if (l_size > Max_l_size) Max_l_size = l_size;
    }

public:
    HashMap() {
        maxsize = 10;
        size = 0;
        array = new vector<item<T>>*[maxsize];
        for (unsigned int i = 0; i < maxsize; i++) array[i] = nullptr;
    };
    ~HashMap() {
        delete[] array;
    };
    void Dodaj(const string key, const T value) {
        int index = hash(key);
        if (size >= (maxsize * 0.75)) rehash();
        if (array[index] != nullptr) {
            for (auto& v : *array[index]) {
                if (v.key == key) {
                    v.value = value;
                    return;
                }
                item<T> temp = item<T>();
                temp.value = value;
                temp.key = key;
                array[index]->push_back(temp);
                l_sizes(index);
                return;
            }
        }
        else if (array[index] == nullptr) {
            array[index] = new vector<item<T>>;
            item<T> temp = item<T>();
            temp.value = value;
            temp.key = key;
            array[index]->push_back(temp);
            size++;
            return;
        }
    }
    item<T>* Znajdz(string key) {
        int index = hash(key);
        if (array[index] == nullptr) return nullptr;
        else for (auto v : *array[index]) if (v.key == key) return &v;
        return nullptr;
    }
    bool Usun(string key) {
        int index = hash(key);
        for (auto& v : *array[index]) {
            if (v.key == key) {
                array[index]->remove(v);
                if (array[index]->size() == 0) {
                    array[index] = nullptr;
                    size--;
                }
                return true;
            }
        }
        return false;
    }
    void Wyczysc() {
        delete[] array;
        size = 0, maxsize = 10;
        l_size = 0, Max_l_size = 0;
        array = new vector<item<T>>*[maxsize];
        for (unsigned int i = 0; i < maxsize; i++) array[i] = nullptr;
    }
    void Wyswietl() {
        int some = 0;
        cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "current_size: " << size << endl;
        cout << "max_size: " << maxsize << endl;
        cout << "table:" << endl << "{" << endl << endl;
        for (unsigned int i = 0; i < maxsize; i++) {
            if (array[i] != nullptr && some < 10) {
                cout << i << ": ";
                for (auto v : *array[i]) cout << v.key << " -> " << v.value << ", ";
                cout << endl;// << endl;
                some++;
            }
        }
        cout << "}" << endl << "stats:" << endl;
        cout << "list min size: 1" << endl;
        cout << "list max size: " << Max_l_size << endl;
        cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    }
};
string R_String() {
    static const char znaki[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string random;
    for (int i = 0; i < 6; i++) random += znaki[rand() % (sizeof(znaki) - 1)];
    return random;
}
double timer(clock_t time1, clock_t time2)
{
    double difference = (time2 - time1) / (double)CLOCKS_PER_SEC * 1000;
    return difference;
}
int main()
{
    clock_t time1, time2;
    srand(time(NULL));
    const int MO = 7;
    for (int i = 1; i <= MO; i++) {
        HashMap<int>* obj = new HashMap<int>();
        const double p1 = pow(10, i);

        time1 = clock();
        for (int i = 0; i < p1; i++) {
            obj->Dodaj(R_String(), i);
        }
        time2 = clock();

        obj->Wyswietl();
        cout << "Wyniki dla " << i << " danych: " << endl;
        cout << "Wykonanie dodawania: " << timer(time1, time2) << " milisekund." << endl;

        int hits = 0;
        const int p2 = pow(10, 4);
        time1 = clock();
        for (int i = 0; i < p2; i++) {
            if (obj->Znajdz(R_String()) != nullptr) {
                hits++;
            }
        }
        time2 = clock();

        cout << "Wykonanie szukania: " << timer(time1, time2) << " milisekund." << endl;
        cout << "Liczba trafien: " << hits << endl;

        obj->Wyczysc();
        delete obj;
    }
    return 0;
}


/*
    srand(time(NULL));
    //obj->Dodaj("aaAAaa", 1);
    //obj->Usun("aaAAaa");
    for (int i = 0; i < 10000; i++) {
        int t1 = rand() % 100000;
        obj->Dodaj(R_String(), t1);
    }
    obj->Wyswietl();
    //cout << obj->Znajdz("aaAAaa") << endl;
    obj->Wyczysc();
    obj->Wyswietl();
    getchar();
*/

/*
unsigned int tmp_s = size;
maxsize = maxsize * 2;
auto tmp = array;
arr = new list<item<T>>*[maxsize];
for (unsigned int i = 0; i < size; i++) arr[i] = array[i];
for (tmp_s; tmp_s < maxsize; tmp_s++) arr[tmp_s] = nullptr;
delete[] array;
array = arr;
*/

/*
arr = new list<item<T>>*[maxsize];
for (unsigned int i = 0; i < maxsize; i++) arr[i] = nullptr;
for (int i = 0; i < maxsize; i++) {
    if (array[i] != nullptr) arr[i] = array[i];
}
size = 0;
delete[] array;
for (unsigned int i = 0; i < t; i++) {
    if (arr[i] != nullptr) for (auto v : *arr[i]) Dodaj(v.key, v.value);
}
array = arr;
*/
/*
delete[] array;
unsigned int tmp_s = size;
size = 0;
maxsize = maxsize * 2;
array = new list<item<T>>*[maxsize];
for (unsigned int i = 0; i < maxsize; i++) array[i] = nullptr;
for (unsigned int i = 0; i < tmp_s; i++) {
    if (tmp[i] != nullptr) for (auto v : *tmp[i]) Dodaj(v.key, v.value);
}
*/
