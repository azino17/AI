#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class CryptArithmetic {
private:
    string word1, word2, result;
    unordered_map<char, int> letterToDigit;
    bool usedDigits[10];
    vector<char> uniqueLetters;

    void extractUniqueLetters() {
        unordered_set<char> seen;
        for (char c : (word1 + word2 + result)) {
            if (seen.find(c) == seen.end()) {
                uniqueLetters.push_back(c);
                seen.insert(c);
            }
        }
    }

    bool isValid() {
        // Leading letters cannot be zero
        if (letterToDigit[word1[0]] == 0 || letterToDigit[word2[0]] == 0 || letterToDigit[result[0]] == 0)
            return false;

        int num1 = getValue(word1);
        int num2 = getValue(word2);
        int numResult = getValue(result);
        return (num1 + num2) == numResult;
    }

    int getValue(const string& word) {
        int value = 0;
        for (char c : word) {
            value = value * 10 + letterToDigit[c];
        }
        return value;
    }

    bool backtrack(int index) {
        if (index == (int)uniqueLetters.size()) {
            return isValid();
        }

        for (int digit = 0; digit <= 9; digit++) {
            if (!usedDigits[digit]) {
                letterToDigit[uniqueLetters[index]] = digit;
                usedDigits[digit] = true;

                if (backtrack(index + 1))
                    return true;

                // Backtrack
                letterToDigit.erase(uniqueLetters[index]);
                usedDigits[digit] = false;
            }
        }
        return false;
    }

public:
    CryptArithmetic(string w1, string w2, string res) : word1(move(w1)), word2(move(w2)), result(move(res)) {
        fill(begin(usedDigits), end(usedDigits), false);
        extractUniqueLetters();
    }

    bool solve() {
        return backtrack(0);
    }

    void printSolution() {
        for (const auto& entry : letterToDigit) {
            cout << entry.first << " -> " << entry.second << "\n";
        }
    }
};

int main() {
    cout << "Enter first word:\n";
    string w1; getline(cin, w1);
    cout << "Enter second word:\n";
    string w2; getline(cin, w2);
    cout << "Enter result word:\n";
    string res; getline(cin, res);

    // Convert input to uppercase
    for (auto& c : w1) c = toupper(c);
    for (auto& c : w2) c = toupper(c);
    for (auto& c : res) c = toupper(c);

    CryptArithmetic solver(w1, w2, res);

    if (solver.solve()) {
        solver.printSolution();
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}
