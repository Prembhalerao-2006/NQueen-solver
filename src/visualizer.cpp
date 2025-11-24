// visualizer.cpp
// A small console visualizer that animates one solution being placed step-by-step.
// Compile: g++ -O2 -std=c++17 visualizer.cpp -o visualizer
// Usage: ./visualizer N
// It uses the classic backtracking to find one solution and animates placement.

#include <bits/stdc++.h>
#include <unistd.h> // usleep
using namespace std;

void clearConsole() {
    // ANSI escape to clear screen
    cout << "\033[2J\033[H";
}

void printBoard(const vector<int>& pos, int highlightRow = -1, int highlightCol = -1) {
    int n = pos.size();
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            bool isQueen = (pos[r] == c);
            if (r == highlightRow && c == highlightCol) cout << '[';
            else cout << ' ';
            cout << (isQueen ? 'Q' : '.');
            if (r == highlightRow && c == highlightCol) cout << ']';
            else cout << ' ';
        }
        cout << '\n';
    }
}

bool tryFindOne(int row, int n, vector<int>& pos) {
    if (row == n) return true;
    for (int col = 0; col < n; ++col) {
        bool ok = true;
        for (int r = 0; r < row; ++r) {
            if (pos[r] == col || abs(pos[r] - col) == row - r) { ok = false; break; }
        }
        if (!ok) continue;
        pos[row] = col;
        // animate placement
        clearConsole();
        cout << "Placing at row " << row << " col " << col << "\n\n";
        printBoard(pos, row, col);
        usleep(200000); // 200ms
        if (tryFindOne(row+1, n, pos)) return true;
        // backtrack animate removal
        pos[row] = -1;
        clearConsole();
        cout << "Backtracking from row " << row << " col " << col << "\n\n";
        printBoard(pos, row, col);
        usleep(150000);
    }
    return false;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " N\n";
        return 0;
    }
    int N = stoi(argv[1]);
    if (N < 4) {
        cout << "No solutions for N < 4 (except N=1). Try N >= 4\n";
        return 0;
    }
    vector<int> pos(N, -1);
    bool found = tryFindOne(0, N, pos);
    if (found) {
        cout << "\nFound solution:\n";
        printBoard(pos);
    } else {
        cout << "No solution found.\n";
    }
    return 0;
}
