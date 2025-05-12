typedef struct {
    int key;
    UT_hash_handle hh;
} HashItem;

HashItem *hashFindItem(HashItem **obj, int key) {
    HashItem *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    return pEntry;
}

bool hashAddItem(HashItem **obj, int key) {
    if (hashFindItem(obj, key)) {
        return false;
    }
    HashItem *pEntry = (HashItem *)malloc(sizeof(HashItem));
    pEntry->key = key;
    HASH_ADD_INT(*obj, key, pEntry);
    return true;
}

void hashFree(HashItem **obj) {
    HashItem *curr = NULL, *tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int *findEvenNumbers(int *digits, int digitsSize, int *returnSize) {
    HashItem *nums = NULL;  // Target even set
    int n = digitsSize;
    // Traverse the indices of three digits
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                // Determine whether it meets the condition of the target even
                // number
                if (i == j || j == k || i == k) {
                    continue;
                }
                int num = digits[i] * 100 + digits[j] * 10 + digits[k];
                if (num >= 100 && num % 2 == 0) {
                    hashAddItem(&nums, num);
                }
            }
        }
    }

    // Converted to an array sorted in ascending order
    int numsSize = HASH_COUNT(nums);
    *returnSize = numsSize;
    int *res = (int *)malloc(sizeof(int) * numsSize);
    int pos = 0;
    for (HashItem *pEntry = nums; pEntry; pEntry = pEntry->hh.next) {
        res[pos++] = pEntry->key;
    }
    qsort(res, numsSize, sizeof(int), compare);
    return res;
}