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

    BigUInt operator+(const BigUInt&);
    BigUInt operator-(const BigUInt&);
    BigUInt operator*(BigUInt& right);
    BigUInt operator/(BigUInt& right);
    // BigUInt operator%(BigUInt& right);

    // ostream &operator<<(BigUInt&);
    // istream &operator>>(BigUInt&);

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

BigUInt BigUInt::operator*(BigUInt& right){
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

// BigUInt BigUInt::operator/(BigUInt& right)
// {
//     int* res = new int[SIZE];
//     int* curValue = new int[SIZE];
//     for(int k=0; k<SIZE; k++){
//         res[k]=0;
//         curValue[k]=0;
//     }

//     for (int i = SIZE-1; i>=0; i--)
//     {
//         // level up
//         for (int i=1; i<SIZE; i++){
//             curValue[i] = curValue[i-1];
//         }
//         curValue[0] = this->value[i];

//         // подбираем максимальное число x, такое что b * x <= curValue
//         int x = 0;
//         int l = 0;
//         int r = BASE;
//         while (l <= r)
//         {
//             int m = (l + r) >> 1;
//             BigUInt cur = right*m;
//             if (cur <= curValue)
//             {
//                 x = m;
//                 l = m+1;
//             }
//             else{
//                 r = m-1;
//             }
//         }
//         res[i] = x;
//         curValue = curValue - right * x;
//     }

//     uint64_t s = SIZE;
//     while (res[s-1]==0 && s>0) s--;
    
//     return BigUInt(res, SIZE, s);
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

// =======================================================

void division(int* left, int* right, int* result){
    int* modulo = new int[SIZE];
    for(int i=0; i<SIZE; i++){
        modulo[i] = 0;
    }
    delete[] modulo;
}

//=======================================================

int main(){
    int* x = new int[SIZE];
    int* y = new int[SIZE];
    int* res = new int[SIZE];
    for (int i=0; i<SIZE; i++){
        x[i]=0; y[i]=0; res[i]=0;
    }
    x[0]=5; x[1]=5; x[2]=5;
    y[0]=1; y[1]=1; y[2]=1;

    division(x, y, res);

    for(int k=0; k<SIZE; k++){
        std::cout << res[k] <<" ";
    }
    std::cout << "\n";
    

    return 0;
}
