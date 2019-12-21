#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
struct queue
{
    int data;
    int activity;
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
queue* activityEnqueue(int vertex, int activity, queue *head){
    queue *now;
    queue *ptr;
    now = (queue *)malloc(sizeof(queue));
    now->data = vertex;
    now->activity = activity;
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
void count_ee(queue* head, int event, int* ee, int* activity){
    queue* ptr;
    ptr = head;
    while(ptr != NULL){    
        if((ee[ptr->data] + activity[ptr->activity]) > ee[event]){
            ee[event] = (ee[ptr->data] + activity[ptr->activity]);
        }
        ptr = ptr->next;
    }
}
void count_le(queue* head, int event, int* le, int* activity){
    queue* ptr;
    ptr = head;
    while(ptr != NULL){    
        if((le[ptr->data] - activity[ptr->activity]) < le[event]){
            le[event] = le[ptr->data] - activity[ptr->activity];
        }
        ptr = ptr->next;
    }
}
int main(){
    int i, activity_number;
    int act, vertex1, vertex2, duration;
    scanf("%d", &activity_number);
    int activity[activity_number + 1];
    int vertex[activity_number + 1];
    int vertex_number = 0;
    queue* processorhead[activity_number + 1];
    queue* listhead[activity_number + 1];
    queue* ptr;
    for(i = 0; i < (activity_number + 1); i++){
        vertex[i] = 0;
        processorhead[i] = NULL;
        listhead[i] = NULL;
    }
    for(i = 0; i < activity_number; i++){
        scanf("%d%d%d%d", &act, &vertex1, &vertex2, &duration);
        if(vertex[vertex1] == 0){
            vertex[vertex1] = 1;
            vertex_number++;
        }
        if(vertex[vertex2] == 0){
            vertex[vertex2] = 1;
            vertex_number++;
        }
        activity[act] = duration;
        processorhead[vertex2] = activityEnqueue(vertex1, act, processorhead[vertex2]);
        listhead[vertex1] = activityEnqueue(vertex2, act, listhead[vertex1]);
    }
    int ee[vertex_number], le[vertex_number];
    int e[activity_number + 1], l[activity_number + 1], slack[activity_number + 1], critical[activity_number + 1]; 
    // for(i = 0; i < vertex_number; i++){
    //     ptr = processorhead[i];
    //     printf("%d", i);
    //     while(ptr != NULL){
    //         printf("pro = %d", ptr->data);
    //         ptr = ptr->next;
    //     }
    //     printf("\n");
    // }
    for(i = 0; i < vertex_number; i++){
        ee[i] = -1;
    }
    ee[0] = 0;
    for(i = 1; i < vertex_number; i++){
        count_ee(processorhead[i], i, ee, activity);
    }
    for(i = 0; i < vertex_number; i++){
        le[i] = ee[vertex_number - 1];
    }
    le[(vertex_number - 1)] = ee[vertex_number - 1];
    for(i = (vertex_number - 2); i >= 0; i--){
        count_le(listhead[i], i, le, activity);
    }
    for(i = 0; i < vertex_number; i++){
        printf("ee[%d] = %d ", i, ee[i]);
        printf("le[%d] = %d\n", i, le[i]);
    }
}