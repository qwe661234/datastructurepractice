#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct queue
{
    int data;
    int weight;
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
queue* weightEnqueue(int vertex, int weight, queue *head){
    queue *now;
    queue *ptr;
    now = (queue *)malloc(sizeof(queue));
    now->data = vertex;
    now->weight = weight;
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
queue* Dequeue(int target, queue *head){
    queue* ptr;
    queue* temp;
    int count = 0;
    int i;
    ptr = head;
    while(ptr != NULL){
        if(ptr -> data == target){
            break;
        }
        count ++;
        ptr = ptr->next;
    }
    if(count == 0){
        
        temp = head;
        head = head->next;
        free(temp);
    }else{
        ptr = head;
        for(i = 0; i < (count - 1); i++){
            ptr = ptr->next;
        }
        temp = ptr->next;
        ptr->next = temp->next;
        free(temp);
    }
    return head;
}
void relax(queue* head, int vertex, int* distance, int *processor, char  (*path)[1024]){
    queue* ptr;
    char a[100];
    ptr = head;
    while(ptr != NULL){    
        if(distance[ptr->data] > (distance[vertex] + ptr->weight)){
            distance[ptr->data] = distance[vertex] + ptr->weight;
            processor[ptr->data] = vertex;
            strncpy(path[ptr->data], path[vertex], strlen(path[vertex]));
            strcat(path[ptr->data], ",");
            itoa( ptr->data, a, 10);
            strcat(path[ptr->data], a);
        }
        ptr = ptr->next;
    }
}
int minimum(int* distance, queue* head){
    queue* ptr;
    ptr = head;
    int mindistance = distance[ptr->data];
    int minvertex = ptr->data;
    while(ptr != NULL){ 
        if(mindistance > distance[ptr->data]){
            mindistance = distance[ptr->data];
            minvertex = ptr->data;
        }
        ptr= ptr->next;
    }
    return minvertex;
} 
int main(){
        int i;
        int vertex_number;
        int edge_number;
        int vertex1, vertex2, weight;
        int min; 
        while(scanf("") != EOF){
        scanf("%d", &vertex_number);
        scanf("%d", &edge_number);
        queue* taskhead = NULL;
        queue* completehead = NULL;
        queue* list_head[vertex_number];
        queue* ptr;
        char path[vertex_number][1024];
        int distance[vertex_number];
        int processor[vertex_number];
        for(i = 0; i < vertex_number; i++){
            taskhead =  Enqueue(i, taskhead);
            list_head[i] = NULL;
            distance[i] = INT_MAX;
            processor[i] = -1;
        }
        for(i = 0; i < edge_number; i++){
            scanf("%d%d%d", &vertex1, &vertex2, &weight);
            list_head[vertex1] = weightEnqueue(vertex2, weight, list_head[vertex1]); 
        }
        taskhead = Dequeue(0, taskhead);
        completehead = Enqueue(0, completehead);
        distance[0] = 0;
        strcpy(path[0], "0");
        relax(list_head[0], 0, distance, processor, path);
        for(i = 0; i < (vertex_number - 1); i++){
            min = minimum(distance, taskhead); 
            if(distance[min] != INT_MAX){  
                taskhead = Dequeue(min, taskhead);
                completehead = Enqueue(min, completehead);
                relax(list_head[min], min, distance, processor, path);
            }
        }
        for(i = 1; i < vertex_number; i++){
            if(distance[i] == INT_MAX){
                printf("Impossible\n");
            }else{
                printf("%s", path[i]);
                printf(" %d\n", distance[i]);
            }
        }
        for(i = 0; i < vertex_number; i++){
            memset(path[i], 0, sizeof(path[i])); 
        }
        printf("\n");
    }
    return 0;
}