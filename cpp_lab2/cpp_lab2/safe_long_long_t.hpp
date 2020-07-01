#pragma once

#include <iostream>

class safe_long_long_t {
private:
    long long value;

public:
    // constructors
    safe_long_long_t();
    safe_long_long_t(long long new_value);
    
    // copy constructor
    safe_long_long_t(const safe_long_long_t &copy_from);
    
    // getter
    long long& get_value();
    
    // assignment operator
    void operator= (safe_long_long_t number);
    
    // math operators with =
    void operator+=(safe_long_long_t number);
    safe_long_long_t& operator-=(safe_long_long_t number);
    safe_long_long_t& operator*=(safe_long_long_t number);
    safe_long_long_t& operator/=(safe_long_long_t number);
    safe_long_long_t& operator%=(safe_long_long_t number);
    
    safe_long_long_t operator- () const {
        return -value;
    }
    
    // num++, ++num, num--, --num
    safe_long_long_t operator++();
    safe_long_long_t operator++(int);
    safe_long_long_t operator--();
    safe_long_long_t operator--(int);
    
    // input/output
    friend std::ostream& operator<< (std::ostream &output, safe_long_long_t number);
    friend std::istream& operator>> (std::istream &input, safe_long_long_t &number);
};

// comparative operators
bool operator== (safe_long_long_t num1, safe_long_long_t num2);
bool operator!= (safe_long_long_t num1, safe_long_long_t num2);
bool operator< (safe_long_long_t num1, safe_long_long_t num2);
bool operator> (safe_long_long_t num1, safe_long_long_t num2);
bool operator<= (safe_long_long_t num1, safe_long_long_t num2);
bool operator>= (safe_long_long_t num1, safe_long_long_t num2);

// math operators without =
safe_long_long_t operator+ (safe_long_long_t num1, safe_long_long_t num2);
safe_long_long_t operator- (safe_long_long_t num1, safe_long_long_t num2);
safe_long_long_t operator* (safe_long_long_t num1, safe_long_long_t num2);
safe_long_long_t operator/ (safe_long_long_t num1, safe_long_long_t num2);
safe_long_long_t operator% (safe_long_long_t num1, safe_long_long_t num2);

std::ostream& operator<<(std::ostream &output, safe_long_long_t number);
std::istream& operator>>(std::istream &input, safe_long_long_t &number);
