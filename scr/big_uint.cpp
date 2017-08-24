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
    BigUInt(int*, uint64_t, uint64_t);
    ~BigUInt();

    uint64_t get_buffer_length() const {return buffer;}
    uint64_t get_value_length() const {return size;}
    int operator[](unsigned int i) const {return value[i];}

    void operator=(unsigned int);
    void operator=(const BigUInt&);

    bool operator==(BigUInt);
    bool operator!=(BigUInt);
    bool operator>(BigUInt);
    bool operator>=(BigUInt);
    bool operator<(BigUInt);
    bool operator<=(BigUInt);

    BigUInt operator+(const BigUInt&);
    BigUInt operator-(const BigUInt&);
    // BigUInt operator*(BigUInt& right);
    // BigUInt operator/(BigUInt& right);
    // BigUInt operator%(BigUInt& right);

    // ostream &operator<<(BigUInt&);
    // istream &operator>>(BigUInt&);

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
    this->buffer = SIZE;
    this->size = 0;
}

BigUInt::BigUInt(int* v, uint64_t b, uint64_t s){
    this->value = v;
    this->buffer = b;
    this->size = s;

    for(int i=0; i<b;i++){
        this->value[i] = v[i];
    }
}

BigUInt::~BigUInt(){
    delete this->value;
}

void BigUInt::operator=(unsigned int x){
    this->clear();
    this->size = 0;
    while(x)
    {
        this->value[size] = x%BASE;
        x /= BASE;
        this->size++;
    }
}

void BigUInt::operator=(const BigUInt& x){
    this->buffer = x.get_buffer_length();
    this->size = x.get_value_length();

    if(this->value != nullptr){
        delete this->value;
    }
    this->value = new int[this->buffer];

    for(int i=0; i<this->size; i++){
        this->value[i] = x[i];
    }
}

bool BigUInt::operator==(BigUInt x){
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

bool BigUInt::operator!=( BigUInt x){
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

bool BigUInt::operator>( BigUInt x){
    if(this->size > x.get_value_length()){
        return true;
    }
    
    if(this->size < x.get_value_length()){
        return false;
    }

    for(int i=this->size-1; i>=0; i--){
        if(this->value[i] > x[i]){
            return true;
        }
    }
    return false;
}

bool BigUInt::operator>=( BigUInt x){
    if(this->size > x.get_value_length()){
        return true;
    }
    
    if(this->size < x.get_value_length()){
        return false;
    }

    for(int i=this->size-1; i>=0; i--){
        if(this->value[i] < x[i]){
            return false;
        }
    }

    return true;
}

bool BigUInt::operator<( BigUInt x){
    if(this->size < x.get_value_length()){
        return true;
    }
    
    if(this->size > x.get_value_length()){
        return false;
    }

    for(int i=this->size-1; i>=0; i--){
        if(this->value[i] < x[i]){
            return true;
        }
    }
    return false;
}

bool BigUInt::operator<=( BigUInt x){
    if(this->size < x.get_value_length()){
        return true;
    }
    
    if(this->size > x.get_value_length()){
        return false;
    }

    for(int i=this->size-1; i>=0; i--){
        if(this->value[i] > x[i]){
            return false;
        }
    }

    return true;
}

BigUInt BigUInt::operator+(const BigUInt & right){
    uint64_t b = right.get_buffer_length();
    int* v = new int[b];
    uint64_t s;
    if(this->size > right.get_value_length()){
        s = this->size;
    }
    else{
        s = right.get_value_length();
    }

    int carry = 0;
    for(int i=0; i<s; i++)
    {
        int data = this->value[i]+right[i]+carry;
        carry = data/10;
        v[i] = data%10;
    }

    if(carry > 0){
        v[s] = carry;
        s++;
    }

    return BigUInt(v, b, s);
}

// BigUInt BigUInt::operator-(const BigUInt right){
//     uint64_t b = 10;
//     int* v = new int[b];
//     uint64_t s = 0;

//     return BigUInt(v, b, s);
// }

std::string BigUInt::to_string(){
    if(this->size == 0){
        return std::string("0");
    }

    std::string res;
    for(int i=0; i < this->size; i++){
        res += std::to_string( value[size-1-i] );
    }
    return res;
}

}; // namespace


int main(){
    // int* v = new int[10];
    // uint64_t s = 1;
    // uint64_t b = 10;
    
    BigNumber::BigUInt x,y;
    x=10;
    std::cout << y.to_string() << "\n";

    y=x+x;
    y=x+x;

    y=100;
    std::cout << y.to_string() << "\n";

    return 0;
}
