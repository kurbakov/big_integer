#include "big_uint.h"

namespace BigNumber{
BigUInt::BigUInt(){
    this->value = new int[SIZE];
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
    for(int i=0; i<SIZE; i++){
        int data = this->value[i]-(right[i]+borrow);
        if(data<0){
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
    for (int i=SIZE-1; i>=0; i--){
        int cur = ost * BASE + this->value[i];
        v[i] = cur / right;
        ost = cur % right;
    }

    uint64_t s = SIZE;
    while(v[s-1] == 0 && s>0) s--;

    return BigUInt(v, s);
}

BigUInt BigUInt::operator/(const BigUInt& right){
    int* res = new int[SIZE];

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

        res[i] = x;
        temp=right;
        temp=temp*x;
        curValue=curValue-temp;
    }

    uint64_t s=SIZE;
    while(res[s-1]==0 && s>0) s--;

    return BigUInt(res,s);
}

int BigUInt::operator%(unsigned int right){
    int ost = 0;
    for (int i=SIZE; i>=0; i--){
        int cur = ost * BASE + this->value[i];
        ost = cur % right;
    }
    return ost;
}

BigUInt BigUInt::operator%(const BigUInt& right){
    int* res = new int[SIZE];
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
    for(int i=0; i < this->size; i++){
        res += std::to_string( value[size-1-i] );
    }
    return res;
}

}; // namespace