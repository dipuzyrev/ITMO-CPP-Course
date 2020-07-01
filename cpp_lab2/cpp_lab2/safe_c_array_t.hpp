#pragma once

#include <iostream>

template <typename T>
class safe_c_array_t {
private:
    T *array;
    size_t size;
    
public:
    // constructor
    explicit safe_c_array_t(size_t new_size);

    // copy cunstructor
    safe_c_array_t(const safe_c_array_t &copy_from);

    // desctructor
    ~safe_c_array_t();
    
    // getters
    T* get_array();
    size_t get_size();
    
    // assignment
    void operator= (const safe_c_array_t<T> &other);

    // with changing
    T& operator[] (size_t index);
    
    // without changing
    T operator[] (size_t index) const;
};
