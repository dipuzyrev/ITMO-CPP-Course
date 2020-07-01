#include <iostream>

#include "safe_long_long_t.hpp"
#include "safe_c_array_t.tpp"

int main() {
    //tests for safe_long_long_t
    safe_long_long_t number1, number2, number3;
    number1 = 1025;
    safe_long_long_t number1_equal = number1;
    number2 = 1024000;
    
    

    std::cout << "number1++: " << number1++ << std::endl;
    std::cout << "++number1_equal: " << ++number1_equal << std::endl;
    std::cout << "number1_equal--: " << number1_equal-- << std::endl;
    std::cout << "--number1: " << --number1 << std::endl;

    std::cout << "number1 = " << number1 << std::endl;
    std::cout << "number2 = " << number2 << std::endl << std::endl;

    number3 = 5 + number1;
    std::cout << "5 + " << number1 << " = " << number3 << std::endl;
    std::cout << "number3 = " << number3 << std::endl;
    std::cout << "number3 += number2" << std::endl;


    std::cout << "number3 = " << number3 << std::endl;
    number3 = number1 + number2;
    std::cout << number1 << " + " << number2 << " = " << number3 << std::endl;

    std::cout << "number1 == number2: " << (number1 == number2) << std::endl;
    std::cout << "number1 == number1_equal: " << (number1 == number1_equal) << std::endl;
    std::cout << "number1 != number2: " << (number1 != number2) << std::endl;
    std::cout << "number1 != number1_equal: " << (number1 != number1_equal) << std::endl;

//    std::cin >> number3;
//    std::cout << number3 << std::endl;

    std::cout << "number1 == number2: " << (number1 == number2) << std::endl;
    std::cout << "number1 == number1_equal: " << (number1 == number1_equal) << std::endl;
    std::cout << "5 == number1: " << (5 == number1) << std::endl;
    std::cout << "1025 == number1: " << (1025 == number1) << std::endl;
    
    
    //tests for safe_c_array_t
    int size = 5;
    
    safe_c_array_t<int> safe_array = safe_c_array_t<int>(size);
    
    
    
    
    safe_c_array_t<int> array(size);
    safe_c_array_t<int> array_copy(array);
    safe_c_array_t<int> new_array(size);

    for (int i = 0; i < size; ++i) {
      array[i] = i + 1;
      array_copy[i] = i + 1;
    }

    new_array = array;

    for (int i = 0; i < size; ++i) {
      std::cout << "i: " << i << std::endl;
      std::cout << "safe_array[i] before redefinition: " << safe_array[i] << std::endl;
      std::cout << "new_array[i] before redefinition: " << new_array[i] << std::endl;
      std::cout << "array_copy[i] before redefinition: " << array_copy[i] << std::endl;

      array_copy[i] = i + 11;
      std::cout << "safe_array[i] after redefinition: " << safe_array[i] << std::endl;
      std::cout << "new_array[i] after redefinition: " << new_array[i] << std::endl;
      std::cout << "array_copy[i] after redefinition: " << array_copy[i] << std::endl;
      std::cout << std::endl;
    }
    
    
    safe_c_array_t<int> arr1(10);
    safe_c_array_t<int> arr2(5);
    
    arr2 = arr1;
    std::cout << arr2[0];

    return 0;
}
