#include <stdio.h>
#include <pthread.h>

#define MAX_DIGIT 100

int list[MAX_DIGIT];
int n;

typedef struct {
    int start;
    int end;
} ThreadArgs;

void insertion_sort(int start, int end) {
    for (int i = start + 1; i < end; i++) {
        int key = list[i];
        int j = i - 1;
        while (j >= start && list[j] > key) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
}

void* sortt(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    insertion_sort(args->start, args->end);
    pthread_exit(NULL);
}

void* mergee(void* arg) {
    int mid = n / 2;
    int temp[MAX_DIGIT];
    int i = 0, j = mid, k = 0;

    while (i < mid && j < n) {
        if (list[i] < list[j])
            temp[k++] = list[i++];
        else
            temp[k++] = list[j++];
    }
    while (i < mid)
        temp[k++] = list[i++];
    while (j < n)
        temp[k++] = list[j++];

    for (int i = 0; i < n; i++)
        list[i] = temp[i];

    pthread_exit(NULL);
}

int main() {
    printf("Enter number of digits : \n", MAX_DIGIT);
    scanf("%d", &n);
    if (n <= 0 || n > MAX_DIGIT) {
        printf("Unvalid ! \n");
        return 1;
    }

    printf("Enter your digits : \n");
    for (int i = 0; i < n; i++)
        scanf("%d", &list[i]);

    pthread_t t1, t2, t3;
    // t1 for the first half part
    // t2 for the second half part
    // t3 for meerrggiinngg them

    ThreadArgs args1 = {0, n / 2};
    ThreadArgs args2 = {n / 2, n};

    pthread_create(&t1, NULL, sortt, &args1);
    pthread_create(&t2, NULL, sortt, &args2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_create(&t3, NULL, mergee, NULL);
    pthread_join(t3, NULL);

    printf("Sorted List : \n");
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");

    return 0;
}
