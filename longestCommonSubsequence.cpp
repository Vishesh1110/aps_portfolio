// Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.

// A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

// For example, "ace" is a subsequence of "abcde".
// A common subsequence of two strings is a subsequence that is common to both strings.

 
// Example 1:

// Input: text1 = "abcde", text2 = "ace" 
// Output: 3  
// Explanation: The longest common subsequence is "ace" and its length is 3.

#include <bits/stdc++.h> 
using namespace std;


// TC : O(2^(l1 + l2))
// SC : O(l1 + l2))
int recursion(int index1, int index2, string& text1, string& text2) {
    if(index1 < 0 || index2 < 0) return 0;

    if(text1[index1] == text2[index2]) 
        return 1 + recursion(index1 - 1, index2 - 1, text1, text2);
    
    return max(recursion(index1 - 1, index2, text1, text2), recursion(index1, index2 - 1, text1, text2));
}


// TC : O(l1 * l2)
// SC : O(l1 * l2) + O(l1 + l2)
int memoizationHelper(int index1, int index2, string& text1, string& text2, vector<vector<int>>& dp) {
    if(index1 < 0 || index2 < 0) return 0;

    if(dp[index1][index2] != -1) return dp[index1][index2];

    if(text1[index1] == text2[index2]) 
        return dp[index1][index2] = 1 + memoizationHelper(index1 - 1, index2 - 1, text1, text2, dp);
    
    return dp[index1][index2] = max(memoizationHelper(index1 - 1, index2, text1, text2, dp), memoizationHelper(index1, index2 - 1, text1, text2, dp));
}
int memoization(int l1, int l2, string& text1, string& text2) {
    vector<vector<int>> dp(l1, vector<int>(l2, -1));
    return memoizationHelper(l1 - 1, l2 - 1, text1, text2, dp);
}


// TC : O(l1 * l2)
// SC : O(l1 * l2)
int tabulation(int l1, int l2, string& text1, string& text2) {
    vector<vector<int>> dp(l1+1, vector<int>(l2+1, 0));

    // for(int index2 = 0; index2 <= l2; index2++) 
    //     dp[0][index2] = 0;
    // for(int index1 = 0; index1 <= l1; index1++) 
    //     dp[index1][0] = 0;

    for(int index1 = 1; index1 <= l1; index1++) {
        for(int index2 = 1; index2 <= l1; index2++) {
            if(text1[index1 - 1] == text2[index2 - 1]) {
                dp[index1][index2] = 1 + dp[index1 - 1][index2 - 1];
            }
            else {
                dp[index1][index2] = max(dp[index1 - 1][index2], dp[index1][index2 - 1]);
            }
        }
    }

    string lcs = "";
    // int len = dp[l1][l2];
    // for (int i = 0; i < len; i++)
    //     lcs += '$';
    
    // cout << "\n";
    // for(int i = 0; i < dp.size(); i++) {
    //     for(int j = 0; j < dp[i].size(); j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    int i = l1, j = l2;
    while(i > 0 && j > 0) {
        // cout << i << " " << j << "\n";
        
        if(text1[i-1] == text2[j-1]) {
            lcs.push_back(text1[i-1]);
            // cout << lcs << " inner\n";
            i--, j--;
        }
        else if(dp[i-1][j] > dp[i][j-1]) {
            i--;
        }
        else {
            j--;
        }
    }
    reverse(lcs.begin(), lcs.end());
    cout << "\nLongest Common Subsequence: " << lcs << "\n";

    return dp[l1][l2];
}


// TC : O(l1 * l2)
// SC : O(l2) * 2
int spaceOptimization1(int l1, int l2, string& text1, string& text2) {
    vector<int> prev(l2+1, 0), curr(l2+1, 0);

    // for(int index2 = 0; index2 <= l2; index2++) 
    //     prev[index2] = 0;

    for(int index2 = 1; index2 <= l2; index2++) {
        for(int index1 = 1; index1 <= l1; index1++) {
            if(text1[index1 - 1] == text2[index2 - 1]) {
                curr[index1] = 1 + prev[index1 - 1];
            }
            else {
                curr[index1] = max(prev[index1], curr[index1 - 1]);
            }
        }
        prev = curr;
    }
    return prev[l2];
}

// TC : O(l1 * l2)
// SC : O(l2)
int spaceOptimization2(int l1, int l2, string& text1, string& text2) {
    vector<int> dp(l2+1, 0);

    // for(int index2 = 0; index2 <= l2; index2++) 
    //     prev[index2] = 0;

    for(int index2 = 1; index2 <= l2; index2++) {
        int prev = 0;
        for(int index1 = 1; index1 <= l1; index1++) {
        int curr = dp[index1];
            if(text1[index1 - 1] == text2[index2 - 1]) {
                dp[index1] = 1 + prev;
            }
            else {
                dp[index1] = max(dp[index1], dp[index1 - 1]);
            }
            prev = curr;
        }
    }
    return dp[l2];
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string text1 = "adebc", text2 = "dcadb";
    cout << "\nText 1: " << text1;
    cout << "\nText 2: " << text2;

    if(text1 == text2) {
        cout << "Longest Common Subsequence : " << text1.size();
        exit(0);
    }

    int l1 = text1.size(), l2 = text2.size();
    
    cout << "\n\nLongest Common Subsequence via recursion: " << recursion(l1 - 1, l2 - 1, text1, text2) << "\n";
    cout << "Longest Common Subsequence via memoization: " << memoization(l1, l2, text1, text2) << "\n";
    cout << "Longest Common Subsequence via tabulation: " << tabulation(l1, l2, text1, text2) << "\n";
    cout << "Longest Common Subsequence via space Optimization1: " << spaceOptimization1(l1, l2, text1, text2) << "\n";
    cout << "Longest Common Subsequence via space Optimization2: " << spaceOptimization2(l1, l2, text1, text2) << "\n";

    return 0;
}