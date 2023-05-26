//Task #2. Palindrome

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool isPalindromeWithTrash(string inputString, string trashSymbolsString) {
    transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);     // Convert inputString to lowercase.
    size_t start = 0;
    size_t end = inputString.length() - 1;

    while (start < end) {
        char startChar = inputString[start];
        char endChar = inputString[end];

        // If startChar is a trash symbol, move the start pointer forward.
        if (trashSymbolsString.find(startChar) != string::npos) {
            start++;
            continue;
        }

        // If endChar is a trash symbol, move the end pointer backward.
        if (trashSymbolsString.find(endChar) != string::npos) {
            end--;
            continue;
        }

        // If startChar and endChar are different, =!palindrome.
        if (startChar != endChar) {
            return false;
        }

        // Move both pointers inward.
        start++;
        end--;
    }

    // If all characters checked and no mismatch found = palindrome.
    return true;
}

int main() {
    string inputString;
    string trashSymbolsString;

    cout << "InputString: ";    // Get inputString.
    getline(cin, inputString);

    cout << "TrashSymbolsString: "; // Get trashSymbolsString.
    getline(cin, trashSymbolsString);

    // Check if inputString = isPalindrome with ignored trash symbols.
    bool isPalindrome = isPalindromeWithTrash(inputString, trashSymbolsString);

    // Output the result as either "true" or "false"
    cout << (isPalindrome ? "true" : "false") << endl;

    return 0;
}
