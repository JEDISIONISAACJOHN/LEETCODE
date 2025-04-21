int numberOfArrays(int* differences, int differencesSize, int lower,
                   int upper) {
    int x = 0, y = 0, cur = 0;
    for (int i = 0; i < differencesSize; i++) {
        cur += differences[i];
        x = (x < cur) ? x : cur;
        y = (y > cur) ? y : cur;
        if (y - x > upper - lower) {
            return 0;
        }
    }
    return (upper - lower) - (y - x) + 1;
}