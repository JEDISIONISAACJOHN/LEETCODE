class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        vector<vector<int>> dp(2, vector<int>(arr.size()+1, 0));
        int res = 0, mod = 1e9+7;

        for(int i = arr.size()-1; i >= 0; i--) {
            if(arr[i] & 1) {  // Odd number
                dp[1][i] = (dp[0][i+1] + 1) % mod;
                dp[0][i] = dp[1][i+1] % mod;
            } else {  // Even number
                dp[1][i] = dp[1][i+1] % mod;
                dp[0][i] = (dp[0][i+1] + 1) % mod;
            }
            res = (res + dp[1][i]) % mod;
        }
        return res;
    }
};