#include<iostream> 	//Basic I/O Lib
#include <typeinfo> //check type
//include<cstdlib>	//System ("PAUSE") Lib
//#include<stdio.h>	//stdio.h包含了print
using namespace std;	//C++的標準函式庫皆定義在std名稱空間中



int main(){
	
	int a = 5;
	
	cout << "a" <<a<< "\n";
	cout << "a address:"<<&a<<"\n";
	//i means integer on your compiler
	cout << typeid(&a).name()<<"\n";
	
	
	return 0;
	
}