#include <iostream>
#include <string>

#define SIZE 10
#define BASE 10

namespace BigNumber{
class BigUInt{
private:
    void clear();
    void resize(unsigned int);

protected:
    int* value;
    uint64_t buffer;
    uint64_t size;

public:
    BigUInt();
    ~BigUInt();

    uint64_t get_buffer_length(){return buffer;}
    uint64_t get_value_length(){return size;}
    int operator[](unsigned int i){return value[i];}

    void operator=(unsigned int);
    void operator=(BigUInt&);

    // bool operator==(BigUInt&);
    // bool operator!=(BigUInt);
    // bool operator>(BigUInt);
    // bool operator>=(BigUInt);
    // bool operator<(BigUInt);
    // bool operator<=(BigUInt);

    // BigUInt operator+(const BigUInt right);
    // BigUInt operator+(const unsigned int right);

    // BigUInt operator+=(const BigUInt right);
    // BigUInt operator+=(const unsigned int right);

    // BigUInt operator-(const BigUInt right);
    // BigUInt operator-(const unsigned int right);

    // BigUInt operator-=(const BigUInt right);
    // BigUInt operator-=(const unsigned int right);

    // BigUInt operator*(const BigUInt right);
    // BigUInt operator*(const unsigned int right);

    // BigUInt operator*=(const BigUInt right);
    // BigUInt operator*=(const unsigned int right);

    // BigUInt operator/(const BigUInt right);
    // BigUInt operator/(const unsigned int right);

    // BigUInt operator/=(const BigUInt right);
    // BigUInt operator/=(const unsigned int right);

    // BigUInt operator%(const BigUInt right);
    // BigUInt operator%(const unsigned int right);

    // BigUInt operator%=(const BigUInt right);
    // BigUInt operator%=(const unsigned int right);

    std::string to_string();
};

}; // namespace

namespace BigNumber{

void BigUInt::clear(){
    for(int i=0; i<size; i++){
        value[i] = 0;
    }
}

void BigUInt::resize(unsigned int new_size){
    int* temp = value;
    delete value;
    value = new int[new_size];
    buffer = new_size;
    clear();
    for(int i=0; i<size; i++){
        value[i] = temp[i];
    }
    return;
}

BigUInt::BigUInt(){
    value = new int[SIZE];
    clear();
    buffer = SIZE;
    size = 0;
}

BigUInt::~BigUInt(){
    delete value;
}

void BigUInt::operator=(unsigned int x){
    clear();
    size = 0;
    while(x)
    {
        value[size] = x%BASE;
        x /= BASE;
        size++;
    }
}

void BigUInt::operator=(BigUInt & x){
    buffer = x.get_buffer_length();
    size = x.get_value_length();

    delete value;
    value = new int[buffer];
    
    clear();
    for(int i=0; i<size; i++){
        value[i] = x[i];
    }
}


std::string BigUInt::to_string(){
    if(size == 0)
        return std::string("0");

    std::string res;
    for(int i=0; i < size; i++){
        res += std::to_string( value[size-1-i] );
    }
    return res;
}

}; // namespace


int main(){
    BigNumber::BigUInt n;
    n=100;
    std::cout << n.to_string() << "\n";

    BigNumber::BigUInt x;
    x=n;
    std::cout << x.to_string() << "\n";
}
