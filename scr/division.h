// http://cppalgo.blogspot.de/2010/08/div-mod_29.html

#ifndef DIVISION_H
#define DIVISION_H

#include <vector>
#include <iostream>

#include "multiplication.h"

class division
{
public:
    division();

    bool is_null(std::vector<unsigned short>);
    void level_up(std::vector<unsigned short>);

    std::vector<unsigned short>
    divide(std::vector<unsigned short>, std::vector<unsigned short>);
};

division::division() {}

bool division::is_null(std::vector<unsigned short> v)
{
    for(unsigned int i=0; i<v.size(); ++i)
        if(v[i] != 0) return true;

    return false;
}

void division::level_up(std::vector<unsigned short> v)
{
    for (auto i = v.size(); i>=1; i--)
        v[i] = v[i-1];
}

std::vector<unsigned short int>
division::divide(std::vector<unsigned short int> left, std::vector<unsigned short int>  right)
{
    // check right != 0
    if(is_null(right))
        throw std::runtime_error("ERROR: Division by 0");

    std::vector<unsigned short int> result;
    std::vector<unsigned short int> modulo;

    for (auto i = left.size()-1; i>=0; i--)
    {
        level_up(modulo);
        modulo[0] = left[i];

        unsigned short x=0;
        int l=0;
        int r=10; // BASE
        while(l <= r){
            int mid = (l+r)/2;
            auto cur = right * mid;
        }

        result[i] = x;
        modulo = modulo - right * x;
    }

    return result;
}



#endif