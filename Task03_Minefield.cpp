//Task#3 Mindfield: Traversal Algorithm

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to create the minefield with randomly placed bombs
vector<vector<bool>> createMinefield(int n, int m, int numBombs) {
    vector<vector<bool>> minefield(n, vector<bool>(m, false));
    vector<int> bombPositions(n * m);
    for (int i = 0; i < n * m; ++i) {
        bombPositions[i] = i;
    }
    random_shuffle(bombPositions.begin(), bombPositions.end());
    for (int i = 0; i < numBombs; ++i) {
        int pos = bombPositions[i];
        int row = pos / m;
        int col = pos % m;
        minefield[row][col] = true;
    }
    return minefield;
}

// Function to print the minefield with Totoshka's and Ally's positions
void printMinefield(const vector<vector<bool>>& minefield, const map<pair<int, int>, int>& positions) {
    char symbols[2] = { 'v', 'X' }; //v = safe path, X = bomb
    for (int i = 0; i < minefield.size(); ++i) {
        for (int j = 0; j < minefield[i].size(); ++j) {
            auto pos = make_pair(i, j);
            if (positions.count(pos)) {
                char symbol = (positions.at(pos) == 0) ? 'T' : 'A'; //T = Totoshka, A = Ally
                cout << symbol << " ";
            } else {
                cout << symbols[minefield[i][j]] << " ";
            }
        }
        cout << endl;
    }
}

// Function to check for adjacent bombs using Totoshka's sense of smell
vector<pair<int, int>> sniffAdjacentFields(const vector<vector<bool>>& minefield, int x, int y) {
    int n = minefield.size();
    int m = minefield[0].size();
    vector<pair<int, int>> adjacentBombs;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && minefield[nx][ny]) {
                adjacentBombs.emplace_back(nx, ny);
            }
        }
    }
    return adjacentBombs;
}

// Function to move Totoshka to the adjacent field with no bomb
pair<int, int> moveTotoshka(const vector<vector<bool>>& minefield, map<pair<int, int>, int>& positions, int x, int y) {
    int n = minefield.size();
    int m = minefield[0].size();
    vector<pair<int, int>> adjacentFields;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !minefield[nx][ny] && !positions.count(make_pair(nx, ny))) {
                adjacentFields.emplace_back(nx, ny);
            }
        }
    }
    if (!adjacentFields.empty()) {
        int idx = rand() % adjacentFields.size();
        pair<int, int> nextPos = adjacentFields[idx];
        positions[nextPos] = 0;  // Totoshka's position
        return nextPos;
    } else {
        return make_pair(x, y);
    }
}

// Function to move Ally to the field where Totoshka was before
pair<int, int> moveAlly(map<pair<int, int>, int>& positions) {
    auto allyPos = max_element(positions.begin(), positions.end(),
        [](const pair<pair<int, int>, int>& p1, const pair<pair<int, int>, int>& p2) {
            return p1.second < p2.second;
        });
    positions[allyPos->first] = 1;  // Ally's position
    return allyPos->first;
}

// Function for Totoshka and Ally to pass the minefield
void totoAndAllyPassMinefield(int n, int m, int numBombs) {
    srand(static_cast<unsigned int>(time(0)));
    vector<vector<bool>> minefield = createMinefield(n, m, numBombs);
    map<pair<int, int>, int> positions;
    positions[make_pair(0, 0)] = 0;  // Totoshka's initial position
    int x = 0, y = 0;

    cout << "Initial minefield:" << endl;
    printMinefield(minefield, positions);
    cout << endl;

    while (x != n - 1 || y != m - 1) {
        vector<pair<int, int>> adjacentBombs = sniffAdjacentFields(minefield, x, y);
        if (adjacentBombs.empty()) {
            tie(x, y) = moveTotoshka(minefield, positions, x, y);
        }
        pair<int, int> allyPos = moveAlly(positions);
        cout << "Updated minefield:" << endl;
        printMinefield(minefield, positions);
        cout << endl;
    }

    cout << "Final minefield:" << endl;
    printMinefield(minefield, positions);
    cout << "YAAAAYYY!! :D \nTotoshka and Ally passed the minefield!" << endl;
}

int main() {
    int n, m, numBombs;
    
    cout << "<<======  n(0^0n)  HELP TOTOSHKA AND ALLY!!! (n0^0)n   ======>>"<< endl;
    cout << "Enter the number of rows in the minefield: ";
    cin >> n;
    cout << "Enter the number of columns in the minefield: ";
    cin >> m;
    cout << "Enter the number of bombs: ";
    cin >> numBombs;

    totoAndAllyPassMinefield(n, m, numBombs);
    return 0;
}
