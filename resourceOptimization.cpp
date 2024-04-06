#include <bits/stdc++.h>
using namespace std;

int func(vector<vector<int>>& mat, int n) {
    int sz = pow(2, n);
    vector<int> dp(sz, INT_MAX);
    dp[0] = 0;

    for(int mask = 0; mask < sz; mask++) {
        int setBits = __builtin_popcount(mask);
        for(int j = 0; j < n; j++) {
            if(!(mask & (1 << j))) {
                dp[mask | (1 << j)] = min(dp[mask | (1 << j)], dp[mask] + mat[setBits][j]);
            }
        }
    }
    return dp[sz - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<vector<int>> mat = {{3, 2, 1, 5},
                                {3, 2, 1, 9},
                                {4, 4, 2, 10},
                                {2, 2, 2, 3}};

    cout << "Minimum Cost : " << func(mat, mat.size()) << "\n";
    return 0;
}