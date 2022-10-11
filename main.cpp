#include <iostream>
#include <fstream>
#include <random>
using namespace std;

/**
 *
 * нужна папка data/ в каталоге где лежат *.срр
 */
int main() {
    setlocale(LC_ALL, "RUS");
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<> dist(0,5);

    int atm_dimension = 1000;
    int banknotes[] {100,200,500,1000,2000,5000};
    int banknotes_pool[] {0,0,0,0,0,0};

    for (int i = 0; i < atm_dimension; i++) {
        int index = dist(gen);
        banknotes_pool[index]++;
    }




    return 0;
}
