#define MOD 1000000007

long long dfs(int pos, int curr, int oddCnt, int* cnt, int* psum, int target,
              long long*** memo, long long** comb, int maxOdd) {
    /* If the remaining positions cannot be legally filled, or if the sum of the
     * elements at the current odd positions is greater than the target value */
    if (oddCnt < 0 || psum[pos] < oddCnt || curr > target) {
        return 0;
    }
    if (pos > 9) {
        return curr == target && oddCnt == 0;
    }
    if (memo[pos][curr][oddCnt] != -1) {
        return memo[pos][curr][oddCnt];
    }

    /* Even-numbered positions remaining to be filled */
    int evenCnt = psum[pos] - oddCnt;
    long long res = 0;
    int start = fmax(0, cnt[pos] - evenCnt);
    int end = fmin(cnt[pos], oddCnt);
    for (int i = start; i <= end; i++) {
        /* The current digit is filled with i positions at odd positions, and
         * cnt[pos] - i positions at even positions */
        long long ways = comb[oddCnt][i] * comb[evenCnt][cnt[pos] - i] % MOD;
        res = (res + ways *
                         dfs(pos + 1, curr + i * pos, oddCnt - i, cnt, psum,
                             target, memo, comb, maxOdd) %
                         MOD) %
              MOD;
    }
    memo[pos][curr][oddCnt] = res;
    return res;
}

int countBalancedPermutations(char* num) {
    int tot = 0, n = strlen(num);
    int cnt[10] = {0};
    for (int i = 0; i < n; i++) {
        int d = num[i] - '0';
        cnt[d]++;
        tot += d;
    }
    if (tot % 2 != 0) {
        return 0;
    }

    int target = tot / 2;
    int maxOdd = (n + 1) / 2;

    /* Pre-calculate combinations */
    long long** comb = (long long**)malloc((maxOdd + 1) * sizeof(long long*));
    for (int i = 0; i <= maxOdd; i++) {
        comb[i] = (long long*)malloc((maxOdd + 1) * sizeof(long long));
        comb[i][i] = comb[i][0] = 1;
        for (int j = 1; j < i; j++) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
        }
    }

    int psum[11] = {0};
    for (int i = 9; i >= 0; i--) {
        psum[i] = psum[i + 1] + cnt[i];
    }
    /* Initialize memoization array */
    long long*** memo = (long long***)malloc(10 * sizeof(long long**));
    for (int i = 0; i < 10; i++) {
        memo[i] = (long long**)malloc((target + 1) * sizeof(long long*));
        for (int j = 0; j <= target; j++) {
            memo[i][j] = (long long*)malloc((maxOdd + 1) * sizeof(long long));
            for (int k = 0; k <= maxOdd; k++) {
                memo[i][j][k] = -1;
            }
        }
    }

    long long result = dfs(0, 0, maxOdd, cnt, psum, target, memo, comb, maxOdd);
    for (int i = 0; i <= maxOdd; i++) {
        free(comb[i]);
    }
    free(comb);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j <= target; j++) {
            free(memo[i][j]);
        }
        free(memo[i]);
    }
    free(memo);

    return result;
}