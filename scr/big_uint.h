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
    void LevelUp()
    {
        for (int i = SIZE-1;i>=1;i--){
            value[i] = value[i-1];
        }
        
        size = SIZE;
        while(value[size-1] && size>0) size--;
    }

public:
    BigUInt();
    BigUInt(int*, uint64_t);
    BigUInt(const BigUInt&);

    ~BigUInt();
    uint64_t get_value_length() const {return size;}
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

    // ostream &operator<<(const BigUInt&);
    // istream &operator>>(const BigUInt&);

    std::string to_string();
};

}; // namespace

#endif