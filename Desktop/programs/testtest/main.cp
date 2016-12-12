//
//  main.cpp
//  testtest
//
//  Created by  WhitePhosphorus on 16/9/16.
//  Copyright © 2016年  WhitePhosphorus. All rights reserved.
//

#include <iostream>
//#include <stdio.h>
using namespace std;
const unsigned int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};

int main(int argc, const char * argv[]) {
    // insert code here...
    unsigned int y1,m1,d1,y2,m2,d2;
    cout << "input two dates split by space" << endl;
    cout << "example: 1998 4 27 2000 3 10" << endl;
    
    cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
    
    while (m1 > 12 || m2 > 12 || d1 > 31 || d2 > 31) {
        cout << "invalid date!" << endl;
        cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
    }
    
    unsigned int date1,date2,md1,md2;
    date1=d1+100*m1+10000*y1;
    date2=d2+100*m2+10000*y2;
    md1=d1+100*m1;
    md2=d2+100*m2;
    if (date2 > date1) { //swap
        date1 = date1 + date2;
        date2 = date1 - date2;
        date1 = date1 - date2;
    }
    
    /*if (y1 == y2) {
        if (m1 == m2) {
            cout << d2-d1 << endl;
        } else {
            
        }
    }*/
    
    unsigned int rst;
    //years
    rst = 365 * ((date1 - date2) / 10000);
    if (md1 < md2) { //beyond a year
        m1+=12;
    }
    //add sum of days in each month
    unsigned int i;
    rst += d1 - d2;
    for (i = m2; i < m1; i++){
        rst += days[i % 12 - 1];
    }
    
    //leap years
    unsigned int tmp1, tmp2;
    tmp2 = (md2 > 300) ? (y2 + 1 + (y2 + 1) % 4) : (y2 + y2 % 4);
    tmp1 = (md1 < 300) ? (y1 - 1 - (y1 - 1) % 4) : (y1 - y1 % 4);
    rst += tmp1 >= tmp2 ? (tmp1 - tmp2) / 4 + 1 : 0;
    
    tmp2 = (md2 > 300) ? (y2 + 1 + (y2 + 1) % 100) : (y2 + y2 % 100);
    tmp1 = (md1 < 300) ? (y1 - 1 - (y1 - 1) % 100) : (y1 - y1 % 100);
    rst -= tmp1 >= tmp2 ? (tmp1 - tmp2) / 100 + 1 : 0;
    
    tmp2 = (md2 > 300) ? (y2 + 1 + (y2 + 1) % 400) : (y2 + y2 % 400);
    tmp1 = (md1 < 300) ? (y1 - 1 - (y1 - 1) % 400) : (y1 - y1 % 400);
    rst += tmp1 >= tmp2 ? (tmp1 - tmp2) / 400 + 1 : 0;
    
    cout << rst << (rst == 1 ? " day" : " days") << endl;
    return 0;
}
