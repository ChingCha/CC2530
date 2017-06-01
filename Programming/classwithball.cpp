#include <string>
#include "Ball.h"
using namespace std;

/*預設建構函式(Constructor)
它沒有傳回值
作用在於物件生成時自動初始一些必要的資訊
*/

//::」稱之為類別範圍解析（Class scope resolution）運算子
Ball::Ball() {//在不指定引數的情況下，會將 radius設定為0，而name設定為"noname ball"
    _radius = 0.0; 
    _name = "noname ball"; 
}

Ball::Ball(double radius, const char *name) { 
    _radius = radius; 
    _name = name;
}

Ball::Ball(double radius, string &name) { 
    _radius = radius; 
    _name = name;
}

double Ball::radius() { 
    return _radius; 
} 

double Ball::volumn() { 
    return (4 / 3 * 3.14159 * _radius * _radius * _radius); 
} 

string& Ball::name() { 
    return _name; 
} 

void Ball::radius(double radius) { 
    _radius = radius; 
} 

void Ball::name(string &name) { 
    _name = name; 
}

void Ball::name(const char *name) { 
    _name = name; 
}