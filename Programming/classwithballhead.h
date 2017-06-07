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
