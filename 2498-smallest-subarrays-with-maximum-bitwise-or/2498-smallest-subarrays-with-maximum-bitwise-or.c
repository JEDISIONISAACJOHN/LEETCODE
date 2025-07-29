int* smallestSubarrays(int* nums, int numsSize, int* returnSize) {
    int* pos = (int*)malloc(31 * sizeof(int));
    memset(pos, -1, 31 * sizeof(int));
    int* ans = (int*)malloc(numsSize * sizeof(int));
    for (int i = numsSize - 1; i >= 0; --i) {
        int j = i;
        for (int bit = 0; bit < 31; ++bit) {
            if (!(nums[i] & (1 << bit))) {
                if (pos[bit] != -1) {
                    j = fmax(j, pos[bit]);
                }
            } else {
                pos[bit] = i;
            }
        }
        ans[i] = j - i + 1;
    }
    free(pos);
    *returnSize = numsSize;
    return ans;
}