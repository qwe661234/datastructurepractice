#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
// 加入 Mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
struct para {
    char path[1000];
    char s[128];
    char msg[1000]; 
};
void querytask(char *path, struct dirent *entry, char *s, char *msg, int rootlen){							
        FILE *fileptr;
        char filech;
        int i;
        char count[30];
        char printfpath[1000] = ".";
        char *dnameptr;
        strcat(path, entry->d_name);								
        fileptr = fopen(path, "r");								
        char filebuf[1000] = "";								
        int filelen = 0;								
        while((filech = getc(fileptr)) != EOF){								
            filebuf[filelen] = filech;								
            filelen ++;								
        }															
        int querycount = 0;								
        int queryloc = 0;								
        while(queryloc <= strlen(filebuf)){								
            char *queryptr = &filebuf[queryloc];								
            int rightcount = 0;								
            for(i = 0; i < strlen(s); i++){								
                if(*(queryptr + i) == s[i]){								
                rightcount ++;								
            }								
        }								
        if(rightcount == strlen(s)){								
            querycount ++;								
        }								
            queryloc ++;								
        }								
        if(querycount != 0){
                dnameptr = &path[rootlen-1];
                strcat(printfpath, dnameptr);
                itoa(querycount, count, 10);
                strcat(msg, "File: ");
                strcat(msg, printfpath);
                strcat(msg, ", Count: ");	
                strcat(msg, count);
                strcat(msg, "\n");						
            }																
    }
void openfd(char *a, struct dirent *entry, char *s, char* msg, int rootlen){	
        strcat(a, entry->d_name);	
        DIR *fold = opendir(a);	
        char temp[1000];
        strncpy(temp, a, strlen(a));
        while( (entry=readdir(fold)) )	
        {	
            if(strstr(entry->d_name, ".txt")){
                strcat(temp, "\\");
                querytask(temp, entry, s, msg, rootlen);
            }else if(strstr(entry->d_name, ".") == NULL){	
                strcat(temp, "\\");
                openfd(temp, entry, s, msg, rootlen);
            }
            memset(temp, '\0', sizeof(temp));
            strncpy(temp, a, strlen(a));
        }	
        closedir(fold);	
    }
void *child(void *arg){
    pthread_mutex_lock( &mutex1 ); // 上鎖
    struct para *paraptr;
    paraptr = (struct para *)arg;
    DIR *folder;								
    struct dirent *entry;												
    folder = opendir(paraptr->path);
    char path[1000];	
    int rootlen;
    if(folder == NULL)								
    {								
        perror("Unable to read directory");								
    }		
    while( (entry=readdir(folder)) )								
    {										
        if(strstr(entry->d_name, ".txt")){	
            memset(path, '\0', sizeof(path));
            strncpy(path, paraptr->path, strlen(paraptr->path));
            strcat(path, "\\");	
            rootlen = strlen(path);			
            querytask(path, entry, paraptr->s, paraptr->msg, rootlen);
        }
        else if(strstr(entry->d_name, ".") == NULL){
                memset(path, '\0', sizeof(path));
                strncpy(path, paraptr->path, strlen(paraptr->path));
                strcat(path, "\\");	
                rootlen = strlen(path);
                openfd(path, entry, paraptr->s, paraptr->msg, rootlen);	
            }			
    }					
    closedir(folder);
    pthread_mutex_unlock( &mutex1 ); // 解鎖
    pthread_exit(NULL);
}
struct thread_pool
{
 pthread_t work_thread;
 char searchjob[128];
 
};
// 主程式
int main(int argc, char *argv[]) {
    struct thread_pool pth[3];
    struct para p[3];
    int msglen = 0;
    strcpy(pth[0].searchjob, "test");
    strcpy(pth[1].searchjob, "cw");
    strcpy(pth[2].searchjob, "as");
    strcpy(p[0].path, "C:\\cygwin64\\home\\qwe66\\data_structure_cy\\txt");
    strcpy(p[0].s, pth[0].searchjob);
    memset(p[0].msg, '\0', sizeof(p[0].msg));
    strcat(p[0].msg, "String: \"");
    strcat(p[0].msg, p[0].s);
    strcat(p[0].msg, "\"\n");
    msglen = strlen(p[0].msg);
    pthread_create(&(pth[0].work_thread), NULL, child, &p[0]);
    pthread_join(pth[0].work_thread, NULL);
    if(strlen(p[0].msg) == msglen){
        strcat(p[0].msg, "Not found\n");
    }
    printf("%s", p[0].msg);
    return 0;
}
//String: “QUERY_STRING”\n 
//File: FILE_PATH, Count: STRING_COUNT\n 
//String: “QUERY_STRING”\n 
//Not found\n
