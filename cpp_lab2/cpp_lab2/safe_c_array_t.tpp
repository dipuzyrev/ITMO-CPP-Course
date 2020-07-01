#include "safe_c_array_t.hpp"

// constructor
template <typename T>
safe_c_array_t<T>::safe_c_array_t (size_t new_size) {
  size = new_size;
  array = new T[size];
}

// copy constructor
template <typename T>
safe_c_array_t<T>::safe_c_array_t (const safe_c_array_t<T> &copy_from) {
  size = copy_from.size;
  array = new T[size];
  for (size_t i = 0; i < size; i++) {
    array[i] = copy_from[i];
  }
}

// destructor
template <typename T>
safe_c_array_t<T>::~safe_c_array_t() {
  delete[] array;
}

// getters
template <typename T>
T *safe_c_array_t<T>::get_array() {
  return array;
}

template <typename T>
size_t safe_c_array_t<T>::get_size() {
  return size;
}

// assignment
template <typename T>
void safe_c_array_t<T>::operator= (const safe_c_array_t<T> &other) {
  if(this != &other) {
      delete[] array;
      size = other.size;
      array = new T[size];
      for (int i = 0; i < size; ++i) {
          array[i] = other[i];
      }
  }
}

// with changing
template <typename T>
T &safe_c_array_t<T>::operator[] (size_t index) {
  return array[index];
}

// without changing
template <typename T>
T safe_c_array_t<T>::operator[] (size_t index) const {
  return array[index];
}

