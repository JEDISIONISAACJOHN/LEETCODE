long long countSubarrays(int *nums, int numsSize, long long k) {
    int n = numsSize;
    long long res = 0, total = 0;
    for (int i = 0, j = 0; j < n; j++) {
        total += nums[j];
        while (i <= j && total * (j - i + 1) >= k) {
            total -= nums[i];
            i++;
        }
        res += j - i + 1;
    }
    return res;
}