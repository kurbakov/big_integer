#ifndef NUMBER_H
#define NUMBER_H

#include <vector>
#include "multiplication.h"
// #include "division.h"

enum Sign{positive, negative};

class Number{
private:
    Sign sign;
    std::vector<unsigned short int> data;
    unsigned long long size;

    void resize();

public:
    Number();
    Number(long long);

    // Number operator+(const Number right);
    // Number operator+(const int right);

    // Number operator-(const Number right);
    // Number operator-(const int right);

    Number operator=(const Number right);

    // bool operator==(const Number right);
    // bool operator!=(const Number right);
    // bool operator>(const Number right);
    // bool operator>=(const Number right);
    // bool operator<(const Number right);
    // bool operator<=(const Number right);

    Number operator*(const Number right);
    Number operator*(const int right);

    // Number operator/(const Number right);
    // Number operator/(const int right);

    // Number operator%(const Number right);
    // Number operator%(const int right);

    void print();

protected:
    int SIZE = 64;
    int BIAS = 10;
};

// Constructors
Number::Number()
{
    sign = positive;
    data.resize(SIZE);
    size = 0;
}

Number::Number(long long d) 
{
    if(d>=0) 
    {
        sign = positive;
    }
    else 
    {
        sign = negative;
        d *= -1;
    }
    data.resize(SIZE);

    size = 0;
    while(d)
    {
        data[size] = d%10;
        d /= 10;
        size++;
    }
}

// Help functions
void Number::print() 
{
    if(sign == negative)
        std::cout << "-";

    for(int i=size-1; i>=0; --i) 
    {
        std::cout << data[i];
    }
    std::cout << std::endl;
}


// operator overloading

Number Number::operator=(const Number right) {

    this->sign = right.sign;
    this->size = right.size;

    for(auto i=0; i<right.data.size(); i++)
        this->data[i] = right.data[i];

    return *this;
}


Number Number::operator*(const Number right){
    Number result;

    if(this->sign != right.sign)
        result.sign = negative;
    else
        result.sign = positive;

    Multiplication m;
    result.data = m.multiply_2v(this->data, right.data);

    result.size = SIZE;
    while(result.data[result.size-1] == 0) {result.size--;}

    return result;
}

Number Number::operator*(const int right){
    Number result;
    result.sign = this->sign;

    Multiplication m;
    result.data = m.multiply_vi(this->data, right);

    result.size = SIZE;
    while(result.data[result.size-1] == 0) 
    {
        result.size--;
    }

    return result;
}

#endif
