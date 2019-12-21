#include<iostream>
#include<math.h>
#include<string>
using namespace std;

void printSet(string *set,int size){
	int i, j = int();
	int set_number = pow(2, size);
	for(i = 0; i < set_number; i++){
		string str = "";
		for(j = 0; j < size; j++){
			if(i & (1 << j)){
				str = str + set[j] + " "; 
			}
		}
		if (str.size()){
			str[str.size() - 1] = '}';
		}else{
			str = "}";
		}
		str = "{" + str;
		cout << str << endl;
	}
}

int main(){
	int i = int();
	string a[10] = {};
	while (!cin.eof()){
		cin >> a[i];
		i++;
	}
	i--;
	printSet(a, i);
	return 0;
}
