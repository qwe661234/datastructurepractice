#include <stdio.h>
#include <stdlib.h>
struct queue
{
    int data;
    struct queue *next; 
};
typedef struct queue queue;
void printqueue(queue *head){
    queue* ptr;
    ptr = head;
    while(ptr != NULL){
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}
queue* Enqueue(int vertex, queue *head){
    queue *now;
    queue *ptr;
    now = (queue *)malloc(sizeof(queue));
    now->data = vertex;
    now->next = NULL;
    ptr = head;
    if(head == NULL){
        head = now;
    }else{ 
        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        ptr->next = now;
    }
    return head;
}
queue* Dequeue(queue *head){
    queue *ptr;
    ptr = head;
    head = head->next;
    free(ptr);
    return head;
}
void DFS(int vertex_number, queue **list_head){
    int color[vertex_number];
    int processor[vertex_number];
    int discover[vertex_number];
    int time = 0;
    int i;
    int visit;
    queue *ptr;
    for(i = 0; i < vertex_number; i++){
        color[i] = 0;
        processor[i] = -1;
        discover[i] = -1;
    }
    visit = 0;
    color[visit] = 1;
    discover[visit] = time;
    time++;
    ptr = list_head[visit];
    while(time > vertex_number){
        if(ptr != NULL){
            if(color[ptr->data] == 0){
                color[ptr->data] = 1;
                processor[ptr->data] = visit;
                discover[ptr->data] = time;
                time ++;
                visit = ptr->data;
                ptr = list_head[ptr->data];
            }else{
                ptr = ptr->next;
            }
        }else{
            visit = processor[visit];
        }
    }
    for(i = 0; i < vertex_number; i++)
        printf("%d", discover[i]);
} 
int main(){
    int i;
    int vertex_number;
    int edge_number;
    int vertex1, vertex2;
    scanf("%d", &vertex_number);
    scanf("%d", &edge_number);
    queue* list_head[vertex_number];
    int distance[vertex_number];
    for(i = 0; i < vertex_number; i++){
        list_head[i] = NULL;
    }
    for(i = 0; i < edge_number; i++){
        scanf("%d%d", &vertex1, &vertex2);
        list_head[vertex2] = Enqueue(vertex1, list_head[vertex2]);
        list_head[vertex1] = Enqueue(vertex2, list_head[vertex1]);   
    }
    DFS(vertex_number, list_head);
}