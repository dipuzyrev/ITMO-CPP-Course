#include <algorithm>
#include <stdexcept>

#include "int_list_t.hpp"

int_list_t::node_t::node_t(): val(0), next(nullptr), prev(nullptr) {}

int_list_t::node_t::node_t(int v, int_list_t::node_t *next, int_list_t::node_t *prev):
    val(v), next(next), prev(prev) {}

// O(1)
int_list_t::int_list_t(): _size(0), _first(nullptr), _last(nullptr) {}

// COPY $other list O(other.size)
int_list_t::int_list_t(const int_list_t &other): int_list_t() {
    if (!other.empty()) {
        size_t other_size = other.size();
        for (int i = 0; i < other_size; i++) {
          push_back(other[i]);
        }
    }
}

// create list $count size and fill it with $value O($count)
int_list_t::int_list_t(size_t count, int value): int_list_t() {
    for (size_t i = 0; i < count; i++) {
        push_back(value);
    }
}

int_list_t::~int_list_t() {
    clear();
}

int_list_t &int_list_t::operator=(const int_list_t &other) {
    clear();
    _size = other.size();
    for (int i = 0; i < other.size(); i++) {
      push_back(other[i]);
    }
    return *this;
}

// O(min($pos, size - $pos))
int &int_list_t::operator[](size_t pos) {
    if (pos > size()) {
        throw std::out_of_range("operator[] out of bound");
    } else {
        return get_node(pos)->val;
    }
}

const int int_list_t::operator[](size_t pos) const {
    if (pos > size()) {
        throw std::out_of_range("operator[] out of bound");
    } else {
        return get_node(pos)->val;
    }
}

int &int_list_t::back() {
    if (empty()) {
      throw std::out_of_range("Trying to call 'back()' from empty list");
    }
    return _last->val;
}

const int int_list_t::back() const {
    if (empty()) {
      throw std::out_of_range("Trying to call 'back()' from empty list");
    }
    return _last->val;
}

int &int_list_t::front() {
    if (empty()) {
      throw std::out_of_range("Trying to call 'first()' from empty list");
    }
    return _first->val;
}

const int int_list_t::front() const {
    if (empty()) {
      throw std::out_of_range("Trying to call 'first()' from empty list");
    }
    return _first->val;
}

// O(size)
void int_list_t::clear() {
    node_t *ptr = _first;
    while (ptr != nullptr) {
        node_t *tmp = ptr;
        ptr = ptr->next;
        delete tmp;
    }
    
    _size = 0;
    _first = nullptr;
    _last = nullptr;
}

size_t int_list_t::size() const {
    return _size;
}

bool int_list_t::empty() const {
    return _size == 0;
}

// insert element $new_val BEFORE element with index $pos O(min($pos, size - $pos))
void int_list_t::insert(size_t pos, int new_val) {
    if (pos >= _size) {
        throw std::out_of_range("index 'pos' in insert() out of bound");
    }
    
    if (pos == 0) {
        push_front(new_val);
    } else {
        node_t *ptr = get_node(pos);
        node_t *new_node = new node_t(new_val, ptr, ptr->prev);
        
        ptr->prev->next = new_node;
        ptr->prev = new_node;
        _size++;
    }
}

// O(1)
void int_list_t::push_front(int new_val) {
    node_t *new_node = new node_t(new_val, _first, nullptr);
    
    if (!empty()) {
        _first->prev = new_node;
    }
    
    _first = new_node;
    
    if (empty()) {
        _last = _first;
    }
    
    _size++;
}

// O(1)
void int_list_t::push_back(int new_val) {
    node_t *new_node = new node_t(new_val, nullptr, _last);
    
    if (!empty()) {
        _last->next = new_node;
    }
    
    _last = new_node;
    
    if (empty()) {
        _first = _last;
    }
    
    _size++;
}

void int_list_t::erase(size_t pos) {
    if (pos >= _size) {
        throw std::out_of_range("index 'pos' in erase() out of bound");
    }
    
    if (pos == 0) {
        pop_front();
        return;
    } else if (pos == (size() - 1)) {
        pop_back();
        return;
    }
    
    node_t *ptr = get_node(pos);
    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;
    delete ptr;
    _size--;
}

void int_list_t::pop_front() {
    if (empty()) {
        throw std::out_of_range("pop_front() out of bound");
    }
    
    node_t *ptr = _first;
    _first = _first->next;
    _first->prev = nullptr;
    delete ptr;
    _size--;
    
    return;
}

void int_list_t::pop_back() {
    if (empty()) {
        throw std::out_of_range("pop_back() out of bound");
    }
    
    node_t *ptr = _last;
    _last = _last->prev;
    _last->next = nullptr;
    delete ptr;
    _size--;
    
    return;
}

// splice part of list into result (not copy!) O($start_pos + $count)
int_list_t int_list_t::splice(size_t start_pos, size_t count) {
    int_list_t res;
    if (count != 0 && start_pos < _size) {
        count = std::min(count, _size - start_pos);
        node_t *first_node = get_node(start_pos);
        node_t *last_node = get_node(start_pos + count - 1);
        
        if (start_pos == 0) {
            _first = last_node->next;
            _first->prev = nullptr;
        } else {
            first_node->prev->next = last_node->next;
        }
        
        if ((start_pos + count) == size()) {
            _last = first_node->prev;
            _last->next = nullptr;
        } else {
            last_node->next->prev = first_node->prev;
        }
        
        res._first = first_node;
        res._first->prev = nullptr;
        
        res._last = last_node;
        res._last->next = nullptr;
        
        res._size = count;
        _size -= count;
    }
    return res;
}

// merge two lists, after operation $other must be valid empty list O(1)
int_list_t &int_list_t::merge(int_list_t &other) {
    if (this != &other && !other.empty()) {
        
        node_t *part1_start = _last;
        node_t *part2_start = other._first;
        node_t *part2_end = other._last;
        
        if (this->empty()) {
            _first = part2_start;
        } else {
            part1_start->next = part2_start;
            part2_start->prev = part1_start;
        }
        
        _last = part2_end;
        _size += other._size;

        other._first = nullptr;
        other._last = nullptr;
        other._size = 0;
    }
    return *this;
}

// O(size)
void int_list_t::reverse() {
    node_t *cur = _last;
    _last = _first;
    _first = cur;
    do {
        node_t *tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;
        cur = tmp;
    } while (cur != nullptr);
}

void int_list_t::swap(int_list_t &other) {
    std::swap(_first, other._first);
    std::swap(_last, other._last);
    std::swap(_size, other._size);
}

std::istream &operator>>(std::istream &stream, int_list_t &list) {
    int val = 0;
    list.clear();
    while (stream >> val) {
        list.push_back(val);
    }
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const int_list_t &list) {
    int_list_t::node_t *ptr = list._first;
    while (ptr != nullptr) {
        stream << ptr->val << ' ';
        ptr = ptr->next;
    }
    return stream;
}

int_list_t::node_t *int_list_t::get_node(size_t pos) const {
    if (pos > size()) {
        throw std::out_of_range("'pos' > 'size' in get_node()");
    }

    if (2 * pos <= _size) {
        node_t *cur = _first;
        while (pos) {
            cur = cur->next;
            pos--;
        }
        return cur;
    } else {
        node_t *cur = _last;
        pos = size() - pos - 1;
        while (pos) {
            cur = cur->prev;
            pos--;
        }
        return cur;
    }
}
