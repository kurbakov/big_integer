#ifndef COMPARISION_H
#define COMPARISION_H

#include <vector>

class Comparision{
public:
    Comparision();

    // ==
    bool equal(std::vector<unsigned short>, std::vector<unsigned short>);

    // !=
    bool not_equal(std::vector<unsigned short>, std::vector<unsigned short>);

    // >
    bool greater(std::vector<unsigned short>, std::vector<unsigned short>);

    // >=
    bool greater_equal(std::vector<unsigned short>, std::vector<unsigned short>);

    // <
    bool smaller(std::vector<unsigned short>, std::vector<unsigned short>);

    // <=
    bool smaller_equal(std::vector<unsigned short>, std::vector<unsigned short>);
};

Comparision::Comparision() {}

bool Comparision::equal(std::vector<unsigned short> left, std::vector<unsigned short> right) {
    if(left.size() != right.size())
        throw std::runtime_error("ERROR: Different size of vectors!");

    for(auto i=0; i<left.size(); i++)
        if(left[i] != right[i])
            return false;

    return true;
}

bool Comparision::not_equal(std::vector<unsigned short> left, std::vector<unsigned short> right) {
    if(left.size() != right.size())
        throw std::runtime_error("ERROR: Different size of vectors!");

    for(auto i=0; i<left.size(); i++)
        if(left[i] != right[i])
            return true;

    return false;
}

bool Comparision::greater(std::vector<unsigned short> left, std::vector<unsigned short> right) {
    if(left.size() != right.size())
        throw std::runtime_error("ERROR: Different size of vectors!");

    for(auto i=0; i<left.size(); i++)
        if(left[i] != right[i])
            return left[i] > right[i];

    return false;
}

bool Comparision::greater_equal(std::vector<unsigned short> left, std::vector<unsigned short> right) {
    if(left.size() != right.size())
        throw std::runtime_error("ERROR: Different size of vectors!");

    for(auto i=0; i<left.size(); i++)
        if(left[i] != right[i])
            return left[i] > right[i];

    return true;
}

bool Comparision::smaller(std::vector<unsigned short> left, std::vector<unsigned short> right) {
    if(left.size() != right.size())
        throw std::runtime_error("ERROR: Different size of vectors!");

    for(auto i=0; i<left.size(); i++)
        if(left[i] != right[i])
            return left[i] < right[i];

    return false;
}

bool Comparision::smaller_equal(std::vector<unsigned short> left, std::vector<unsigned short> right) {
    if(left.size() != right.size())
        throw std::runtime_error("ERROR: Different size of vectors!");

    for(auto i=0; i<left.size(); i++)
        if(left[i] != right[i])
            return left[i] < right[i];

    return true;
}

#endif

