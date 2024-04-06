// Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

// You have the following three operations permitted on a word:

// Insert a character
// Delete a character
// Replace a character
 

// Example 1:

// Input: word1 = "horse", word2 = "ros"
// Output: 3
// Explanation: 
// horse -> rorse (replace 'h' with 'r')
// rorse -> rose (remove 'r')
// rose -> ros (remove 'e')
// Example 2:

// Input: word1 = "intention", word2 = "execution"
// Output: 5
// Explanation: 
// intention -> inention (remove 't')
// inention -> enention (replace 'i' with 'e')
// enention -> exention (replace 'n' with 'x')
// exention -> exection (replace 'n' with 'c')
// exection -> execution (insert 'u')


#include <bits/stdc++.h>
using namespace std;


// TC : Exponential
// SC : O(N + M)
int recursionUtil(int i, int j, string& word1, string& word2) {
    if(i < 0)
        return j+1;
    if(j < 0)
        return i+1;

    if(word1[i] == word2[j])
        return recursionUtil(i - 1, j - 1, word1, word2);
    
    int insert = 1 + recursionUtil(i - 1, j, word1, word2);
    int deletion = 1 + recursionUtil(i, j - 1, word1, word2);
    int replace = 1 + recursionUtil(i - 1, j - 1, word1, word2);

    return min({insert, deletion, replace});
}
int recursion(string word1, string word2) {
    return recursionUtil(word1.length() - 1, word2.length() - 1, word1, word2);
}



// TC : O(N * M)
// SC : O(N * M) + O(N + M)(recursive stack space)
int memoizationUtil(int i, int j, string& word1, string& word2, vector<vector<int>>& dp) {
    if(i < 0)
        return j+1;
    if(j < 0)
        return i+1;

    if(dp[i][j] != -1)
        return dp[i][j];

    if(word1[i] == word2[j])
        return memoizationUtil(i - 1, j - 1, word1, word2, dp);
    
    int insert = 1 + memoizationUtil(i, j - 1, word1, word2, dp);
    int deletion = 1 + memoizationUtil(i - 1, j, word1, word2, dp);
    int replace = 1 + memoizationUtil(i - 1, j - 1, word1, word2, dp);

    return dp[i][j] = min({insert, deletion, replace});
}
int memoization(string word1, string word2) {
    vector<vector<int>> dp(word1.length(), vector<int>(word2.length(), -1));
    return memoizationUtil(word1.length() - 1, word2.length() - 1, word1, word2, dp);
}


// TC : O(N * M)
// SC : O(N * M)
int tabulation(string word1, string word2) {
    int n = word1.length(), m = word2.length();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    // base cases
    for(int i = 0; i <= n; i++)
        dp[i][0] = i;
    for(int j = 0; j <= m; j++)
        dp[0][j] = j;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                int insert = 1 + dp[i][j - 1];
                int deletion = 1 + dp[i - 1][j];
                int replace = 1 + dp[i - 1][j - 1];

                dp[i][j] = min({insert, deletion, replace});
            }
        }
    }
    return dp[n][m];
}

// TC : O(N * M)
// SC : O(2 * M)
int spaceOptimization(string word1, string word2) {
    int n = word1.length(), m = word2.length();
    vector<int> prev(m+1, 0), curr(m+1, 0);

    // base cases(not needed though...)
    for(int j = 0; j <= m; j++)
        prev[j] = j;


    for(int i = 1; i <= n; i++) {
        curr[0] = i;
        for(int j = 1; j <= m; j++) {
            if(word1[i - 1] == word2[j - 1]) {
                curr[j] = prev[j - 1];
            }
            else {
                int insert = 1 + prev[j];
                int deletion = 1 + curr[j - 1];
                int replace = 1 + prev[j - 1];

                curr[j] = min({insert, deletion, replace});
            }
        }
        prev = curr;
    }
    return prev[m];
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string word1 = "horse", word2 = "ros";
    cout << "\nWord1 : " << word1 << "\n";
    cout << "Word2 : " << word2 << "\n";

    cout << "\nMinimum number of Operations via recursion: " << recursion(word1, word2) << "\n";
    cout << "Minimum number of Operations via memoization: " << memoization(word1, word2) << "\n";
    cout << "Minimum number of Operations via tabulation: " << tabulation(word1, word2) << "\n";
    cout << "Minimum number of Operations via spaceOptimization: " << spaceOptimization(word1, word2) << "\n";

    return 0;
}