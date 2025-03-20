/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include "StanfordCPPLib/tokenscanner.h"
#include "StanfordCPPLib/console.h"
#include "StanfordCPPLib/simpio.h"
#include <iostream>
#include <cctype>
#include <fstream>
using std::string;

/* struct for storing file stats */
struct FileInfo {
    int wordNum;
    int sentenceNum;
    int syllableNum;
};

/* FUNCTION DEFINITIONS */
FileInfo newFileInfo(int words, int sentences, int syllables);
FileInfo parseFile(TokenScanner &scanner);

int getSyllableCount(string token);
double calcGrade(FileInfo *fi);
void printInfo(FileInfo *fi);
bool isPunct(char ch);

int main() {
    std::cout << getSyllableCount("applepie sauce") << std::endl;
    const string SENTINEL = "-1";
    while (true) {
        string fileName = getLine("Enter file name: ");
        if (fileName == SENTINEL) break;
        std::ifstream input{ fileName };
        if (!input) {
            std::cout << "Error: file doesn't exist" << std::endl;
            continue;
        }

        TokenScanner scanner{ input };
        scanner.ignoreWhitespace();
        scanner.addWordCharacters("'");
        FileInfo fi = parseFile(scanner);
        printInfo(&fi);
    }

    return 0;
}


// initialize file info
FileInfo newFileInfo(int words=0, int sentences=0, int syllables=0) {
    return FileInfo{
        words,
        sentences,
        syllables
    };
}

/* parse the file and get data
*    returns the word/sentence/syllable counts grouped together in a struct
*/
FileInfo parseFile(TokenScanner &scanner) {
    int wordCount = 0;
    int sentenceCount = 0;
    int syllableCount = 0;

    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();

        if (token.length() == 1 && token[0] == '"') continue;

        // check if token is a word
        if (isalpha(token[0])) {
            wordCount++;
            syllableCount += getSyllableCount(token);
            continue;
        }

        // check if the sentence has ended
        if (isPunct(token[0]) && (token.length() == 1 || !isalnum(token[1]))) {
            sentenceCount++;
        }
    }

    wordCount = wordCount > 1 ? wordCount : 1;
    sentenceCount = sentenceCount> 1 ? sentenceCount : 1;
    syllableCount = syllableCount > 1 ? syllableCount : 1;

    FileInfo fi = newFileInfo(wordCount, sentenceCount, syllableCount);
    return fi;
}

// count syllables in the token
int getSyllableCount(string token) {
    string vow = "aeiouy";
    int cnt = 0;
    for (int i = 0; i < token.length(); i++) {
        if (vow.find(tolower(token[i])) != string::npos) {
            if (i == 0 || vow.find(tolower(token[i - 1])) == string::npos) {
                cnt++;
            }
        }
    }

    // dont't count the silent vowel 'e'
    if (token.length() > 2 && cnt > 1 &&
        tolower(token[token.length() - 1]) == 'e' &&
        vow.find(tolower(token[token.length() - 2])) == string::npos)
    {
        cnt--;
    }

    return cnt > 1 ? cnt : 1;
}

double calcGrade(FileInfo *fi) {
    const double C0 = -15.59;
    const double C1 = 0.39;
    const double C2 = 11.8;

    return C0 + C1 * ((double) fi->wordNum / fi->sentenceNum) +
            C2 * ((double) fi->syllableNum / fi->wordNum);
}

void printInfo(FileInfo *fi) {
    std::cout << "Words -> " << fi->wordNum << std::endl;
    std::cout << "Sentences -> " << fi->sentenceNum << std::endl;
    std::cout << "Syllables -> " << fi->syllableNum << std::endl;
    std::cout << "Grade -> " << calcGrade(fi) << std::endl;
}

bool isPunct(char ch) {
    string punct = ".!?"; // punctuations that end sentences
    return punct.find(ch) != string::npos;
}

