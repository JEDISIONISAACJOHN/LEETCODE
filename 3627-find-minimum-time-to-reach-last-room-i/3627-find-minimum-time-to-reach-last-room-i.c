#define MIN_QUEUE_SIZE 64

typedef struct Element {
    int x;
    int y;
    int dist;
} Element;

typedef bool (*compare)(const void *, const void *);

typedef struct PriorityQueue {
    Element *arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;

static bool greater(const void *a, const void *b) {
    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    return e1->dist > e2->dist;
}

static void memswap(void *m1, void *m2, size_t size) {
    unsigned char *a = (unsigned char *)m1;
    unsigned char *b = (unsigned char *)m2;
    while (size--) {
        *b ^= *a ^= *b ^= *a;
        a++;
        b++;
    }
}

static void swap(Element *arr, int i, int j) {
    memswap(&arr[i], &arr[j], sizeof(Element));
}

static void down(Element *arr, int size, int i, compare cmpFunc) {
    for (int k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if (k + 1 < size && cmpFunc(&arr[k], &arr[k + 1])) {
            k++;
        }
        if (cmpFunc(&arr[k], &arr[(k - 1) / 2])) {
            break;
        }
        swap(arr, k, (k - 1) / 2);
    }
}

PriorityQueue *createPriorityQueue(compare cmpFunc) {
    PriorityQueue *obj = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    obj->capacity = MIN_QUEUE_SIZE;
    obj->arr = (Element *)malloc(sizeof(Element) * obj->capacity);
    obj->queueSize = 0;
    obj->lessFunc = cmpFunc;
    return obj;
}

void heapfiy(PriorityQueue *obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->lessFunc);
    }
}

void enQueue(PriorityQueue *obj, Element *e) {
    if (obj->queueSize == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = realloc(obj->arr, sizeof(Element) * obj->capacity);
    }
    memcpy(&obj->arr[obj->queueSize], e, sizeof(Element));
    for (int i = obj->queueSize;
         i > 0 && obj->lessFunc(&obj->arr[(i - 1) / 2], &obj->arr[i]);
         i = (i - 1) / 2) {
        swap(obj->arr, i, (i - 1) / 2);
    }
    obj->queueSize++;
}

Element *deQueue(PriorityQueue *obj) {
    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->lessFunc);
    Element *e = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;
    return e;
}

bool isEmpty(const PriorityQueue *obj) { return obj->queueSize == 0; }

Element *front(const PriorityQueue *obj) {
    if (obj->queueSize == 0) {
        return NULL;
    } else {
        return &obj->arr[0];
    }
}

void clear(PriorityQueue *obj) { obj->queueSize = 0; }

int size(const PriorityQueue *obj) { return obj->queueSize; }

void freeQueue(PriorityQueue *obj) {
    free(obj->arr);
    free(obj);
}

const int inf = 0x3f3f3f3f;

int minTimeToReach(int **moveTime, int moveTimeSize, int *moveTimeColSize) {
    int n = moveTimeSize, m = moveTimeColSize[0];
    int d[n][m], v[n][m];
    memset(d, 0x3f, sizeof(d));
    memset(v, 0, sizeof(v));

    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    d[0][0] = 0;
    PriorityQueue *q = createPriorityQueue(greater);
    Element e = {0, 0, 0};
    enQueue(q, &e);

    while (!isEmpty(q)) {
        Element *p = front(q);
        Element s = {p->x, p->y, p->dist};
        deQueue(q);
        if (v[s.x][s.y]) {
            continue;
        }
        v[s.x][s.y] = 1;
        for (int i = 0; i < 4; i++) {
            int nx = s.x + dirs[i][0];
            int ny = s.y + dirs[i][1];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }
            int dist = fmax(d[s.x][s.y], moveTime[nx][ny]) + 1;
            if (d[nx][ny] > dist) {
                d[nx][ny] = dist;
                e.x = nx;
                e.y = ny;
                e.dist = dist;
                enQueue(q, &e);
            }
        }
    }
    freeQueue(q);
    return d[n - 1][m - 1];
}