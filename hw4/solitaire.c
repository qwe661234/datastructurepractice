#include <stdio.h>
#include <time.h>
#include <stdlib.h>  
struct card{
    int data;
    struct card *next;
};
typedef struct card card;
int check(int b, int* count){
    if(count[b - 1] == 0){
        count[b - 1] = 1;
        return b;
    }else{
        b = rand() % 13 + 1;
        return check(b, count);
    }
};

void putiInArray(int *b){
    int count[13] = {0};
    srand(time(NULL));
    for(int i = 0; i < 13 ; i ++){
        b[i] = rand() % 13 + 1;
        b[i] = check(b[i], count);
    }
};  
  
void printCard(card* head){
        card *ptr1;
        ptr1 = head;
        while(ptr1 != NULL){
            if(ptr1->data == 1){
                printf("A ");
            }else if(ptr1->data == 11){
                printf("J ");
            }else if(ptr1->data == 12){
                printf("Q ");
            }else if(ptr1->data == 13){
                printf("K ");
            }else{
                printf("%d ", ptr1->data);
            }
            ptr1 = ptr1->next;
        }
        printf("\n");
    };

int drawCard(int b, int rightcard){
    if(b == rightcard){
        return 1;
    }else{
        return 0;
    }
};

card* putToButtom(card *head){
    card *ptr2;
    card *temp;
    ptr2 = head;
    while (ptr2->next != NULL)
    {
        ptr2 = ptr2->next;
    }
    temp = head;
    ptr2->next = temp;
    head = head->next;
    temp->next = NULL;
    return head;
};

card* drawOut(card* head){
    card* temp;
    temp = head;
    head = head->next;
    temp->next = NULL;
    free(temp);
    return head;
};

    int main(){
        int b[13];
        int i, j;
        int len = 13;
        card *head = NULL;
        card *ptr;
        card *now;
        card *prev;
        putiInArray(b);
        for(i = 0; i < 13; i++){
            now = (card *)malloc(sizeof(card));
            now->data = b[i];
            now->next = NULL;
            if(head == NULL){
                head = now;
                prev = now;
            }else{
                prev->next = now;
                prev = now;
            }
        }
        while(ptr != NULL){
                for(j = 13; j > 0;){
                ptr = head;
                if(drawCard(ptr->data, j)){
                    j--;
                    printCard(head);
                    head = drawOut(head);
                }else{
                    printCard(head);
                    head = putToButtom(head);   
                }
            }
        }
        printCard(head);
    }