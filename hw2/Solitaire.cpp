#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
   
int check(int b, int* count){
        if(count[b-1] == 0){
            count[b-1] = 1;
            return b;
        }else{
            b = rand() % 13 + 1;
            return check(b, count); // recursive要加return
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
  
void printCard(int* b, int len){
        int i;
        for(i = 0; i < len; i++){
            if(b[i] == 1){
                cout << 'A' << " ";
            }else if(b[i] == 11){
                cout << 'J' << " ";
            }else if(b[i] == 12){
                cout << 'Q' << " ";
            }else if(b[i] == 13){
                cout << 'K' << " ";
            }else{
                cout << b[i] << " ";
            }
        }
        cout << endl;
    };

int drawCard(int b, int card){
        if(b == card){
            return 1;
        }else{
            return 0;
        }
    };

void putToButtom(int* b, int len){
        int i;
        int temp;
        temp = b[0];
        for(i = 0; i < (len - 1); i++){
            b[i] = b[i + 1];
        }
        b[len - 1] = temp;
    };

void drawOut(int* b, int len){
    int i;
    for(i = 0; i < len - 1; i++){
        b[i] = b[i + 1];
    }
    b[len - 1] = 0;
};

    int main(){
        int b[13];
        int i, j;
        int len = 13;
        putiInArray(b);
        for(j = 13; j > 0; j--){
            for(i = 0; i < len;){
                if(drawCard(b[0], j)){
                    printCard(b, len);
                    drawOut(b, len);
                    len --;
                    break;
                }else{
                    printCard(b, len);
                    putToButtom(b, len);
                    i++;
                }
            }
        }
        printCard(b, len);
    }
    
    