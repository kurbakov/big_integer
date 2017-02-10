#ifndef ADDITION_H
#define ADDITION_H

#include <vector>

class Addition{
public:
    Addition();

    std::vector<unsigned short> add_2v(std::vector<unsigned short>, std::vector<unsigned short>);
    std::vector<unsigned short> add_vi(std::vector<unsigned short>, int);
};

Addition::Addition() {}

std::vector<unsigned short> Addition::add_2v(std::vector<unsigned short> left, std::vector<unsigned short> right) 
{
    if(left.size() != right.size())
        throw std::runtime_error("ERROR: Vectors in addition have different size!");

    std::vector<unsigned short> result;
    result.resize(left.size());

    unsigned short carry = 0;
    for(auto i=0; i<left.size(); i++)
    {
        unsigned short data = left[i]+right[i]+carry;
        carry = data/10;
        result[i] = data%10;
    }

    return result;
}

std::vector<unsigned short> Addition::add_vi(std::vector<unsigned short> left, int right) 
{
    std::vector<unsigned short> result;
    result.resize(left.size());

    int carry = 0;
    for(auto i =0; i<left.size(); i++)
    {
        int data = left[i] + right%10 + carry;
        right /= 10;

        carry = data/10;
        result[i] = data%10;
    }

    return result;
}

#endif
