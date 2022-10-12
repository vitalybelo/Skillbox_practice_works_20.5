#ifndef SKILLBOX_PRACTICE_WORKS_20_5_EMPLOYEE_H
#define SKILLBOX_PRACTICE_WORKS_20_5_EMPLOYEE_H
#pragma once
#include <iostream>
#include <fstream>
#include <utility>
using namespace std;

class Employee {

private:
    string firstName;
    string lastName;
    string paymentDate;
    int paymentAmount;

public:

    Employee(string &firstName, string &lastName, string &paymentDate, int paymentAmount = 0) {
        Employee::firstName = firstName;
        Employee::lastName = lastName;
        Employee::paymentDate = paymentDate;
        Employee::paymentAmount = paymentAmount;
    }

    Employee() { }

    static bool getDateString (string &date) {
        int days[] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        cin >> date;
        if (date.length() != 10) return false;
        if (date[2] != '.' && date[5] != '.') return false;

        int year = stoi(date.substr(6,4));
        if (year > 2022 || year < 0) return false;
        int month = stoi(date.substr(3,2));
        if (month < 0 || month > 12) return false;
        int day = stoi(date.substr(0,2));
        if (day <= 0 || day > days[month - 1]) return false;

        return true;
    }

    void saveFileRecord (ofstream &file) {
        if (file.is_open()) {
            file << "person: " << lastName << " " << firstName << " ";
            file << "date: " << paymentDate << " amount: " << paymentAmount << endl;
        }
    }

    const string &getFirstName() const {
        return firstName;
    }

    const string &getLastName() const {
        return lastName;
    }

    const string &getPaymentDate() const {
        return paymentDate;
    }

    int getPaymentAmount() const {
        return paymentAmount;
    }

    void setFirstName(const string &nameOne) {
        firstName = nameOne;
    }

    void setLastName(const string &nameTwo) {
        lastName = nameTwo;
    }

    void setPaymentDate(const string &payDate) {
        paymentDate = payDate;
    }

    void setPaymentAmount(int payAmount) {
        paymentAmount = payAmount;
    }
};


#endif //SKILLBOX_PRACTICE_WORKS_20_5_EMPLOYEE_H
