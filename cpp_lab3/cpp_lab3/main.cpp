#include <iostream>
#include <vector>
#include <algorithm>

#include "int_list_t.hpp"

size_t test_id = 1;

void log(bool verdict);

void print_test(std::string title);
void test(const int_list_t &list, const std::vector<int> &array);
void test(const size_t val1, const size_t val2);
void test(const bool condition);

int main() {
    {
        print_test("Create empty list");
        int_list_t list;
        test(list, {});
    }
    
    {
        print_test("Create list with 5 elements with each value = 1");
        int_list_t list(5, 1);
        test(list, {1, 1, 1, 1, 1});
    }
    
    {
        print_test("Test operator =");
        int_list_t list1(5, 1);
        int_list_t list2 = list1;
        test(list2, {1, 1, 1, 1, 1});
        list1[0] = 0;
        test(list1, {0, 1, 1, 1, 1});
        test(list2, {1, 1, 1, 1, 1});
        
        int_list_t list;
        for (int i = 0; i < 5; i++) {
            list.push_back(i);
        }
        list = list;
        test(list, {0, 1, 2, 3, 4});
    }
    
    {
        print_test("Test operator []");
        int_list_t list(5, 1);
        test(list[2], 1);
    }
    
    {
        print_test("Test clear()");
        int_list_t list(5, 1);
        list.clear();
        test(list, {});
    }
    
    {
        print_test("Test is_empty()");
        int_list_t list1;
        test(list1.empty());
        
        int_list_t list2(5, 1);
        test(!list2.empty());
        
        list2.clear();
        test(list2.empty());
    }
    
    {
        print_test("Test get_size()");
        int_list_t list(5, 1);
        test(list.size(), 5);
    }
    
    {
        print_test("Test push_back()");
        int_list_t list(2, 1);
        list.push_back(2);
        test(list, {1, 1, 2});
    }
    
    {
        print_test("Test push_front()");
        int_list_t list(2, 1);
        list.push_front(2);
        test(list, {2, 1, 1});
    }
    
    {
        print_test("Test back()");
        int_list_t list(5, 1);
        test(list.back(), 1);
    }
    
    {
        print_test("Test front()");
        int_list_t list(5, 1);
        test(list.front(), 1);
    }
    
    {
        print_test("Test insert()");
        int_list_t list(5, 1);
        list.insert(2, 2);
        test(list, {1, 1, 2, 1, 1, 1});
        test(list.size(), 6);
        
        list.insert(0, 3);
        test(list, {3, 1, 1, 2, 1, 1, 1});
        
        list.insert(6, 4);
        test(list, {3, 1, 1, 2, 1, 1, 4, 1});
    }
    
    {
        print_test("Test erase()");
        int_list_t list(1, 4);
        list.insert(0, 3);
        list.insert(0, 2);
        list.insert(0, 1);
        
        list.erase(2);
        test(list, {1, 2, 4});
        
        list.erase(0);
        test(list, {2, 4});
        
        list.erase(1);
        test(list, {2});
    }
    
    {
        print_test("Test pop_front() and pop_back()");
        int_list_t list(1, 3);
        list.insert(0, 2);
        list.insert(0, 1);
        
        list.pop_front();
        test(list, {2, 3});
        
        list.pop_back();
        test(list, {2});
    }
    
    {
        print_test("Test splice()");
        int_list_t list1(1, 3);
        list1.insert(0, 2);
        list1.insert(0, 1);
        int_list_t res1 = list1.splice(0, 2);
        test(res1, {1, 2});

        int_list_t list2(1, 3);
        list2.insert(0, 2);
        list2.insert(0, 1);
        int_list_t res2 = list2.splice(1, 2);
        test(res2, {2, 3});

        int_list_t list3(4, 1);
        int_list_t res3 = list3.splice(1, 2);
        test(res3, {1, 1});
    }
    
    {
        print_test("Test merge()");
        int_list_t list1(3, 1);
        int_list_t list2(3, 2);
        list1.merge(list2);

        test(list1, {1, 1, 1, 2, 2, 2});
        test(list2, {});
        
        int_list_t l1;
        int_list_t l2(3, 2);
        l1.merge(l2);
        test(l1, {2, 2, 2});
        test(l2, {});
    }
    
    {
        print_test("Test reverse()");
        int_list_t list(1, 3);
        list.insert(0, 2);
        list.insert(0, 1);
        list.reverse();
        test(list, {3, 2, 1});
    }
    
    {
        print_test("Test swap()");
        int_list_t list1(3, 1);
        int_list_t list2(3, 2);
        list1.swap(list2);
        test(list1, {2, 2, 2});
        test(list2, {1, 1, 1});
    }
    
    return 0;
}

void log(bool verdict) {
    std::cout << "TEST " << test_id++ << " " << (verdict ? "passed" : "failed") << '\n';
}

void print_test(std::string title) {
    std::cout << "\n> " << title << std::endl;
}

void test(const int_list_t &list, const std::vector<int> &array) {
    if (list.size() != array.size()) {
        log(false);
        return;
    }
    
    for (size_t i = 0; i < list.size(); i++) {
        try {
            int v = list[i];
            if (v != array[i]) {
                std::cout << "\nWRONG VALUE AT INDEX: " << i << std::endl;
                std::cout << list << std::endl;
                log(false);
                return;
            }
        } catch (...) {
            std::cout << "\nERROR AT INDEX: " << i << std::endl;
            std::cout << list << std::endl;
            log(false);
            return;
        }
    }
    
    log(true);
}

void test(const size_t val1, const size_t val2) {
    log(val1 == val2);
}

void test(const bool condition) {
    log(condition);
}
