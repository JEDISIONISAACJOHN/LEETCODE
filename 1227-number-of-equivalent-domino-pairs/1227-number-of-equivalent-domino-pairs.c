int numEquivDominoPairs(int** dominoes, int dominoesSize,
                        int* dominoesColSize) {
    int num[100];
    memset(num, 0, sizeof(num));
    int ret = 0;
    for (int i = 0; i < dominoesSize; i++) {
        int val = dominoes[i][0] < dominoes[i][1]
                      ? dominoes[i][0] * 10 + dominoes[i][1]
                      : dominoes[i][1] * 10 + dominoes[i][0];
        ret += num[val];
        num[val]++;
    }
    return ret;
}