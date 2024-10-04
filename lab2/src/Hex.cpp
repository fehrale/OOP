#include <iostream>
#include "../include/Hex.h"
#include <stdexcept>

void validateDigit(unsigned char digit) {
    if ((digit != 0 && digit < '0') || (digit > '9' && digit < 'A') || digit > 'F') {
        throw std::invalid_argument("Invalid digit");
    }
}

Hex::Hex() : sizeHex{1}, data{new unsigned char[1]{'0'}} {
}

Hex::Hex(const size_t& lengthOfNumber, unsigned char defaultValue) {
    validateDigit(defaultValue);
    sizeHex = lengthOfNumber;
    data = new unsigned char[sizeHex];

    for (size_t i = 0; i < sizeHex; ++i) {
        data[i] = defaultValue;
    }
}

Hex::Hex(const std::initializer_list<unsigned char>& defaultValuesList) {
    sizeHex = defaultValuesList.size();
    data = new unsigned char[sizeHex];

    size_t i = 0;
    for (unsigned char digit : defaultValuesList) {
        validateDigit(digit);
        data[i++] = digit;
    }
}

Hex::Hex(const std::string& defaultValueString) {
    sizeHex = defaultValueString.size();
    data = new unsigned char[sizeHex];

    for (size_t i = 0; i < sizeHex; i++) {
        validateDigit(defaultValueString[i]);
        data[i] = defaultValueString[i];
    }
}

Hex::Hex(const Hex& other) {
    sizeHex = other.sizeHex;
    data = new unsigned char[sizeHex];

    for (size_t i = 0; i < sizeHex; ++i) {
        data[i] = other.data[i];
    }
}

Hex::Hex(Hex&& other) noexcept {
    sizeHex = other.sizeHex;
    data = other.data;
    other.data = nullptr;
    other.sizeHex = 0;
}

Hex& Hex::operator=(const Hex& other) {
    if (this == &other) return *this;

    delete[] data;

    sizeHex = other.sizeHex;
    data = new unsigned char[sizeHex];

    for (size_t i = 0; i < sizeHex; ++i) {
        data[i] = other.data[i];
    }

    return *this;
}

unsigned char Hex::charToHex(unsigned char ch) const {
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    throw std::invalid_argument("Invalid hexadecimal digit");
}

unsigned char Hex::hexToChar(unsigned char hex) const {
    if (hex < 10) return hex + '0';
    return hex - 10 + 'A';
}

Hex& Hex::operator+=(const Hex& other) {
    size_t maxSize = std::max(sizeHex, other.sizeHex) + 1;
    unsigned char* result = new unsigned char[maxSize];
    unsigned char carry = 0;

    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char a = (i < sizeHex) ? charToHex(data[sizeHex - 1 - i]) : 0;
        unsigned char b = (i < other.sizeHex) ? charToHex(other.data[other.sizeHex - 1 - i]) : 0;
        unsigned char sum = a + b + carry;
        carry = sum / 16;
        result[maxSize - 1 - i] = hexToChar(sum % 16);
    }

    delete[] data;
    data = result;
    sizeHex = maxSize;

    while (sizeHex > 1 && data[0] == '0') {
        --sizeHex;
        unsigned char* newData = new unsigned char[sizeHex];
        for (size_t i = 0; i < sizeHex; ++i) {
            newData[i] = data[i + 1];
        }
        delete[] data;
        data = newData;
    }

    return *this;
}

Hex& Hex::operator-=(const Hex& other) {
    if (sizeHex < other.sizeHex) {
        throw std::invalid_argument("Result would be negative");
    }

    unsigned char* result = new unsigned char[sizeHex];
    unsigned char borrowNow = 0;
    unsigned char borrow = 0;

    for (size_t i = 0; i < sizeHex; ++i) {
        unsigned char a = charToHex(data[sizeHex - 1 - i]);
        unsigned char b = (i < other.sizeHex) ? charToHex(other.data[other.sizeHex - 1 - i]) : 0;

        if (a < b + borrowNow) {
            a += 16;
            borrow = 1;
        } else {
            borrow = 0;
        }

        unsigned char diff = a - b - borrowNow;
        result[sizeHex - 1 - i] = hexToChar(diff);
        borrowNow = borrow;
    }

    if (borrow != 0) {
        throw std::invalid_argument("Result would be negative");
    }

    delete[] data;
    data = result;

    while (sizeHex > 1 && data[0] == '0') {
        --sizeHex;
        unsigned char* newData = new unsigned char[sizeHex];
        for (size_t i = 0; i < sizeHex; ++i) {
            newData[i] = data[i + 1];
        }
        delete[] data;
        data = newData;
    }

    return *this;
}

bool Hex::operator==(const Hex& other) const {
    if (sizeHex != other.sizeHex) {
        return false;
    }

    for (size_t i = 0; i < sizeHex; i++) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool Hex::operator<(const Hex& other) const {
    if (sizeHex < other.sizeHex) {
        return true;
    }
    if (sizeHex > other.sizeHex) {
        return false;
    }

    for (size_t i = 0; i < sizeHex; i++) {
        if (data[i] < other.data[i]) {
            return true;
        }
        if (data[i] > other.data[i]) {
            return false;
        }
    }
    return false;
}

bool Hex::operator>(const Hex& other) const {
    if (sizeHex > other.sizeHex) {
        return true;
    }
    if (sizeHex < other.sizeHex) {
        return false;
    }

    for (size_t i = 0; i < sizeHex; i++) {
        if (data[i] > other.data[i]) {
            return true;
        }
        if (data[i] < other.data[i]) {
            return false;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Hex& other) {
    for (size_t i = 0; i < other.sizeHex; ++i) {
        os << other.data[i];
    }
    return os;
}

size_t Hex::getSize() const {
    return sizeHex;
}

Hex::~Hex() noexcept {
    delete[] data;
}
