#include <iostream>
#include "class_atm.h"
using namespace std;

/**
 * ����������� ������ ��������� � ����������� �������� �������.
 * ������� ����� ATM ������� ���������������� ����� ������ = ���������� �������
 * ������� ��������� �������� ����������� ����� � ���������� �� 5000 �� 100
 * ����� ����������� ������ �� ������������� �����, ���� � ��������� ����
 * �������� ��� ������� � ����� ������� ����������� ������� - ����� ��������.
 * � ������ ���� ������ ����� ����������, ������������ ����������� ������� �����
 * ������� �������� ����� ������ - ��� ��������� ����� ���� ����� �� ����� ��������.
 *
 * ������ � ���������� ������� � ��������� �������� � �������� ����� ../data/atm_pool.bin
 * ��� ������ �������� ������, ������� ������ ����������� �� �����, � ����� ��������
 * �������� ������ - ����������� - ������������ � ����.
 *
 * ����� ����� data/ � �������� ��� ����� *.���
 */
int main() {
    setlocale(LC_ALL, "RUS");

    ClassATM atm_client (1000);

    // �������� ���������
    atm_client.randomATM_pool();
    atm_client.printATM_status();

    // ������ �� ���������
    long amount;
    do {
        cout << "������� ����� ������ (0 - �����): ";
        cin >> amount;
        if (amount > 0) {

            if (atm_client.issuanceByATM(amount)) {
                // ������ ��������
                cout << "\n\t������ ������ � ������� 30 ������\n\n";
                cout << "�������� ��� ������: " << atm_client.getTotalAmount() << endl;
            } else {
                // ������ ����������, ���������� ����� ������� ����� ������
                cout << "\n\t���������� ������ �����: " << amount;
                cout << "\n\t���������� ����� ��� ������ " << atm_client.getAmount() << "\n\n";
            }
        }
    } while (amount != 0);

    return 0;
}

