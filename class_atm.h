#ifndef SKILLBOX_PRACTICE_WORKS_20_5_CLASS_ATM_H
#define SKILLBOX_PRACTICE_WORKS_20_5_CLASS_ATM_H
#pragma once
#include <iostream>
#include <fstream>
#include <random>
using namespace std;

class ClassATM {

private:

    const string filename = "../data/atm_pool.bin";                          // имя бекап файла
    int atm_stack;                                                           // общее максимальное количество банкнот
    int banknotes[6] = {5000,2000,1000,500,200,100};  // номиналы банкнот
    int banknotes_pool[6]{};                                                 // количество банкнот каждого номинала
    int size_pool;                                                           // количество слотов для банкнот
    long total_amount;                                                       // остаток средств в банкомате
    long amount;                                                             // сумма запроса для одноразовой выдачи

public:

    explicit ClassATM (int atm_stack) {
        ClassATM::resetATM_pool();
        ClassATM::atm_stack = atm_stack;
        size_pool = sizeof(banknotes) / sizeof (int);
        total_amount = 0;
        amount = 0;
    }

    void resetATM_pool () {
        for (int i = 0; i < size_pool; i++)
            banknotes_pool[i] = 0;
    }

    void backupATM_pool () {
        ofstream fileWriter(filename, ios::binary);;
        if (fileWriter.is_open()) {
            for (int i = 0; i < size_pool; i++)
                fileWriter.write((char*)&banknotes_pool[i],sizeof (int));
        }
        fileWriter.close();
    }

    void restoreATM_pool () {
        ifstream fileReader(filename, ios::binary);
        if (fileReader.is_open()) {
            int i = 0;
            while (i < size_pool || !fileReader.eof()) {
                fileReader.read((char*)&banknotes_pool[i++], sizeof (int));
            }
        }
        fileReader.close();
    }

    void randomATM_pool() {
        random_device rd;
        mt19937_64 gen(rd());
        uniform_int_distribution<> dist(0, (size_pool - 1));

        for (int i = 0; i < atm_stack; i++)
            banknotes_pool[dist(gen)]++;

        ClassATM::backupATM_pool();
    }

    void printATM_pool() {
        for (int i = 0; i < size_pool; i++) {
            cout << "   ";
            if (banknotes[i] < 1000) cout << " ";
            cout << banknotes[i] << " = " << banknotes_pool[i] << endl;
        }
    }

    long getTotalAmount() {
        total_amount = 0;
        ClassATM::restoreATM_pool();
        for (int i = 0; i < size_pool; i++) {
            total_amount += banknotes[i] * banknotes_pool[i];
        }
        return total_amount;
    }

    bool issuanceByATM (long request_amount) {

        ClassATM::restoreATM_pool();
        ClassATM::amount = request_amount;
        int banknotes_count[size_pool];

        // подбираем банкноты для выдачи и определяем остаток
        for (int i = 0; i < size_pool; i++) {
            banknotes_count[i] = amount / banknotes[i];      // считаем нужное количество банкнот 5000 -> 100

            if (banknotes_count[i] > banknotes_pool[i]) {    // проверяем наличие в банкомате нужных банкнот
                banknotes_count[i] = banknotes_pool[i];      // банкнот не хватает - забираем последние
                amount -= banknotes_count[i] * banknotes[i]; // вычисляем остаток для подбора других банкнот
            } else {
                amount %= banknotes[i];                      // банкнот хватает, вычисляем остаток для подбора
            }
            // отображает количество банкнот в подборе (для отладки)
            // cout << endl << banknotes[i] << " :: " << banknotes_count[i];
        }

        // если подбор банкнот под заказанную сумму успешный - осуществляем выдачу банкнот
        if (amount == 0) {
            for (int i = 0; i < size_pool; i++)
                banknotes_pool[i] -= banknotes_count[i];    // забираем из пула нужное количество банкнот
            ClassATM::backupATM_pool();
            return true;
        }
        // подбор не удачный, amount = сумме которую банкомат может выдать
        amount = request_amount - amount;   // сумма которую банкомат точно может выдать
        return false;
    }

    long getAmount() const {
        return amount;
    }

    void printATM_status () {
        cout << "Банкомат загружен:\n";
        ClassATM::printATM_pool();
        cout << "Доступно для выдачи: ";
        cout << ClassATM::getTotalAmount() << endl;
    }

};
#endif
