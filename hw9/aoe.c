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
// void relax(queue* head, int vertex, int* distance, int *processor, char  (*path)[1024]){
//     queue* ptr;
//     ptr = head;
//     while(ptr != NULL){    
//         if(distance[ptr->data] > (distance[vertex] + ptr->weight)){
//             distance[ptr->data] = distance[vertex] + ptr->weight;
//             processor[ptr->data] = vertex;
//         }
//         ptr = ptr->next;
//     }
// }
int main(){
    int i, activity_number;
    int act, vertex1, vertex2, duration;
    scanf("%d", &activity_number);
    int activity[activity_number + 1];
    int vertex[activity_number + 1];
    int vertex_number = 0;
    queue* listhead[activity_number + 1];
    queue* ptr;
    for(i = 0; i < (activity_number + 1); i++){
        vertex[i] = 0;
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
        listhead[vertex1] = activityEnqueue(vertex2, act, listhead[vertex1]);
    }
    for(i = 0; i < vertex_number; i++){
        
    }
}