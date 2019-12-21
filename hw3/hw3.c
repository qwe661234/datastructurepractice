#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct costcoline{
    char customer;
    struct costcoline *next;
};
int minimum(int a[], int num){
    int min = a[0];
    int i;
    for(i = 1; i < num; i++){
        if(a[i] < min){
            min = a[i];
        }
    }
    return min;
}  
        
typedef struct costcoline line;
    int main(){
        char member[26][100];
        char group[100] = "";
        char data[100] = "";
        char leave[] = "";
        char* loc = "";
        int group_exist_count = 0;
        int number_of_group;
        int leave_number = 0;
        int blank_loc;
        int i, j;
        line *head = NULL;
        line *now;
        line *ptr;
        gets(group);
        number_of_group = atoi(group);
        if(number_of_group == 0){
            return -1;
        }
        while(gets(group) != NULL){
            if(strstr(group, "ENQUEUE")){
                int group_number = -1;
                now = (line *)malloc(sizeof(line));
                now->next = NULL;
                now->customer = group[strlen(group) - 1];
                if(head == NULL){
                    head = now;
                }else{
                    group_number = -1;
                    for(i = 0; i < number_of_group; i++){
                        if(strchr(member[i], now->customer) != NULL){
                            group_number = i;
                            break;
                        }
                    }
                    if(group_number == -1){
                        ptr = head;
                        while(ptr->next != NULL){
                                ptr = ptr->next;
                            }
                        ptr->next = now;
                    }else{
                        ptr = head;
                        int pos = 0;
                        int count = 0;
                        int friend_pos[26] = {-1};
                        while(ptr != NULL){
                            if(strchr(member[group_number], ptr->customer) != NULL){
                                friend_pos[count] = pos;
                                count ++;
                            }
                            ptr = ptr->next;
                            pos ++;
                        }
                        if(count == 0){
                            ptr = head;
                            while(ptr->next != NULL){
                                ptr = ptr->next;
                            }
                            ptr->next = now;
                        }else{
                            int min = -1;
                            min = minimum(friend_pos, count);
                            ptr = head;
                            if(min == 0){
                                now->next = ptr;
                                head = now;
                            }else{
                                ptr = head;
                                for(i = 0; i < (min - 1); i ++){
                                    ptr = ptr->next;
                                }
                                now->next = ptr->next;
                                ptr->next = now;
                            }
                        }
                    }   
                }
            }else if(strstr(group, "DEQUEUE")){
                    if(head != NULL){
                        ptr = head;
                        leave[leave_number] = ptr->customer;
                        leave_number ++;
                        head = head->next;
                    }
            }else{
                    if(group_exist_count == number_of_group){
                        printf("group is full");
                    }
                    else{
                        loc = strstr(group, " ");
                        blank_loc = loc - group;
                        for(j = 0; j < (strlen(group) - blank_loc - 1); j++){
                            data[j] = group[j + blank_loc + 1];
                        }
                        strncpy(member[group_exist_count], data, (strlen(group) - blank_loc));
                        group_exist_count ++;
                    }
                }
        }
        for(i = 0; i < leave_number; i++){
            printf("%c\n", leave[i]);
        }
        return 0;
    }