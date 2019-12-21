#include <stdio.h>
#include <stdlib.h>

struct element{
    int value;
};
typedef struct element element;

void push(element *seat, element *heap, int *heapnumber, int n){   
    int i;
    if(*heapnumber == n){
        fprintf(stderr, "heap is full");
        exit(0);
    }
    i = ++ (*heapnumber);
    while(i != 1 && seat->value > heap[i/2].value){
        heap[i] = heap[i /2];
        i = i / 2;
    }
    heap[i] = *seat;
}
element pop(element *heap, int *heapnumber){
    int parent, child;
    element head, temp;
    if(*heapnumber == 0){
        fprintf(stderr, "heap is empty");
        exit(0);
    }
    head = heap[1];
    temp = heap[*heapnumber];
    (*heapnumber) --;
    parent = 1;
    child = 2;
    while(child <= *heapnumber){
        if(child < *heapnumber && heap[child].value < heap[child + 1].value){
            child ++;
        }
        if(heap[child].value < temp.value){
            break;
        }
        heap[parent] = heap[child];
        parent = child;
        child = 2 * child;
    }
    heap[parent] = temp;
    return head;
}
int main(int argc, const char *argv[]){ 
        int a[10];
        int indexa = 0;
        int testcase;
        int i;
        scanf("%d", &testcase);
        while(testcase != 0){
            int fans = 0;
            int n = 0;
            int total = 0;
            int heapnumber = 0;
            element temp;
            element *heap;
            element *now;
            int *vacancy;
            scanf("%d%d", &n, &fans);
            vacancy = (int *)malloc((n + 1) * sizeof(int));
            for(i = 1; i <= n; i++){
                scanf("%d", &vacancy[i]);
            }
            heap = (element *)malloc((n + 1) * sizeof(element));
            for(i  = 1; i <= n; i++){
                now = (element *)malloc(sizeof(element));
                now->value = *(vacancy + i);
                push(now, heap, &heapnumber, n);
            }
            for(i = 1; i <= fans; i++){
                temp = pop(heap, &heapnumber);
                total += temp.value;
                temp.value --;
                now = (element *)malloc(sizeof(element));
                now->value = temp.value;
                push(now, heap, &heapnumber, n);
            }
            a[indexa] = total;
            indexa ++;
            testcase --;
        }
        for(i = 0; i < indexa; i++){
            printf("%d\n", a[i]);
        }
    }