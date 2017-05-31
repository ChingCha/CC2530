#include <iostream> 
using namespace std; 

int* createArray(int);
void deleteArray(int*);

int main() { 
 int m = 0; 

 cout << "陣列大小: "; 
 cin >> m; 

 int *arr = createArray(m); 

 for(int i = 0; i < m; i++) {
 arr[i] = i; 
 }
 
 for(int i = 0; i < m; i++) {
 cout << "arr[" << i << "] = " 
 << arr[i] << endl; 
 }

 deleteArray(arr);

 return 0; 
} 

// 傳回建立的陣列位址
int* createArray(int m) { 
 int *a = new int[m]; 

 for(int i = 0; i < m; i++) {
 a[i] = 0; 
 }

 return a; 
}

void deleteArray(int* arr) {
 delete [] arr; 
}