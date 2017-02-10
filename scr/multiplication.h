#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <vector>

class Multiplication
{
public:
    Multiplication();

    std::vector<unsigned short>
    multiply_2v(std::vector<unsigned short>, std::vector<unsigned short>);

    std::vector<unsigned short int>
    multiply_vi(std::vector<unsigned short>, int);
};

Multiplication::Multiplication(){}

std::vector<unsigned short>
Multiplication::multiply_2v(std::vector<unsigned short> left, std::vector<unsigned short> right) {

    std::vector<unsigned short> result;
    result.resize(std::max(left.size(), right.size()));

    for (auto i = 0; i < left.size()/2; ++i) 
    {
        for (auto j = 0; j < right.size()/2; ++j) 
        {
            result[i + j] += left[i] * right[j];
        }
    }

    for (auto i = 0; i < result.size(); ++i) 
    {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    return result;
}

std::vector<unsigned short>
Multiplication::multiply_vi(std::vector<unsigned short> left, int right){

    std::vector<unsigned short> result;
    result.resize(left.size());

    int carry = 0;
    for(auto i=0; i<left.size(); i++)
    {
        int data = left[i]*right+carry;
        carry = data / 10;
        result[i] = data % 10;
    }

    return result;
}

#endif
