#include <iostream>
#include <string>

#define SIZE 10
#define BASE 10

namespace BigNumber{
class BigUInt{
private:
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

    // BigUInt operator/(unsigned int);
    // BigUInt operator/(const BigUInt&);
    
    // BigUInt operator%(unsigned int);
    // BigUInt operator%(const BigUInt&);

    // ostream &operator<<(const BigUInt&);
    // istream &operator>>(const BigUInt&);

    std::string to_string();
};

}; // namespace

namespace BigNumber{
BigUInt::BigUInt(){
    this->value = new int[SIZE];
    for(int i=0; i<SIZE; i++){
        this->value[i]=0;
    }
    this->buffer = SIZE;
    this->size = 0;
}

BigUInt::BigUInt(int* v, uint64_t b, uint64_t s){
    this->value = v;
    this->buffer = b;
    this->size = s;
}

BigUInt::~BigUInt(){
    delete[] this->value;
}

void BigUInt::operator=(unsigned int x){
    for(int i=0; i<SIZE; i++){
        this->value[i] = 0;
    }
    this->size = 0;
    while(x)
    {
        this->value[this->size] = x%BASE;
        x /= BASE;
        this->size++;
    }
}

void BigUInt::operator=(const BigUInt& x){
    this->buffer = x.get_buffer_length();
    this->size = x.get_value_length();

    if(this->value != nullptr){
        delete[] this->value;
    }
    this->value = new int[this->buffer];

    for(int i=0; i<this->size; i++){
        this->value[i] = x[i];
    }
}

bool BigUInt::operator==(const BigUInt& x){
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

bool BigUInt::operator!=(const BigUInt& x){
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

bool BigUInt::operator>(const BigUInt& x){
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

bool BigUInt::operator>=(const BigUInt& x){
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

bool BigUInt::operator<(const BigUInt& x){
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

bool BigUInt::operator<=(const BigUInt& x){
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

BigUInt BigUInt::operator+(unsigned int right){
    int* v = new int[SIZE];
    
    int pos = 0;
    v[pos] = this->value[pos] + right;
    
    while (v[pos] >=  BASE){
      v[pos+1]++;
      v[pos] -= BASE;
      pos++;
    }

    uint64_t s = SIZE;
    while(v[s-1] == 0) s--;

    return BigUInt(v, SIZE, s);
}

BigUInt BigUInt::operator+(const BigUInt & right){
    int* v = new int[SIZE];
    uint64_t s;

    int carry = 0;
    for(int i=0; i<SIZE; i++)
    {
        int data = this->value[i]+right[i]+carry;
        carry = data/BASE;
        v[i] = data%BASE;
    }
    
    // if overflow return 0
    if(carry>0){
        for(int i=0; i<SIZE; i++){
            v[i] = 0;
        }
        s=0;
    }
    else{
        s = SIZE;
        while(v[s-1] == 0 && s > 0) s--;
    }

    return BigUInt(v, SIZE, s);
}

BigUInt BigUInt::operator-(unsigned int){/* TODO!!! */}

BigUInt BigUInt::operator-(const BigUInt& right){
    int* v = new int[SIZE];
    uint64_t s;

    int borrow = 0;
    for(int i=0; i<SIZE; i++)
    {
        int data = this->value[i]-(right[i]+borrow);
        if(data<0) {
            data += BASE;
            borrow = 1;
        }
        else{
            borrow = 0;
        }
        v[i] = data;
    }

    //if overflow return 0
    if(borrow > 0){
        for(int i=0; i<SIZE; i++){
            v[i] = 0;
        }
        s=0;
    }
    else{
        s = SIZE;
        while(v[s-1] == 0 && s > 0) s--;
    }

    return BigUInt(v, SIZE, s);
}

BigUInt BigUInt::operator*(unsigned int right){
    int* v = new int [SIZE];
    int r = 0;
    for (int i=0; i<SIZE; i++){
        v[i] = this->value[i] * right + r;
        r = v[i] / BASE;
        v[i] -= r * BASE;
    }
    
    uint64_t s = SIZE;
    while(v[s-1] == 0) s--;

    return BigUInt(v, SIZE, s);
}

BigUInt BigUInt::operator*(const BigUInt& right){
    int* temp = new int[SIZE*2];
    int* v = new int[SIZE];
    for(int i=0; i<SIZE*2; i++){
        temp[i] = 0;
        v[i/2] = 0;
    }

    for (int i = 0; i < SIZE; ++i) 
    {
        for (int j = 0; j < SIZE; ++j) 
        {
            temp[i + j] += this->value[i] * right[j];
        }
    }

    for (int i = 0; i < SIZE*2-1; ++i) 
    {
        temp[i + 1] += temp[i] / BASE;
        temp[i] %= BASE;
    }

    uint64_t s = SIZE*2;
    while(temp[s-1] == 0 && s>0) s--;

    // overflow
    if(s>=SIZE){
        s=0;
    }
    else{
        for(int i=0;i<SIZE; i++)
            v[i] = temp[i];
    }

    delete[] temp;
    return BigUInt(v, SIZE, s);
}

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

//=======================================================

int main()
{
    BigNumber::BigUInt x,y,z;
    x=10;
    y=x+x;

    std::cout << y.to_string() << "\n";
    return 0;
}
