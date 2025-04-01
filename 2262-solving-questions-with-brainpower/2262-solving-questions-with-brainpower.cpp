class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        // Get the number of questions
        int n = questions.size();

        // Initialize DP array where dp[i] represents the maximum points
        // we can earn starting from the ith question
        // Using long long to handle potential large values
        vector<long long> dp(n,0);

        // Base case: For the last question, we just take its points value
        dp[n-1] = questions[n-1][0];

        // Fill the dp array from right to left (bottom-up approach)
        for(int i = n-2 ; i >= 0 ; i--) {
            int points = questions[i][0];
            int brainpower = questions[i][1];
        

        // Option 1: Solve the current question
        // We add the points of current question and the maximum points we can get
        // after skipping the next 'brainpower' questions
        int next_available_index = min(i + brainpower + 1 , n);
        long long solve_points = points + (next_available_index < n ? dp[next_available_index] : 0);

        // Option 2: Skip the current question
        // We take the maximum points we can get starting from the next question
        long long skip_points = dp[i+1];

        // The optimal strategy is to take the maximum of the two options
        dp[i] = max(solve_points,skip_points);

        }

        // dp[0] now contains the maximum points possible starting from the first question (with our bottom-up approach)
        return dp[0];

    }
};