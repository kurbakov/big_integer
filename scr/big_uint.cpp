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
    this->size = 0;
}

BigUInt::BigUInt(int* v, uint64_t s){
    this->value = v;
    this->size = s;
}

BigUInt::BigUInt(const BigUInt& right){
    for(int i=0; i<SIZE; i++){
        this->value[i] = right[i];
    }
    this->size = SIZE;
    while(this->value[this->size-1] == 0 && this->size > 0) this->size--;
}

BigUInt::~BigUInt(){
    delete[] this->value;
}

void BigUInt::operator=(unsigned int x){
    for(int i=0; i<SIZE; i++){
        this->value[i] = 0;
    }

    while(x){
        this->value[this->size] = x%BASE;
        x /= BASE;
    }
    this->size = SIZE;
    while(this->value[this->size-1] == 0 && this->size > 0) this->size--;
}

void BigUInt::operator=(const BigUInt& x){
    for(int i=0; i<this->size; i++){
        this->value[i] = x[i];
    }
    this->size = SIZE;
    while(this->value[this->size-1] == 0 && this->size > 0) this->size--;
}

bool BigUInt::operator==(const BigUInt& x){
    for(int i=0; i<SIZE; i++){
        if(this->value[i] != x[i]){
            return false;
        }
    }
    return true;
}

bool BigUInt::operator!=(const BigUInt& x){
    for(int i=0; i<SIZE; i++){
        if(this->value[i] != x[i]){
            return true;
        }
    }
    return false;
}

bool BigUInt::operator>(const BigUInt& x){    
    for(int i=SIZE-1; i>=0; i--){
        if(this->value[i] > x[i]){
            return true;
        }
    }
    return false;
}

bool BigUInt::operator>=(const BigUInt& x){
    for(int i=SIZE-1; i>=0; i--){
        if(this->value[i] < x[i]){
            return false;
        }
    }
    return true;
}

bool BigUInt::operator<(const BigUInt& x){
    for(int i=SIZE-1; i>=0; i--){
        if(this->value[i] < x[i]){
            return true;
        }
    }
    return false;
}

bool BigUInt::operator<=(const BigUInt& x){
    for(int i=SIZE-1; i>=0; i--){
        if(this->value[i] > x[i]){
            return false;
        }
    }
    return true;
}

BigUInt BigUInt::operator+(const BigUInt & right){
    int* v = new int[SIZE];

    int carry = 0;
    for(int i=0; i<SIZE; i++)
    {
        int data = this->value[i]+right[i]+carry;
        carry = data/BASE;
        v[i] = data%BASE;
    }
    
    uint64_t s;
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

    return BigUInt(v, s);
}

BigUInt BigUInt::operator+(unsigned int right){
    BigUInt x;
    x=right;
    return *this+x;
}

BigUInt BigUInt::operator-(const BigUInt& right){
    int* v = new int[SIZE];


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

    uint64_t s;
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

    return BigUInt(v, s);
}

BigUInt BigUInt::operator-(unsigned int right){
    BigUInt x;
    x=right;
    return *this-x;
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
        temp[i+1] += temp[i] / BASE;
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
    return BigUInt(v, s);
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
    while(v[s-1] == 0 && s>0) s--;

    return BigUInt(v, s);
}

BigUInt BigUInt::operator/(unsigned int right){
    int* v = new int[SIZE];

    int ost = 0;
    for (int i=SIZE-1; i>=0; i--)
    {
      int cur = ost * BASE + this->value[i];
      v[i] = cur / right;
      ost = cur % right;
    }

    uint64_t s = SIZE;
    while(v[s-1] == 0 && s>0) s--;

    return BigUInt(v, s);
}

BigUInt BigUInt::operator/(const BigUInt& right){
    BigUInt res;
    BigUInt curValue;
    BigUInt temp;
    int idx = this->size;
    for (int i=idx-1; i>=0; i--){
        curValue.LevelUp();
        curValue[0] = this->value[i];
        int x = 0;
        int l = 0;
        int r = BASE;
        
        while (l <= r){
            int m = (l + r) >> 1;
            
            temp=right;
            temp=temp*m;
            if (temp<=curValue){
                x = m;
                l = m+1;
            }
            else{
                r = m-1;
            }
        }
        std::cout << x << "\n";
        res[i]=x;
        temp=right;
        temp=temp*x;
        curValue=curValue-temp;
    }

    return res;
}

int BigUInt::operator%(unsigned int right){
    int ost = 0;
    for (int i=SIZE; i>=0; i--)
    {
      int cur = ost * BASE + this->value[i];
      ost = cur % right;
    }
    return ost;
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
    y=200;

    std::cout << (y/x).to_string() << "\n";
    return 0;
}
