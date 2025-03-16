/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "StanfordCPPLib/console.h"
#include "StanfordCPPLib/simpio.h"
using std::string;

// recursive function for getting entry in pascal's triangle
int combinations(int n, int k) {
    if (k == 0 || k == n) return 1; // base case

    return combinations(n - 1, k - 1) + combinations(n - 1, k);
}

int main() {
    int n,k;
    while (true) {   // validate input
        n = getInteger("Enter number n: ");
        k = getInteger("Enter number k: ");
        if (n < 0 || k < 0) {
            std::cout << "Invalid Input: Enter only positive integers" << std::endl;
            continue;
        } else if (n < k) {
            std::cout << "Invalid Input: n cannot be smaller than k" << std::endl;
            continue;
        }
        break;
    }

    int ans = combinations(n, k);
    std::cout << "Answer: " << ans << std::endl;

    return 0;
}
