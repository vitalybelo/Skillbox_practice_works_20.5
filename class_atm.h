#ifndef SKILLBOX_PRACTICE_WORKS_20_5_CLASS_ATM_H
#define SKILLBOX_PRACTICE_WORKS_20_5_CLASS_ATM_H
#pragma once
#include <iostream>
#include <fstream>
#include <random>
using namespace std;

class ClassATM {

private:

    const string filename = "../data/atm_pool.bin";                          // ��� ����� �����
    int atm_stack;                                                           // ����� ������������ ���������� �������
    int banknotes[6] = {5000,2000,1000,500,200,100};  // �������� �������
    int banknotes_pool[6]{};                                                 // ���������� ������� ������� ��������
    int size_pool;                                                           // ���������� ������ ��� �������
    long total_amount;                                                       // ������� ������� � ���������
    long amount;                                                             // ����� ������� ��� ����������� ������

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

        // ��������� �������� ��� ������ � ���������� �������
        for (int i = 0; i < size_pool; i++) {
            banknotes_count[i] = amount / banknotes[i];      // ������� ������ ���������� ������� 5000 -> 100

            if (banknotes_count[i] > banknotes_pool[i]) {    // ��������� ������� � ��������� ������ �������
                banknotes_count[i] = banknotes_pool[i];      // ������� �� ������� - �������� ���������
                amount -= banknotes_count[i] * banknotes[i]; // ��������� ������� ��� ������� ������ �������
            } else {
                amount %= banknotes[i];                      // ������� �������, ��������� ������� ��� �������
            }
            // ���������� ���������� ������� � ������� (��� �������)
            // cout << endl << banknotes[i] << " :: " << banknotes_count[i];
        }

        // ���� ������ ������� ��� ���������� ����� �������� - ������������ ������ �������
        if (amount == 0) {
            for (int i = 0; i < size_pool; i++)
                banknotes_pool[i] -= banknotes_count[i];    // �������� �� ���� ������ ���������� �������
            ClassATM::backupATM_pool();
            return true;
        }
        // ������ �� �������, amount = ����� ������� �������� ����� ������
        amount = request_amount - amount;   // ����� ������� �������� ����� ����� ������
        return false;
    }

    long getAmount() const {
        return amount;
    }

    void printATM_status () {
        cout << "�������� ��������:\n";
        ClassATM::printATM_pool();
        cout << "�������� ��� ������: ";
        cout << ClassATM::getTotalAmount() << endl;
    }

};
#endif
