#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#define  BITS_PER_BYTE  8
class BitArray {

    std::vector<unsigned char> data;
    int length{0};

public:
    BitArray() = default;

    explicit BitArray(int num_bits, unsigned long value = 0) : length(num_bits) {
        int num_bytes = (num_bits + BITS_PER_BYTE - 1) / BITS_PER_BYTE;
        data.resize(num_bytes, 0);
        for (int i = 0; i < num_bits; ++i) {
            set(i, value & (1UL << i));
        }
    }

    BitArray(const BitArray& b) : data(b.data), length(b.length) {}

    ~BitArray() = default;

    void swap(BitArray& b) {
        std::swap(data, b.data);
        std::swap(length, b.length);
    }

    BitArray& operator=(const BitArray& b) {
        if (this != &b) {
            data = b.data;
            length = b.length;
        }
        return *this;
    }

    void resize(int num_bits, bool value = false) {
        int old_length = length;
        length = num_bits;
        int num_bytes = (num_bits  - 1) / BITS_PER_BYTE +1 ;
        data.resize(num_bytes, value ? 0xFF : 0x00);

        if (value && num_bits > old_length) {
            for (int i = old_length; i < num_bits; ++i) {
                set(i, true);
            }
        }
        clear_unused_bits();
    }

    void clear() {
        std::fill(data.begin(), data.end(), 0);
        length = 0;
    }

    void push_back(bool bit) {
        if (length % BITS_PER_BYTE == 0) {
            data.push_back(0);
        }
        set(length, bit);
        ++length;
    }

    BitArray& operator&=(const BitArray& b) {
        if (length != b.length) {
            throw std::invalid_argument("Array sizes do not match");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] &= b.data[i];
        }
        return *this;
    }

    BitArray& operator|=(const BitArray& b) {
        if (length != b.length) {
            throw std::invalid_argument("Array sizes do not match");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] |= b.data[i];
        }
        return *this;
    }

    BitArray& operator^=(const BitArray& b) {
        if (length != b.length) {
            throw std::invalid_argument("Array sizes do not match");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] ^= b.data[i];
        }
        return *this;
    }

    BitArray& operator<<=(int n) {
        if (n >= length) {
            clear();
            return *this;
        }
        for (int i = 0; i < length - n; ++i) {
            set(i, get(i + n));
        }
        for (int i = length - n; i < length; ++i) {
            set(i, false);
        }
        return *this;
    }

    BitArray& operator>>=(int n) {
        if (n >= length) {
            clear();
            return *this;
        }
        for (int i = length - 1; i >= n; --i) {
            set(i, get(i - n));
        }
        for (int i = 0; i < n; ++i) {
            set(i, false);
        }
        return *this;
    }

    BitArray operator<<(int n) const {
        BitArray result(*this);
        result <<= n;
        return result;
    }

    BitArray operator>>(int n) const {
        BitArray result(*this);
        result >>= n;
        return result;
    }

    BitArray& set(int n, bool val = true) {
        if (n < 0 || n >= length) {
            throw std::out_of_range("Index out of range");
        }
        int byte_index = n / BITS_PER_BYTE;
        int bit_offset = n % BITS_PER_BYTE;

        if (val) {
            data[byte_index] |= (1 << bit_offset);
        } else {
            data[byte_index] &= ~(1 << bit_offset);
        }
        return *this;
    }

    BitArray& set() {
        std::fill(data.begin(), data.end(), 0xFF);
        clear_unused_bits();
        return *this;
    }

    BitArray& reset(int n) {
        return set(n, false);
    }

    BitArray& reset() {
        clear();
        return *this;
    }

    bool any() const {
        for (const auto& byte : data) {
            if (byte != 0) return true;
        }
        return false;
    }

    bool none() const {
        return !any();
    }

    BitArray operator~() const {
        BitArray result(*this);
        for (unsigned char& byte : result.data) {
            byte = ~byte;
        }
        result.clear_unused_bits();
        return result;
    }

    int count() const {
        int count = 0;
        for (int i = 0; i < length; ++i) {
            if (get(i)) {
                ++count;
            }
        }
        return count;
    }

    bool operator[](int i) const {
        return get(i);
    }

    int size() const {
        return length;
    }

    bool empty() const {
        return length == 0;
    }

    std::string to_string() const {
        std::string result;
        result.reserve(length);
        for (int i = 0; i < length; ++i) {
            result.push_back(get(i) ? '1' : '0');
        }
        std::reverse(result.begin(), result.end());
        return result;

    }

    friend bool operator==(const BitArray& a, const BitArray& b) {
        return a.length == b.length && a.data == b.data;
    }

    friend bool operator!=(const BitArray& a, const BitArray& b) {
        return !(a == b);
    }

    friend BitArray operator&(const BitArray& b1, const BitArray& b2) {
        if (b1.length != b2.length) {
            throw std::invalid_argument("Array sizes do not match");
        }
        BitArray result(b1.length);
        for (size_t i = 0; i < b1.data.size(); ++i) {
            result.data[i] = b1.data[i] & b2.data[i];
        }
        return result;
    }

    friend BitArray operator|(const BitArray& b1, const BitArray& b2) {
        if (b1.length != b2.length) {
            throw std::invalid_argument("Array sizes do not match");
        }
        BitArray result(b1.length);
        for (size_t i = 0; i < b1.data.size(); ++i) {
            result.data[i] = b1.data[i] | b2.data[i];
        }
        return result;
    }

    friend BitArray operator^(const BitArray& b1, const BitArray& b2) {
        if (b1.length != b2.length) {
            throw std::invalid_argument("Array sizes do not match");
        }
        BitArray result(b1.length);
        for (size_t i = 0; i < b1.data.size(); ++i) {
            result.data[i] = b1.data[i] ^ b2.data[i];
        }
        return result;
    }
    
    void clear_unused_bits() {
        int bit_offset = length % BITS_PER_BYTE;
        if (bit_offset != 0) {
            int last_byte_index = length / BITS_PER_BYTE;
            data[last_byte_index] &= (1 << (bit_offset)) - 1;
        }
    }

    bool get(int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        int byte_index = index / BITS_PER_BYTE;
        int bit_offset = index % BITS_PER_BYTE;
        return (data[byte_index] & (1 << bit_offset)) != 0;
    }
};
