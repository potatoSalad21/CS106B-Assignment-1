/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "StanfordCPPLib/console.h"
#include "StanfordCPPLib/simpio.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);
bool isValid(string str);

/* Main program */

int main() {
    int num = getInteger("Enter integer: ");
    std::cout << intToString(num) << std::endl;

    string numStr = getLine("Enter a string: ");
    std::cout << stringToInt(numStr) << std::endl;

    return 0;
}

// recursively convert integer to string
string intToString(int n) {
    /* Base Cases */
    if (n == 0) return "0";
    // add negative sign
    if (n < 0) {
        return "-" + intToString(-n);
    }
    if (n < 10) {
        return string() + char(n + '0');
    }

    return intToString(n / 10) + intToString(n % 10);
}

// validate integer input
bool isValid(string str) {
    if (str == "") return false;

    int idx = str[0] == '-' ? 1 : 0;
    for (int i = idx; i < str.length(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }

    return true;
}

// recursively convert string to VALID integers
int stringToInt(string str) {
    // base case
    if (str == "") return 0;

    // validate string
    if (!isValid(str)) {
        std::cout << "Invalid number input" << std::endl;
        return -1;
    }

    // check if negative
    if (str[0] == '-') {
        return -stringToInt(str.substr(1));
    }

    return str[str.length() - 1] - '0' + 10 * stringToInt(str.substr(0, str.length()-1));
}
