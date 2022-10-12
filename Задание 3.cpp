#include <iostream>
#include <fstream>
#include <vector>
#include <random>
using namespace std;

/**
 * Постановка задачи предполагает что рыбалка выглядит примерно так:
 * Часам к 12.00 эдак дня рыбак подгребает к берегу на Bentley Limited Edition
 * На берегу терпеливо ожидает официант в ластах, маске и с подводным ружьем
 * Официант вежливо принимает заказ у рыбака, прыгает в воду, какое то время
 * он там плавает, и выносит на берег улов, строго в соответствие с заказом !!
 * НО ....
 * У нас рыбалка реализована так. Рыбак оформляет заказ, вводит номер рыбы
 * которую желает поймать. Но в процесс вмешиваются водные демиурги, которые
 * странным и случайным образом подменяют улов. Как говорится "человек полагает,
 * а Бог располагает". В результате - поймали что попалось на крючок. Но, судьба
 * может и наградить, и если ваш выбор и божий промысел совпали, вы получаете
 * поздравительную открытку. Погнали ))
 *
 * нужна папка data/ в каталоге где лежат *.срр
 */
int main() {
    setlocale(LC_ALL, "RUS");
    random_device rd;
    mt19937 gen(rd());

    int counter = 1;
    vector<string> fishTank;

    // считываем рыбное меню в аквариум
    ifstream fileReader("../data/river.txt",ios::in);
    if (fileReader.is_open()) {
        string fish;
        string space = "\t";
        cout << "We have the following selection of fish today (menu):\n";
        while (fileReader >> fish) {
            cout << space << counter++ << ". " << fish << endl;
            fishTank.push_back(fish);
            space += " ";
        }
    } else {
        return -1; // файл с рыбами не открылся - домой
    }
    fileReader.close();

    // собственно игра в рыбалку
    uniform_int_distribution<> dist(0,(int)(fishTank.size() - 1));
    ofstream fileWriter("../data/basket.txt", ios::out | ios::app);

    if (fileWriter.is_open()) {
        counter = 0;
        int my_choice;
        do {
            cout << "Entry fish number what you going to catch (0 - quit): ";
            cin >> my_choice;
            if (my_choice != 0) {
                int god_choice = dist(gen);
                if (my_choice == god_choice) {
                    cout << "\tLucky you got what you wanted: "  << fishTank[god_choice] << endl;
                } else {
                    cout << "\tMan proposes, God disposes. You catch: " << fishTank[god_choice] << endl;
                }
                fileWriter << fishTank[god_choice] << endl;
                counter++;
            }
        } while (my_choice != 0);

        time_t now = time(0);
        fileWriter << "Fish caught: " << counter << endl;
        fileWriter << "Finished at: " << ctime(&now) << endl << endl;
    } else {
        cerr << "Output file basket.txt: file open error.\n";
    }

    fileWriter.close();
    return 0;
}
