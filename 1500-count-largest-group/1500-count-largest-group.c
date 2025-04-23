int countLargestGroup(int n) {
    int hashMap[100] = {0};
    int maxValue = 0;
    for (int i = 1; i <= n; ++i) {
        int key = 0, i0 = i;
        while (i0) {
            key += i0 % 10;
            i0 /= 10;
        }
        hashMap[key]++;
        if (hashMap[key] > maxValue) {
            maxValue = hashMap[key];
        }
    }

    int count = 0;
    for (int i = 0; i < 100; ++i) {
        if (hashMap[i] == maxValue) {
            count++;
        }
    }
    return count;
}