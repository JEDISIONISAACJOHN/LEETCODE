typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} HashItem;

HashItem *hashFindItem(HashItem **obj, int key) {
    HashItem *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    return pEntry;
}

bool hashAddItem(HashItem **obj, int key, int val) {
    if (hashFindItem(obj, key)) {
        return false;
    }
    HashItem *pEntry = (HashItem *)malloc(sizeof(HashItem));
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_INT(*obj, key, pEntry);
    return true;
}

bool hashSetItem(HashItem **obj, int key, int val) {
    HashItem *pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        hashAddItem(obj, key, val);
    } else {
        pEntry->val = val;
    }
    return true;
}

int hashGetItem(HashItem **obj, int key, int defaultVal) {
    HashItem *pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        return defaultVal;
    }
    return pEntry->val;
}

void hashFree(HashItem **obj) {
    HashItem *curr = NULL, *tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}

long long countInterestingSubarrays(int *nums, int numsSize, int modulo,
                                    int k) {
    HashItem *cnt = NULL;
    long long res = 0;
    int prefix = 0;
    hashAddItem(&cnt, 0, 1);
    for (int i = 0; i < numsSize; i++) {
        prefix += nums[i] % modulo == k;
        res += hashGetItem(&cnt, (prefix - k + modulo) % modulo, 0);
        hashSetItem(&cnt, prefix % modulo,
                    hashGetItem(&cnt, prefix % modulo, 0) + 1);
    }
    hashFree(&cnt);
    return res;
}