#include <iostream>
#include <fstream>
#include "Employee.h"
using namespace std;

int main() {

    setlocale(LC_ALL, "RUS");

    string firstName, lastName, payDate;
    ofstream fileWriter("../data/employee.data", ios::in | ios::app);

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

    cout << "Entry payment amount: ";
    int payAmount;
    cin >> payAmount;

    Employee employee(firstName, lastName, payDate, payAmount);
    employee.saveFileRecord(fileWriter);

    fileWriter.close();
    return 0;
}
