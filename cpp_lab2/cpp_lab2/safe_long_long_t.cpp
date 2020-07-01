#include "safe_long_long_t.hpp"


// constructors
safe_long_long_t::safe_long_long_t() {
    value = 0;
}

safe_long_long_t::safe_long_long_t(long long new_value) {
    value = new_value;
}

// copy constructor
safe_long_long_t::safe_long_long_t(const safe_long_long_t &copy_from) {
    value = copy_from.value;
}


// getter
long long& safe_long_long_t::get_value() {
    return value;
}


// assignment operator
void safe_long_long_t::operator= (safe_long_long_t number) {
    value = number.value;
}


// math operators with =
void safe_long_long_t::operator+=(safe_long_long_t number) {
    value += number.get_value();
    return;
}

safe_long_long_t& safe_long_long_t::operator-=(safe_long_long_t number) {
    value -= number.get_value();
    return *this;
}

safe_long_long_t& safe_long_long_t::operator*=(safe_long_long_t number) {
    value *= number.get_value();
    return *this;
}

safe_long_long_t& safe_long_long_t::operator/=(safe_long_long_t number) {
    value /= number.get_value();
    return *this;
}

safe_long_long_t& safe_long_long_t::operator%=(safe_long_long_t number) {
    value %= number.get_value();
    return *this;
}


// num++
safe_long_long_t safe_long_long_t::operator++() {
    return ++value;
}

// ++num
safe_long_long_t safe_long_long_t::operator++(int) {
    return value++;
}

// num--
safe_long_long_t safe_long_long_t::operator--() {
    return --value;
}

// --num
safe_long_long_t safe_long_long_t::operator--(int) {
    return value--;
}


// comparative operators
bool operator== (safe_long_long_t num1, safe_long_long_t num2) {
    return num1.get_value() == num2.get_value();
}

bool operator!= (safe_long_long_t num1, safe_long_long_t num2) {
    return num1.get_value() != num2.get_value();
}

bool operator< (safe_long_long_t num1, safe_long_long_t num2) {
    return num1.get_value() < num2.get_value();
}

bool operator> (safe_long_long_t num1, safe_long_long_t num2) {
    return num1.get_value() > num2.get_value();
}

bool operator<= (safe_long_long_t num1, safe_long_long_t num2) {
    return num1.get_value() <= num2.get_value();
}

bool operator>= (safe_long_long_t num1, safe_long_long_t num2) {
    return num1.get_value() >= num2.get_value();
}


// math operators without =
safe_long_long_t operator+ (safe_long_long_t num1, safe_long_long_t num2) {
    return num1.get_value() + num2.get_value();
}

safe_long_long_t operator- (safe_long_long_t num1, safe_long_long_t num2) {
    return num1.get_value() - num2.get_value();
}

safe_long_long_t operator* (safe_long_long_t num1, safe_long_long_t num2) {
    return num1.get_value() * num2.get_value();
}

safe_long_long_t operator/ (safe_long_long_t num1, safe_long_long_t num2) {
    return num1.get_value() / num2.get_value();
}

safe_long_long_t operator% (safe_long_long_t num1, safe_long_long_t num2) {
    return num1.get_value() % num2.get_value();
}

// input/output
std::ostream& operator<< (std::ostream &output, safe_long_long_t number) {
    output << number.get_value();
    return output;
}

std::istream& operator>> (std::istream &input, safe_long_long_t &number) {
    long long temp_number;
    input >> temp_number;
    number.value = temp_number;
    return input;
}
