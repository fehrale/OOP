#pragma once
#include <initializer_list>
#include <string>
#include <stdexcept>

void validateDigit(unsigned char digit);

class Hex {
public:
    Hex();
    Hex(const size_t& lengthOfNumber, unsigned char defaultValue = 0);
    Hex(const std::initializer_list<unsigned char>& defaultValuesList);
    Hex(const std::string& defaultValueString);
    Hex(const Hex& other);
    Hex(Hex&& other) noexcept;
    ~Hex() noexcept;

    Hex& operator=(const Hex& other);
    Hex& operator+=(const Hex& other);
    Hex& operator-=(const Hex& other);
    bool operator==(const Hex& other) const;
    bool operator<(const Hex& other) const;
    bool operator>(const Hex& other) const;

    size_t getSize() const;
    friend std::ostream& operator<<(std::ostream& os, const Hex& hex);

private:
    unsigned char* data;
    size_t sizeHex;

    unsigned char charToHex(unsigned char ch) const;
    unsigned char hexToChar(unsigned char hex) const;
};
