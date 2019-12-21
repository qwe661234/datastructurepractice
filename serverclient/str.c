#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <dirent.h>

int main()
{
    DIR *folder;
    struct dirent *entry;
    int files = 0;
    FILE *fileptr;
    char filech;
    char searchelement[128] = "cw";
    folder = opendir("C:\\cygwin64\\home\\qwe66\\data_structure_cy\\txt.");
    if(folder == NULL)
    {
        perror("Unable to read directory");
    }
    while( (entry=readdir(folder)) )
    {
        files++;
        if(strstr(entry->d_name, "txt")){
            char a[1000] = "C:\\cygwin64\\home\\qwe66\\data_structure_cy\\txt\\";
            strcat(a, entry->d_name);
            fileptr = fopen(a, "r");
            char buffer[1000] = "";
            int filelen = 0;
            while((filech = getc(fileptr)) != EOF){
                buffer[filelen] = filech;
                filelen ++;
            }
            
            //query
            int querycount = 0;
            int queryloc = 0;
            while(queryloc <= strlen(buffer)){
                char *queryptr = &buffer[queryloc];
                int rightcount = 0;
                for(int i = 0; i < strlen(searchelement); i++){
                    if(*(queryptr + i) == searchelement[i]){
                        rightcount ++;
                    }
                }
                if(rightcount == strlen(searchelement)){
                    querycount ++;
                }
                queryloc ++;
                }
            if(querycount == 0){
                printf("not found");
            }else{
                printf("%s \n count = %d\n", a, querycount);
            }
            //
        }
    }
    closedir(folder);
}
