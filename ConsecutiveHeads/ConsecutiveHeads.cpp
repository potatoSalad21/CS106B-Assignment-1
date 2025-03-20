/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include "StanfordCPPLib/console.h"
#include "StanfordCPPLib/random.h"
#include <iostream>
#include <string>
using std::string;

enum Side {
    heads,
    tails
};

Side generateCoin() {
    return static_cast<Side>(randomChance(0.5));
}

void display() {
    int headCount = 0;
    int flipCount = 0;
    while (headCount < 3) {
        flipCount++;
        Side coinSide = generateCoin();
        if (coinSide == Side::heads) {
            headCount++;
            std::cout << "heads" << std::endl;
        } else {
            headCount = 0;
            std::cout << "tails" << std::endl;
        }
    }

    std::cout << "It took " << flipCount << " flips to get 3 consecutive heads." << std::endl;
}

int main() {
    display();

    return 0;
}
