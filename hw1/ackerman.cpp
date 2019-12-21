#include<iostream> 
using namespace std;
	int A(int m, int n) {
			int result = int();
			if (m == 0){
				result = n + 1;
			}else if (n == 0){
				return A(m - 1, 1);
			}else{
				return A(m-1, A(m, n-1));
			}
			return result;
		};
	int main(){
		while(!cin.eof()){
		int m = int();
		int n = int();
		cin >> m >> n;
		cout << A(m, n) << endl;
		}
		
		return 0;
	}
