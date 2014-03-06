//
//  myFunc.cpp
//  HelloCpp
//
//  Created by ck02-084 on 14-3-6.
//
//

#include "myFunc.h"
string numberToStr(int n){//整数转string
    char numbuf[128];
    sprintf(numbuf, "%i", n);//xcode中没有itoa
    string numStr=numbuf;
    return numStr;
}
