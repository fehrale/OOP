#include <iostream>
#include "include/scaryNum.h"


int main() {

    std::string day;
    int num;

    std::cout << "Enter the day of the week and the number:" << std::endl;

    std::cin >> day >> num; 

    bool res = scaryNum(day, num);
    
    std::cout << res << std::endl; 

    return 0;
}