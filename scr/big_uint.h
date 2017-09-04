#ifndef SRC_BIG_UINT
#define SRC_BIG_UINT

#include <iostream>
#include <string>

#define SIZE 10
#define BASE 10

namespace BigNumber{
class BigUInt{
private:
    int* value;
    uint64_t size;
    void LevelUp();

public:
    BigUInt();
    BigUInt(int*, uint64_t);
    BigUInt(const BigUInt&);

    ~BigUInt();
    uint64_t get_size() const {return size;}
    int& operator[](unsigned int i) const {return value[i];}

    void operator=(unsigned int);
    void operator=(const BigUInt&);

    bool operator==(const BigUInt&);
    bool operator!=(const BigUInt&);
    bool operator>(const BigUInt&);
    bool operator>=(const BigUInt&);
    bool operator<(const BigUInt&);
    bool operator<=(const BigUInt&);

    BigUInt operator+(unsigned int);
    BigUInt operator+(const BigUInt&);

    BigUInt operator-(unsigned int);
    BigUInt operator-(const BigUInt&);

    BigUInt operator*(unsigned int);
    BigUInt operator*(const BigUInt&);

    BigUInt operator/(unsigned int);
    BigUInt operator/(const BigUInt&);
    
    int operator%(unsigned int);
    BigUInt operator%(const BigUInt&);

    std::string to_string();
};

}; // namespace

#endif