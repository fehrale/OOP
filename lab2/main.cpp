#include <iostream>
#include "include/Hex.h"

int main() {
    size_t lengthNumber;
    std::cout << "Введите длину первого числа: ";
    std::cin >> lengthNumber;

    unsigned char defaultValue;
    std::cout << "Введите значение по умолчанию для первого числа (0-9, A-F): ";
    std::cin >> defaultValue;

    Hex number1;

    try {
        number1 = Hex(lengthNumber, defaultValue);
        std::cout << "Первое число: ";
        std::cout << number1 << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Введите 3 цифры для второго числа (от 0 до 9, A-F): ";
    unsigned char arrayNumbers[3];
    for (int i = 0; i < 3; ++i) {
        std::cin >> arrayNumbers[i];
    }

    Hex number2;
    try {
        number2 = Hex({arrayNumbers[0], arrayNumbers[1], arrayNumbers[2]});
        std::cout << "Второе число: ";
        std::cout << number2 << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::string stringNumber;
    std::cout << "Введите строку из цифр для третьего числа (от 0 до 9, A-F): ";
    std::cin >> stringNumber;

    Hex number3;
    try {
        number3 = Hex(stringNumber);
        std::cout << "Третье число: ";
        std::cout << number3 << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    Hex sumResult = number1;
    sumResult += number2;
    std::cout << "Сумма Число 1 + Число 2: ";
    std::cout << sumResult << std::endl;

    Hex subResult = number3;
    try {
        subResult -= number2;
        std::cout << "Разность Число 3 - Число 2: ";
        std::cout << subResult << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    Hex copyOfNumber1 = number1;
    std::cout << "Копия Числа 1: ";
    std::cout << copyOfNumber1 << std::endl;

    Hex movedNumber = std::move(number2);
    std::cout << "Перемещенное Число 2: ";
    std::cout << movedNumber << std::endl;

    std::cout << "Сравнение: " << std::endl;
    std::cout << "Число 1 == Копия Числа 1: " << (number1 == copyOfNumber1) << std::endl;
    std::cout << "Число 1 < Число 3: " << (number1 < number3) << std::endl;
    std::cout << "Число 3 > Число 1: " << (number3 > number1) << std::endl;

    return 0;
}
