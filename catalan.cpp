#include <bits/stdc++.h>
using namespace std;

unsigned long int catalan(unsigned int n, vector<int>& dp) {
    if(n <= 1)
        return 1;

    if(dp[n] != -1)
        return dp[n];

    unsigned long int res = 0;
    for(int i = 0; i < n; i++)
        res += catalan(i, dp) * catalan(n - i - 1, dp);
    return dp[n] = res;
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);

    unsigned int n;
    cout << "Enter n : ";
    cin >> n;

    vector<int> dp(n+1, -1);

    cout << "Catalan : " << catalan(n, dp) << "\n";

    return 0;
}