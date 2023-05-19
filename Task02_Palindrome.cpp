//Task #2. Palindrome

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string inputString;
    string trashSymbolsString;

    cout << "InputString: ";
    getline(cin, inputString);

    cout << "TrashSymbolsString: ";
    getline(cin, trashSymbolsString);

    // string to lowercase, avoid case-sensitive strings.
    transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);

    // Temp comparison string.
    string temp = "";

    // If any trash, present,
    // it will not be added to the temporary string.
    for (size_t i = 0; i < inputString.length(); i++) {
        char c = inputString[i];
        if (trashSymbolsString.find(c) != string::npos) { //npos absent element.
            continue;
        } else {
            temp += c; // store input after remove trash.
        }
    }

    // check palindrome after removing trash.
    string reversedTemp = temp;
    reverse(reversedTemp.begin(), reversedTemp.end());
    if (temp == reversedTemp) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}

