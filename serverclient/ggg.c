#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <dirent.h>
int checkerrormsg(char *buffer){
    printf("msg : %slen : %d\n", buffer, strlen(buffer));
    if(buffer[6] != '\"'){
        printf("error1\n");
        return 0;
    } 
    if(buffer[strlen(buffer) - 2] != '\"'){
        printf("error2\n");
        return 0;
    }
    int ptrloc = 7;                                     
    char *ptrchr = &buffer[ptrloc];                 
    char *loc = strstr(ptrchr, "\"");
    if(loc == NULL){
        printf("error3 loc=%d\n", ptrloc);
        return 0;
    }                   
    int location;                                                  
    while (1){
        location = loc - ptrchr;                   
        ptrloc = ptrloc + location + 2;                 
        if (ptrloc < (strlen(buffer) - 1)){   
            if(buffer[ptrloc] != '\"'){
                printf("error4 loc = %d\n", ptrloc);
                return 0;       
            }
            ptrloc ++;                  
            ptrchr = &buffer[ptrloc];             
            loc = strstr(ptrchr, "\"");                 
            if(loc == NULL){
                printf("error5 loc = %d\n", ptrloc);
                return 0;
            }
        }else{
            break;                              
        }
    }
    return 1;
};
int main(){
    char buffer[1024] = {0};
    while(1)
    {
        fgets(buffer, 1024, stdin);
        printf("check : %d\n", checkerrormsg(buffer));
    }
}
