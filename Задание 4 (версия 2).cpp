#include <iostream>
#include "class_atm.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    char comm;
    long amount, total_amount;
    ClassATM atm_client (1000);

    if (!atm_client.restoreATM_pool()) {
        cout << "Банкомат не инициализирован.\n";
        cout << "Хотите выполнить инициализацию ( y - да ) ? ";
        cin >> comm;
        if (comm != 'y') return -1;
        atm_client.randomATM_pool();
        atm_client.backupATM_pool();
        atm_client.printATM_status();
    }

    cout << "Введите команду: ";
    cin >> comm;

    switch (comm) {
        case '+':
            atm_client.randomATM_pool();
            atm_client.printATM_status();
            break;
        case '-':
            total_amount = atm_client.getTotalAmount();
            cout << "\nДоступно для выдачи: " << total_amount << endl;

            if (total_amount > 0) {
                do {
                    cout << "Введите сумму выдачи (0 - выход): ";
                    cin >> amount;
                    if (amount > 0) {

                        if (atm_client.issuanceByATM(amount)) {
                            // выдача успешная
                            total_amount = atm_client.getTotalAmount();
                            cout << "\n\tЗаберите деньги в течение 30 секунд\n\n";
                            cout << "Доступно для выдачи: " << total_amount << endl;
                        } else {
                            // выдача невозможна, предлагаем сумму которую можно выдать
                            cout << "\n\tНевозможно выдать сумму: " << amount;
                            cout << "\n\tПодходящая сумма для выдачи " << atm_client.getAmount() << "\n\n";
                        }
                    }
                } while (amount != 0 && total_amount > 0);
            } else {
                cout << "Банкомат пуст :: требуется пополнение.\n";
            }
            break;
        default:
            cout << "\nКоманда не распознана.\n";
    }

    atm_client.backupATM_pool();
    return 0;
}

