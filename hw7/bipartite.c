#include <stdio.h>
#include <stdlib.h>

struct queue
{
    int data;
    struct queue *next; 
};
typedef struct queue queue;
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
int isBipartite(int vertex_number, queue **list_head){
    int i;
    int color[vertex_number];
    int processor[vertex_number];
    queue* ptr;
    for(i = 0; i < vertex_number; i++){
        color[i] = 0;
        processor[i] = -1;
    }
    for(i = 0; i < vertex_number; i++){
        if(color[i] == 0){
            if(processor[i] != -1){
                color[i] = (color[processor[i]] + 1) % 2; 
            }else{
                color[i] = 0;
            }
            ptr = list_head[i];
            while(ptr != NULL){
                if(color[ptr->data] == 0 && processor[ptr->data] == -1){
                    processor[ptr->data] = i;
                }
                ptr = ptr->next;
            }
        }
    }
    for(i = 0; i < vertex_number; i++){
        ptr = list_head[i];
        while(ptr != NULL){
            if(color[i] == color[ptr->data]){
                return 0;
            }
            ptr = ptr->next;
        }
    }
    return 1;
}
void BFS(int vertex_number, queue **list_head, int* distance){
    int color[vertex_number];
    int processor[vertex_number];
    int i;
    queue *ptr;
    for(i = 0; i < vertex_number; i++){
        color[i] = 0;
        processor[i] = -1;
        distance[i] = -1;
    }
    for(i = 0; i < vertex_number; i++){
        if(color[i] == 0){
            color[i] = 1;
            if(processor[i] != -1){
                distance[i] = distance[processor[i]] + 1; 
            }else{
                distance[i] = 0;
            }
            ptr = list_head[i];
            while(ptr != NULL){
                if(color[ptr->data] == 0 && processor[ptr->data] == -1){
                    processor[ptr->data] = i;
                }
                ptr = ptr->next;
            }
        }
    }
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
    if(isBipartite(vertex_number, list_head)){
        printf("true\n");
        BFS(vertex_number, list_head, distance);
        for(i = 0; i < vertex_number; i++){
            if(distance[i] % 2 == 0){
                printf("%d ", i);
            }
        }
        printf("\n");
        for(i = 0; i < vertex_number; i++){
            if(distance[i] % 2 == 1){
                printf("%d ", i);
            }
        }
    }else{
        printf("false\n");
    }
    return 0;
}