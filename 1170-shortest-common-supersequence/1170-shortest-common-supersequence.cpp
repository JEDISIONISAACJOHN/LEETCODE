class Solution {
public:
    string shortestCommonSupersequence(string s, string t) {
        string res = "";
        memset(dp, -1, sizeof(dp));
        int len = solve(0, 0, s, t);
        int n = s.length(), m = t.length();

        for (int i = 0, j = 0; i < n || j < m; ){
            if (i < n && j < m && s[i] == t[j]){
                res.push_back(s[i]);
                i++; j++;
            }
            else if (i < n && (j == m || dp[i + 1][j] <= dp[i][j + 1]))
                res.push_back(s[i++]);
            else
                res.push_back(t[j++]);
        }
        
        return res;
    }
private:
    int dp[1001][1001];
    int solve(int i, int j, string& s, string& t){
        int n = s.length(), m = t.length();
        if (i == n)
            return dp[i][j] = m - j;
        else if (j == m)
            return dp[i][j] = n - i;
        else if (dp[i][j] != -1)
            return dp[i][j];

        if (s[i] == t[j]){
            return dp[i][j] = 1 + solve(i + 1, j + 1, s, t);
        }

        return dp[i][j] = 1 + min(solve(i + 1, j, s, t), solve(i, j + 1, s, t));
    }
};