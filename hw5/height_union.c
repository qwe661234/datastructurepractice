#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct queue
{
    int data;
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
void heightUnion(int tree_number, int *root, int *processor, int *tree_height, int r1, int r2){
    int t1, t2, i;
    for(i = 0; i < tree_number; i++){
        if(root[i] == r1){
            t1 = i;
            break;
        }
    }
    for(i = 0; i < tree_number; i++){
        if(root[i] == r2){
            t2 = i;
            break;
        }
    }
    if(tree_height[t1] > tree_height[t2]){
        processor[r1] = r2;
        tree_height[t1] = 0;
    }else if(tree_height[t1] == tree_height[t2]){
        processor[r2] = r1;
        tree_height[t1] --;
        tree_height[t2] = 0;
    }else{
        processor[r2] = r1;
        tree_height[t2] = 0; 
    }
}

int collapsingFind(int *processor, int node, int node_number){
    int i;
    int traverse_count = 0;
    int reset;
    for(i = node; processor[i] >= 0; i = processor[i]){
        traverse_count ++;
    }
    if(processor[node] == i){
        reset = 0;
    }else{
        processor[node] = i;
        reset = 1;
        for(i = 0; i < node_number; i++){
            if(processor[i] == node){
                reset ++;
            }
        }           
    }
    traverse_count += reset;
    return traverse_count;
}
int node(char* operate, int location, int end){
    char node[3];
    int i, n;
    for(i = location; i < end; i++){
        node[i - location] = operate[i];
         n = atoi(node);
    }
    return n;
}
int main(){
    queue *head = NULL;
    queue *ptr;
    char operate[20] = "";
    int tree_number, parent, child, i, j;
    int node_number;
    int processor[101];
    scanf("%d", &tree_number);
    int root[tree_number];
    int tree_height[tree_number];
    int node_of_tree[tree_number];
    for(i = 0; i < tree_number; i++){
        scanf("%d", &node_of_tree[i]);
        scanf("%d%d", &root[i], &tree_height[i]);
        processor[root[i]] = -1;
        for(j = 0; j < (node_of_tree[i] - 1); j++){
            scanf("%d%d", &child, &parent);
            processor[child] = parent;
        }
    }
    for(i = 0; i < tree_number; i++){
        node_number += node_of_tree[i];
    }
    getchar();
    while(gets(operate) != NULL){
        if(strstr(operate, "UNION")){
            int n1, n2;
            char* loc = NULL;
            int location;
            char *temp = &operate[6];
            loc = strchr(temp, ' ');
            location = loc - operate;
            n1 = node(operate, 6, location);
            n2 = node(operate, location + 1, strlen(operate));
            heightUnion(tree_number, root, processor, tree_height, n1, n2);
        }else if(strstr(operate, "FIND")){
            int n, result;
            n = node(operate, 5, strlen(operate));
            result = collapsingFind(processor, n, node_number);
            head = Enqueue(result, head);
        }else{
            ptr = head;
            while(ptr != NULL){
                printf("%d\n", ptr->data);
                ptr = ptr->next;
            }
            return 0;
        }
    }
}