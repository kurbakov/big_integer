#include <iostream>
#include <string>

#define SIZE 10
#define BASE 10

namespace BigNumber{
class BigUInt{
private:
    void clear();
    void resize(unsigned int);

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

    void operator<<(BigUInt&);

    bool operator==(BigUInt&);
    bool operator!=(BigUInt&);
    bool operator>(BigUInt&);
    bool operator>=(BigUInt&);
    bool operator<(BigUInt&);
    bool operator<=(BigUInt&);

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
        this->value[i] = 0;
    }
}

void BigUInt::resize(unsigned int new_size){
    int* temp = value;
    
    delete this->value;
    this->value = new int[new_size];
    
    this->buffer = new_size;
    
    clear();
    for(int i=0; i<this->size; i++){
        this->value[i] = temp[i];
    }
}

BigUInt::BigUInt(){
    this->value = new int[SIZE];
    clear();
    this->buffer = SIZE;
    this->size = 0;
}

BigUInt::~BigUInt(){
    delete this->value;
}

void BigUInt::operator=(unsigned int x){
    clear();
    this->size = 0;
    while(x)
    {
        this->value[size] = x%BASE;
        x /= BASE;
        this->size++;
    }
}

void BigUInt::operator=(BigUInt & x){
    this->buffer = x.get_buffer_length();
    this->size = x.get_value_length();

    delete this->value;
    this->value = new int[buffer];
    
    clear();
    for(int i=0; i<size; i++){
        this->value[i] = x[i];
    }
}

bool BigUInt::operator==(BigUInt& x){
    if(this->size != x.get_value_length()){
        return false;
    }
    for(int i=0; i<this->size; i++){
        if(this->value[i] != x[i]){
            return false;
        }
    }
    return true;
}

bool BigUInt::operator!=(BigUInt& x){
    if(this->size != x.get_value_length()){
        return true;
    }
    for(int i=0; i<this->size; i++){
        if(this->value[i] != x[i]){
            return true;
        }
    }
    return false;
}

bool BigUInt::operator>(BigUInt& x){return true;}
bool BigUInt::operator>=(BigUInt& x){return true;}
bool BigUInt::operator<(BigUInt& x){return true;}
bool BigUInt::operator<=(BigUInt& x){return true;}


std::string BigUInt::to_string(){
    if(size == 0){
        return std::string("0");
    }

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

    if(n==x){
        std::cout << "true" << "\n";
    }
    BigNumber::BigUInt a;
    a=101;
    if(n==a){
        std::cout << "true" << "\n";
    }
    else{
        std::cout << "false" << "\n";
    }

    return 0;
}
