#include <iostream>
#include <fstream>
#include "Employee.h"
using namespace std;

/**
 * Напросился класс, худенький но местами симпатичный.
 * Реализована полная проверка вводимой даты, включая дни
 * нужна папка data/ в каталоге где лежат *.срр
 */
int main() {

    setlocale(LC_ALL, "RUS");

    string firstName, lastName, payDate;
    ofstream fileWriter("../data/employee.data", ios::out | ios::app);

    cout << endl;
    cout << "Entry employee name: ";
        cin >> firstName;

    cout << "Entry employee surname: ";
        cin >> lastName;

    bool validDate;
    do {
        cout << "Entry payment date (dd.mm.yyyy): ";
        validDate = Employee::getDateString(payDate);
        if (!validDate)
            cout << "Invalid date format. Please repeat.\n";
    } while (!validDate);

    int payAmount;
    cout << "Entry payment amount: ";
        cin >> payAmount;

    Employee employee(firstName, lastName, payDate, payAmount);
    employee.saveFileRecord(fileWriter);

    fileWriter.close();
    return 0;
}
