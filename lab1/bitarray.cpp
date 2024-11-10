//////
////// Created by PC on 05.11.2024.
//////

#include "bitarray.h"
#include <stdexcept>
#include <string>

BitArray BitArray::operator<<(int n) const {
    BitArray result(length, false);

    if (n >= length) {
        return result;
    }

    for (int i = 0; i < length - n; ++i) {
        result.data[i] = data[i + n];
    }

    return result;
}

BitArray BitArray::operator>>(int n) const {
    BitArray result(length, false);

    if (n >= length) {
        return result;
    }

    for (int i = length - 1; i >= n; --i) {
        result.data[i] = data[i - n];
    }

    return result;
}

void BitArray::swap(BitArray& b) {
    if (this == &b) {
        return;
    }
    int lnt = length > b.length ? length : b.length;
    for (int i = 0; i < lnt; ++i) {
        std::swap(data[i], b.data[i]);
    }
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this == &b) {
        return *this;
    }
    length = b.length;
    capacity = b.capacity;
    delete[] data;
    data = new bool[capacity];
    for (int i = 0; i < length; ++i) {
        data[i] = b.data[i];
    }
    return *this;
}

void BitArray::clear() {
    for (int i = 0; i < length; ++i) {
        data[i] = false;
    }
}

void BitArray::push_back(bool bit) {
    if (length >= capacity) {
        resize(length + 1, false);
        data[length - 1] = bit;
        return;
    }
    data[length++] = bit;
}

void BitArray::resize(int num_bits, bool value) {
    if (num_bits <= length) {
        length = num_bits;
        return;
    }

    if (num_bits > length && num_bits <= capacity) {
        for (int i = length; i < num_bits; ++i) {
            data[i] = value;
        }
    }

    if (num_bits > capacity) {
        int new_capacity = capacity > 0 ? capacity : 1;
        while (new_capacity < num_bits) {
            new_capacity *= resize_factor;
        }

        bool* new_data = new bool[new_capacity];

        for (int i = 0; i < length; ++i) {
            new_data[i] = data[i];
        }

        for (int i = length; i < num_bits; ++i) {
            new_data[i] = value;
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    length = num_bits;
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (length != b.length) {
        throw std::invalid_argument("Array sizes do not match");
    }
    for (int i = 0; i < length; ++i) {
        data[i] &= b.data[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (length != b.length) {
        throw std::invalid_argument("Array sizes do not match");
    }
    for (int i = 0; i < length; ++i) {
        data[i] |= b.data[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (length != b.length) {
        throw std::invalid_argument("Array sizes do not match");
    }
    for (int i = 0; i < length; ++i) {
        data[i] ^= b.data[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    for (int i = 0; i < length - n; ++i) {
        data[i] = data[i + n];
    }
    for (int i = length - n; i < length; ++i) {
        data[i] = false;
    }
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    for (int i = length - 1; i >= n; --i) {
        data[i] = data[i - n];
    }
    for (int i = 0; i < n; ++i) {
        data[i] = false;
    }
    return *this;
}

BitArray& BitArray::set(int n, bool val) {
    if (n < 0 || n >= length) throw std::out_of_range("Index out of range");
    data[n] = val;
    return *this;
}

BitArray& BitArray::set() {
    for (int i = 0; i < length; ++i) {
        data[i] = true;
    }
    return *this;
}

BitArray& BitArray::reset(int n) {
    if (n < 0 || n >= length) throw std::out_of_range("Index out of range");
    data[n] = false;
    return *this;
}

BitArray& BitArray::reset() {
    for (int i = 0; i < length; ++i) {
        data[i] = false;
    }
    return *this;
}

bool BitArray::any() const {
    for (int i = 0; i < length; ++i) {
        if (data[i]) {
            return true;
        }
    }
    return false;
}

bool BitArray::none() const {
    for (int i = 0; i < length; ++i) {
        if (data[i]) {
            return false;
        }
    }
    return true;
}

BitArray BitArray::operator~() const {
    BitArray result(length);
    for (int i = 0; i < length; ++i) {
        result.data[i] = !data[i];
    }
    return result;
}

int BitArray::count() const {
    int count = 0;
    for (int i = 0; i < length; ++i) {
        if (data[i]) {
            count++;
        }
    }
    return count;
}

bool BitArray::operator[](int i) const {
    if (i < 0 || i >= length) throw std::out_of_range("Index out of range");
    return data[i];
}

int BitArray::size() const {
    return length;
}

bool BitArray::empty() const {
    return length == 0;
}

std::string BitArray::to_string() const {
    std::string str;
    for (int i = 0; i < length; ++i) {
        str.push_back(data[i] ? '1' : '0');
    }
    return str;
}

bool operator==(const BitArray& a, const BitArray& b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("Array sizes do not match");
    }
    BitArray result(b1.size());
    for (int i = 0; i < b1.size(); ++i) {
        result.set(i, b1[i] & b2[i]);
    }
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("Array sizes do not match");
    }
    BitArray result(b1.size());
    for (int i = 0; i < b1.size(); ++i) {
        result.set(i, b1[i] | b2[i]);
    }
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("Array sizes do not match");
    }
    BitArray result(b1.size());
    for (int i = 0; i < b1.size(); ++i) {
        result.set(i, b1[i] ^ b2[i]);
    }
    return result;
}
