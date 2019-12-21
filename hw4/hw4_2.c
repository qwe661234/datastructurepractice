#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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
    int main(){
        char member[26][100];
        char group[100] = "";
        char data[100] = "";
        char line[1000] = "";
        char leave[1000] = "";
        char* loc = "";
        int group_exist_count = 0;
        int number_of_group;
        int leave_number = 0;
        int blank_loc;
        int i, j;
            gets(group);
            number_of_group = atoi(group);
            if(number_of_group == 0){
                return -1;
            }
        while(gets(group) != NULL){
            if(strstr(group, "ENQUEUE")){
                int group_number;
                char newcost;
                int len = -1;
                newcost = group[strlen(group) - 1];
                if(strlen(line) == 0){
                    line[0] = newcost;
                    line[1] = '\0';
                }else{
                    group_number = -1;
                    for(i = 0; i < number_of_group; i++){
                        if(strchr(member[i], newcost) != NULL){
                            group_number = i;
                            break;
                        }
                    }
                    if(group_number == -1){
                        len = -1;
                        len = strlen(line);
                        line[len] = newcost;
                        line[len + 1] = '\0';
                    }else{
                        int count = 0;
                        int friend_pos[26] = {-1};
                        for(i = 0; i < strlen(line); i++){
                            if(strchr(member[group_number], line[i]) != NULL){
                                friend_pos[count] = i;
                                count ++;
                            }
                        }
                        if(count == 0){
                            len = -1;
                            len = strlen(line);
                            line[len] = newcost;
                            line[len + 1] = '\0';
                        }else{
                            int min = -1;
                            len = -1;
                            len = strlen(line);
                            min = minimum(friend_pos, count);
                            if(min == 0){
                                for(i = len; i > 0 ; i--){
                                    line[i] = line[i - 1];
                                }
                                line[0] = newcost;
                                line[len + 1] = '\0';
                            }else{
                                for(i = len; i > min; i--){
                                   line[i] = line[i - 1]; 
                                }
                                line[min] = newcost;
                                line[len + 1] = '\0';
                            }
                        }
                    }  
                }  
            }else if(strstr(group, "DEQUEUE")){
                    if(strlen(line) != 0){
                        int len = -1;
                        len = strlen(line);
                        leave[leave_number] = line[0];
                        leave[leave_number + 1] = '\0';
                        leave_number ++;
                        for(i = 0; i < len - 1; i++){
                            line[i] = line[i + 1];
                        }
                        line[len - 1] = '\0';
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
        for(i = 0; i < strlen(leave); i++){
            printf("%c\n", leave[i]);
        }
        return 0;
    }
