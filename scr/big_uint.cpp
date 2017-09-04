#include "big_uint.h"

namespace BigNumber{
BigUInt::BigUInt(){
    this->value = new int[SIZE];
    for(int i=0; i<SIZE; i++){
        this->value[i]=0;
    }
    this->size = 0;
}

BigUInt::BigUInt(const BigUInt& right){
    this->value = new int[SIZE];

    for(int i=0; i<SIZE; i++){
        this->value[i] = right[i];
    }
    this->size = SIZE;
    while(this->value[this->size-1] == 0 && this->size > 0) this->size--;
}

BigUInt::~BigUInt(){
    delete[] this->value;
}

void BigUInt::LevelUp(){
    for (int i = SIZE-1;i>=1;i--){
        value[i] = value[i-1];
    }
    
    size = SIZE;
    while(value[size-1] && size>0) size--;
}

void BigUInt::FixSize(){
    size = SIZE;
    while(value[size-1] && size>0) size--;
}

void BigUInt::operator=(unsigned int x){
    for(int i=0; i<SIZE; i++){
        this->value[i] = 0;
    }
    this->size = 0;
    while(x){
        this->value[this->size++] = x%BASE;
        x /= BASE;
    }
}

void BigUInt::operator=(const BigUInt& x){
    for(int i=0; i<SIZE; i++){
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
    BigUInt result;

    int carry = 0;
    for(int i=0; i<SIZE; i++)
    {
        int data = this->value[i]+right[i]+carry;
        carry = data/BASE;
        result[i] = data%BASE;
    }
    
    // if overflow return 0
    if(carry>0){
        for(int i=0; i<SIZE; i++){
            result[i] = 0;
        }
    }
    result.FixSize();
    return result;
}

BigUInt BigUInt::operator+(unsigned int right){
    BigUInt x;
    x=right;
    return *this+x;
}

BigUInt BigUInt::operator-(const BigUInt& right){
    BigUInt result;

    int borrow = 0;
    for(int i=0; i<SIZE; i++){
        int data = this->value[i]-(right[i]+borrow);
        if(data<0){
            data += BASE;
            borrow = 1;
        }
        else{
            borrow = 0;
        }
        result[i] = data;
    }

    //if overflow return 0
    if(borrow > 0){
        for(int i=0; i<SIZE; i++){
            result[i] = 0;
        }
    }
    result.FixSize();
    return result;
}

BigUInt BigUInt::operator-(unsigned int right){
    BigUInt x;
    x=right;
    return *this-x;
}

BigUInt BigUInt::operator*(const BigUInt& right){
    BigUInt result;
    int* temp = new int[SIZE*2];
    for(int i=0; i<SIZE*2; i++){
        temp[i]=0;
    }

    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            temp[i + j] += this->value[i] * right[j];
        }
    }

    for (int i = 0; i < SIZE*2-1; ++i){
        temp[i+1] += temp[i] / BASE;
        temp[i] %= BASE;
    }

    uint64_t s = SIZE*2;
    while(temp[s-1] == 0 && s>0) s--;

    if(s >= SIZE){
        // overflow
    }
    else{
        for(int i=0;i<SIZE; i++)
            result[i] = temp[i];
    }
    
    result.FixSize();
    delete[] temp;
    return result;
}

BigUInt BigUInt::operator*(unsigned int right){
    BigUInt result;
    int r = 0;
    for (int i=0; i<SIZE; i++){
        result[i] = this->value[i] * right + r;
        r = result[i] / BASE;
        result[i] -= r * BASE;
    }
    
    result.FixSize();
    return result;
}

BigUInt BigUInt::operator/(unsigned int right){
    BigUInt result;
    if(right == 0){
        return result;
    }

    int ost = 0;
    for (int i=SIZE-1; i>=0; i--){
        int cur = ost * BASE + this->value[i];
        result[i] = cur / right;
        ost = cur % right;
    }

    result.FixSize();
    return result;
}

BigUInt BigUInt::operator/(const BigUInt& right){
    BigUInt result;
    // division by 0
    if(right.get_size()==0){
        return result;
    }

    BigUInt curValue;
    BigUInt temp;
    int idx = SIZE;
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

        result[i] = x;
        temp=right;
        temp=temp*x;
        curValue=curValue-temp;
    }

    result.FixSize();
    return result;
}

int BigUInt::operator%(unsigned int right){
    if(right==0) return 0;

    int ost = 0;
    for (int i=SIZE; i>=0; i--){
        int cur = ost * BASE + this->value[i];
        ost = cur % right;
    }
    return ost;
}

BigUInt BigUInt::operator%(const BigUInt& right){
    BigUInt curValue;
    if(right.get_size()==0) return curValue;

    int* res = new int[SIZE];
    
    BigUInt temp;
    int idx = SIZE;
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

        res[i] = x;
        temp=right;
        temp=temp*x;
        curValue=curValue-temp;
    }
    delete[] res;
    return curValue;
}

std::string BigUInt::to_string(){
    if(this->size == 0){
        return std::string("0");
    }

    std::string res;
    for(uint64_t i=0; i<this->size; i++){
        res += std::to_string( value[size-1-i] );
    }
    return res;
}

}; // namespace