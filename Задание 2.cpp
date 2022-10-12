#include <iostream>
#include <random>
#include <fstream>
#include <ctime>
using namespace std;

/**
 * Картинки добавляются в файл, не стирая предыдущие. Каждая "казяка-базяка"
 * подписывается датой и временем. Есть ограничение для введенных ширины и высоты
 * = 250, просто так, из й. Вместо нулей и единичек - пробелы и звездочки.
 * Случайные значения выбираются из библиотеки random в диапазоне dist().
 * Значения не детерминированные
 *
 * нужна папка data/ в каталоге где лежат *.срр
 */
int main() {
    setlocale(LC_ALL, "RUS");

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0,1);

    int pic_width;
    cout << "Entry picture width: ";
    cin >> pic_width;

    int pic_height;
    cout << "Entry picture height: ";
    cin >> pic_height;

    // немного ограничим фантазии художника
    pic_width = min(pic_width, 250);
    pic_height = min(pic_height, 250);

    ofstream fileWriter("../data/picture.txt",ios::app);
    if (fileWriter.is_open()) {
        for (int j = 0; j < pic_height; j++) {
            for (int i = 0; i < pic_width; i++) {
                fileWriter << (dist(gen) ? '*' : ' ');
            }
            fileWriter << endl;
        }
        time_t now = time(0);
        fileWriter << "Picture size: " << pic_width << " * " << pic_height << endl;
        fileWriter << "Finished at: " << ctime(&now) << endl << endl;
    }
    if (fileWriter.good())
        cout << "Record successful. Asta La Vista.\n";

    fileWriter.close();
    return 0;
}
