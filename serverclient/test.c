#include<stdio.h>
#include<stdlib.h>
    struct link
{
    int data;
    struct link *next;
};
typedef struct link link;
int main(){
    int a[5]={1,2,3,4,5};
    link *now;
    link *prev;
    link *head = NULL;
    int i;
    for(i = 0; i< 5; i++){
        now = (link *)malloc(sizeof(link));
        now->next = NULL;
        now->data = a[i];
        if(head == NULL){
            head = now;
            prev = now;
        }else{
            prev->next = now;
            prev = now;
        }
    }
    
    now = head;
    while(now != NULL){ 
        link* temp;
        temp = now->next;
        now = now->next;
        free(temp);
        printf("%d\n", temp->data);
    }
    
    return 0;
}