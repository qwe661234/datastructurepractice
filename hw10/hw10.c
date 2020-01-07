#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
void swap(int*a, int i, int j){
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
void quicksort(int* a, int left, int right){
    if(left < right){
        int i = left;
        int j = right + 1;
        int pivot;
        pivot = a[left];
        do{
            do{
                i++;
            }while(a[i] < pivot);
            do{
                j--;
            }while (a[j] > pivot);
            if(i < j){
                swap(a, i, j);
            }
        }while(i < j);
        swap(a, left, j);
        if((j - 1 - left) < (right - j  - 1)){
            quicksort(a, left, j - 1);
            quicksort(a, j + 1, right);
        }else{
            quicksort(a, j + 1, right);
            quicksort(a, left, j - 1);
        }
    }
}
int selectMiddle(int* a, int left, int right){
    int b[3];
    int middleIndex;
    b[0] = a[left];
    b[1] = a[(left + right) / 2];
    b[2] = a[right];
    quicksort(b, 0, 2);
    if(b[1] == a[left]){
        middleIndex = left;
    }else if(b[1] == a[right]){
        middleIndex = right;
    }else{
        middleIndex = (left + right) / 2;
    }
    return middleIndex;
}
int findMiddle(int* a, int left, int right){
    int i, j, k;
    int pivot, pivotIndex;
    pivotIndex = selectMiddle(a, left, right);
    pivot = a[pivotIndex];
    a[pivotIndex] = -1;
    i = left - 1;
    j = right + 1;
    do{
        do{
            i++;
        }while(a[i] < pivot);
        do{
            j--;
        }while (a[j] > pivot);
        if(i < j){
            swap(a, i, j);
        }
    }while(i < j);
    for(k = 0; k <= right; k++){
        if(a[k] == -1){
            break;
        }
    }
    swap(a, k, j);
    a[j] = pivot;
    return j;
}
void middleQuicksort(int* a, int left, int right){
    int middle;
    if(left < right){
        middle = findMiddle(a, left, right);
        middleQuicksort(a, left, middle - 1);
        middleQuicksort(a, middle + 1, right);
    }
}
int main(int argc, char* argv[]){
    clock_t start, end; 
    double cpu_time_used;
    start = clock(); 
    FILE *fptr;
    int count = 0;
    int i;
    int a[100000];
    fptr = fopen("b.txt", "r");
    while(fscanf(fptr, "%d", &a[count]) != EOF){
        count ++;
    }
    middleQuicksort(a, 0, count - 1);
    printf("%d", count);
    printf("\n");
    end = clock(); 
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; 
    printf("use leftmost and longer fist execution time = %f\n", cpu_time_used);
}