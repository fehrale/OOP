#include "../include/scaryNum.h"


bool scaryNum(std::string d, int n) {
    if (d == "Monday") {
        return (n == 12);
    } else if (d == "Tuesday") {
        return (n > 95);
    } else if (d == "Wednesday") {
        return (n == 34);
    } else if (d == "Thursday") {
        return (n == 0);
    } else if (d == "Friday") {
        return (n % 2 == 0);
    } else if (d == "Saturday") {
        return (n == 56);
    } else if (d == "Sunday") {
        return (n == -666 || n == 666);
    }
    return false;
}