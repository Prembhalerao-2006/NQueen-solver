// solver.cpp
// Compile: g++ -O2 -std=c++17 solver.cpp -o solver
// Usage: ./solver N [mode]
// mode 0 = classic backtracking (prints solutions), mode 1 = bitmask (counts solutions, fast)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void printBoard(const vector<int>& pos) {
    int n = pos.size();
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c)
            cout << (pos[r] == c ? 'Q' : '.') << ' ';
        cout << '\n';
    }
    cout << '\n';
}

// Classic backtracking (explicit checks)
void bt_classic(int row, int n, vector<int>& pos, vector<vector<int>>& out) {
    if (row == n) {
        out.push_back(pos);
        return;
    }
    for (int col = 0; col < n; ++col) {
        bool ok = true;
        for (int r = 0; r < row; ++r) {
            if (pos[r] == col || abs(pos[r] - col) == row - r) {
                ok = false; break;
            }
        }
        if (!ok) continue;
        pos[row] = col;
        bt_classic(row + 1, n, pos, out);
    }
}

// Bitmask optimized solver (counts solutions)
ll solve_bitmask(int n) {
    // Uses recursion with bitmasks (row-by-row recursion passing three masks)
    // columns, diag1, diag2: bits 1 indicate occupied
    // Define dfs2 as a 4-argument function: (row, cols, diags, anti)
    function<ll(int,int,int,int)> dfs2 = [&](int row, int cols, int diags, int anti) -> ll {
        if (row == n) return 1;
        int all = (1<<n) - 1;
        int free = all & ~(cols | diags | anti);
        ll cnt = 0;
        while (free) {
            int bit = free & -free;
            free -= bit;
            cnt += dfs2(row+1, cols|bit, (diags|bit)<<1, (anti|bit)>>1);
        }
        return cnt;
    };
    return dfs2(0,0,0,0);
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " N [mode]\n"
             << "mode 0 = classic backtracking (prints solutions)\n"
             << "mode 1 = bitmask count only (fast)\n";
        return 0;
    }
    int N = stoi(argv[1]);
    int mode = 1;
    if (argc >= 3) mode = stoi(argv[2]);

    if (N <= 0) {
        cout << "N must be positive\n";
        return 0;
    }

    if (mode == 0) {
        vector<int> pos(N, -1);
        vector<vector<int>> sols;
        auto t0 = chrono::high_resolution_clock::now();
        bt_classic(0, N, pos, sols);
        auto t1 = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(t1 - t0).count();
        cout << "Found " << sols.size() << " solutions for N = " << N << " (classic)\n";
        cout << "Time: " << ms << " ms\n\n";
        // Print solutions (be careful: for large N this becomes huge)
        for (size_t i = 0; i < sols.size(); ++i) {
            cout << "Solution " << i+1 << ":\n";
            printBoard(sols[i]);
        }
    } else {
        auto t0 = chrono::high_resolution_clock::now();
        // bitmask may be slow in recursion depth if n>31; we'll restrict to n<=15 typically
        if (N > 20) {
            cout << "Warning: bitmask solver here is implemented for N up to ~20 comfortably (due to shifting). Using 64-bit would extend it.\n";
        }
        ll count = solve_bitmask(N);
        auto t1 = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(t1 - t0).count();
        cout << "Number of solutions for N = " << N << " is: " << count << "\n";
        cout << "Time: " << ms << " ms\n";
    }
    return 0;
}
