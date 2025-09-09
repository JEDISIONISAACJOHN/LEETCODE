#define MOD 1000000007

typedef struct {
    int day;
    int count;
} Pair;

typedef struct {
    Pair* data;
    int front;
    int rear;
    int capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (Pair*)malloc(capacity * sizeof(Pair));
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    return queue;
}

int isEmpty(Queue* queue) { return queue->rear < queue->front; }

void enqueue(Queue* queue, Pair item) {
    if (queue->rear == queue->capacity - 1) {
        queue->capacity *= 2;
        queue->data =
            (Pair*)realloc(queue->data, queue->capacity * sizeof(Pair));
    }
    queue->data[++queue->rear] = item;
}

Pair dequeue(Queue* queue) { return queue->data[queue->front++]; }

Pair peek(Queue* queue) { return queue->data[queue->front]; }

void freeQueue(Queue* queue) {
    free(queue->data);
    free(queue);
}

int peopleAwareOfSecret(int n, int delay, int forget) {
    Queue* know = createQueue(n);
    Queue* share = createQueue(n);

    Pair initial = {1, 1};
    enqueue(know, initial);
    int knowCnt = 1, shareCnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!isEmpty(know) && peek(know).day == i - delay) {
            Pair first = dequeue(know);
            knowCnt = (knowCnt - first.count + MOD) % MOD;
            shareCnt = (shareCnt + first.count) % MOD;
            enqueue(share, first);
        }
        if (!isEmpty(share) && peek(share).day == i - forget) {
            Pair first = dequeue(share);
            shareCnt = (shareCnt - first.count + MOD) % MOD;
        }
        if (!isEmpty(share)) {
            knowCnt = (knowCnt + shareCnt) % MOD;
            Pair newPair = {i, shareCnt};
            enqueue(know, newPair);
        }
    }

    freeQueue(know);
    freeQueue(share);

    return (knowCnt + shareCnt) % MOD;
}