long long minSum(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    long long sum1 = 0, sum2 = 0;
    int zero1 = 0, zero2 = 0;

    for (int i = 0; i < nums1Size; i++) {
        sum1 += nums1[i];
        if (nums1[i] == 0) {
            sum1 += 1;
            zero1++;
        }
    }

    for (int i = 0; i < nums2Size; i++) {
        sum2 += nums2[i];
        if (nums2[i] == 0) {
            sum2 += 1;
            zero2++;
        }
    }

    if ((zero1 == 0 && sum2 > sum1) || (zero2 == 0 && sum1 > sum2)) {
        return -1;
    }

    return sum1 > sum2 ? sum1 : sum2;
}