//表頭檔案的名稱建議與類別名稱同名，一個定義良好的類別

#include <string>
using namespace std;

class Ball { 
public: 
    Ball(); 
    Ball(double, const char*); 
    Ball(double, string&); 
    double radius();
    string& name(); 
 
    void radius(double); 
    void name(const char*); 
    void name(string&); 
 
    double volumn(); 

private:
    double _radius; // 半徑 
    string _name; // 名稱 
};

/*Class四階段：
	-	類別(Class)：
		#	類別成員可以是資料(Data)、變數(variable)、函數(Function)、建構子(Constructor)
		#	歸屬於類別的OXOX，皆稱為成員(member)變數(variable)、函數(Function)
		#	至於建構子(Constructor)屬於特別的成員函數，用來建立該類別物件的專屬函數。
		#	
		



*/