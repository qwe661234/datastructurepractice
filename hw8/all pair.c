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
int relax(queue* head, int* distance1, int* distance2, int vertex, int *processor, int vertex_number){
    int i;
    int change = -1;
    queue* ptr;
    ptr = head;
    while(ptr != NULL){    
        if(ptr->data == vertex){
            for(i = 0; i < vertex_number; i++){
                if(distance2[i] != INT_MAX && distance1[i] > (ptr->weight + distance2[i])){
                        distance1[i] = (ptr->weight + distance2[i]);
                        processor[i] = vertex;
                        change = i;
                    }
                }
            }
        ptr = ptr->next;
    }   
    return change;
}
int main(){
    int i, j;
    int vertex_number;
    int edge_number;
    int vertex1, vertex2, weight, change;
    while(scanf("") != EOF){
        scanf("%d", &vertex_number);
        scanf("%d", &edge_number);
        queue* list_head[vertex_number];
        queue* intermediatehead = NULL;
        queue* ptr;
        int distance[vertex_number][vertex_number];
        int processor[vertex_number][vertex_number];
        char a[100];
        char path[vertex_number][vertex_number][1024];
        for(i = 0; i < vertex_number; i++){
                list_head[i] = NULL;
            }
        for(i = 0; i < vertex_number; i++){
            for(j = 0; j < vertex_number; j++){
                itoa(i , a, 10);
                strncpy(path[i][j], a, sizeof(a)); 
            }
        }
        for(i = 0; i < edge_number; i++){
            scanf("%d%d%d", &vertex1, &vertex2, &weight);
            list_head[vertex1] = weightEnqueue(vertex2, weight, list_head[vertex1]); 
            }
        for(i = 0; i < vertex_number; i++){
            for(j = 0; j < vertex_number; j++){
                distance[i][j] = INT_MAX;
                processor[i][j] = -1;
                if(i == j){
                distance[i][j] = 0;
                processor[i][j] = -1;
                }else{
                    ptr = list_head[i];
                    while(ptr != NULL){
                        if(j == ptr->data){
                            distance[i][j] = ptr->weight;
                            processor[i][j] = i;
                        }
                        ptr = ptr->next;
                    }
                }
            }
        }
        for(i = 0; i < vertex_number; i++){
                intermediatehead = Enqueue(i, intermediatehead);
            }
        ptr = intermediatehead;
        while(ptr != NULL){
            for(i = 0; i < vertex_number; i++){
                change = relax(list_head[i], distance[i], distance[ptr->data], ptr->data, processor[i], vertex_number);
                if(change != -1){
                    itoa(ptr->data, a, 10);
                    strcat(path[i][change], ",");
                    strcat(path[i][change], a);
                }
            }
            ptr = ptr->next;
        }
        for(i = 0; i < vertex_number; i++){
            for(j = 0; j < vertex_number; j++){
                itoa(j, a, 10);
                strcat(path[i][j], ","); 
                strcat(path[i][j], a); 
            }
        }
        for(i = 0; i < vertex_number; i++){
            for(j = 0; j < vertex_number; j++){
                if(distance[i][j] != 0 && distance[i][j] != INT_MAX){
                    printf("%s ", path[i][j]);
                    printf("%d\n", distance[i][j]);
                }
            }
        }
        for(i = 0; i < vertex_number; i++){
            for(j = 0; j < vertex_number; j++){
                memset(path[i][j], 0, sizeof(path[i][j]));
            }
        }
        printf("\n");
    }
}