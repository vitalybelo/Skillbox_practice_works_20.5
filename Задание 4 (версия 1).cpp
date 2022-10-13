#include <iostream>
#include "class_atm.h"
using namespace std;

/**
 * Реализована работа банкомата с полноценным подбором банкнот.
 * Напилил класс ATM который инициализируется одним числом = количество банкнот
 * Сначала случайным подбором заполняются слоты с банкнотами от 5000 до 100
 * Далее реализована выдача по запрашиваемой сумме, если в банкомате есть
 * банкноты для подбора и сумма кратная достоинству банкнот - сумма выдается.
 * В случае если выдать сумму невозможно, предлагается максимально близкая сумма
 * которую банкомат может выдать - при повторном вводе этой суммы ее можно получить.
 *
 * Данные о количестве банкнот в банкомате хранятся в бинарном файле ../data/atm_pool.bin
 * При каждой операции выдачи, сначала данные загружаются из файла, а после успешной
 * операции выдачи - обновляются - записываются в файл.
 *
 * нужна папка data/ в каталоге где лежат *.срр
 */
int main() {
    setlocale(LC_ALL, "RUS");

    ClassATM atm_client (1000);

    // загрузка банкомата
    atm_client.randomATM_pool();
    atm_client.printATM_status();

    // выдача из банкомата
    long amount;
    do {
        cout << "Введите сумму выдачи (0 - выход): ";
        cin >> amount;
        if (amount > 0) {

            if (atm_client.issuanceByATM(amount)) {
                // выдача успешная
                cout << "\n\tЗабери деньги в течение 30 секунд\n\n";
                cout << "Доступно для выдачи: " << atm_client.getTotalAmount() << endl;
            } else {
                // выдача невозможна, предлагаем сумму которую можно выдать
                cout << "\n\tНевозможно выдать сумму: " << amount;
                cout << "\n\tПодходящая сумма для выдачи " << atm_client.getAmount() << "\n\n";
            }
        }
    } while (amount != 0);

    return 0;
}

