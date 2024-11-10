//
// Created by PC on 05.11.2024.
//

#ifndef LAB1_BITARRAY_H
#define LAB1_BITARRAY_H

#include "string"

/**
 * @class BitArray
 * @brief A dynamic array of bits that supports bitwise operations and resizing.
 *
 * The BitArray class allows the user to manage an array of bits with dynamic resizing capabilities.
 * It provides bitwise operations such as AND, OR, and XOR, as well as shift operations and utility
 * functions to manipulate and query the bit array.
 */
class BitArray {
    /**
     * @brief Enum for array configuration constants.
     *
     * Defines initial capacity, resize factor, and maximum capacity for the BitArray.
     */
    enum {
        start_length_array = 8, /**< Initial capacity of the array. */
        resize_factor = 2,      /**< Factor by which the array size increases when resized. */
        max_length_array = 300,  /**< Maximum allowed capacity of the array. */
    };

    /**
     * @brief Pointer to the dynamic array holding the bit values.
     *
     * Each element in the array represents a bit, with `true` representing 1 and `false` representing 0.
     */
    bool *data{nullptr};

    /**
    * @brief The number of bits currently stored in the array.
    *
    * This represents the logical size of the BitArray, i.e., the number of bits that have been set or reserved.
    */
    int length{0};

    /**
     * @brief The allocated physical size of the array in terms of the number of bits it can hold.
     *
     * This represents the current capacity of the array, which may be greater than or equal to `length`.
     */
    int capacity{0};

public:
    /**
 * @brief Default constructor that initializes an empty BitArray with default capacity.
 *
 * This constructor initializes the BitArray with zero length and a predefined starting capacity.
 * All bits are initially set to false (0).
 */
    BitArray() : length(0), capacity(start_length_array) {
        data = new bool[start_length_array];
        *data = false;// инициализируем нулями
    }

    /**
    * @brief Destructor that deallocates the memory used by the BitArray.
    */
    ~BitArray() { delete[] data; }

    /**
    * @brief Constructor that initializes a BitArray with a given length and default bit value.
    * @param length The initial number of bits in the array.
    * @param value The initial value of each bit (true for 1, false for 0).
    */
    explicit BitArray(int num_bits, bool value = 0) : BitArray() {
        resize(num_bits);
        for (int i = 0; i < length; ++i) {
            data[i] = value;
        };
    };

    /**
    * @brief Copy constructor that creates a new BitArray as a copy of another.
    * @param other The BitArray to copy from.
    */
    BitArray(const BitArray &other) : length(other.length), capacity(other.capacity) {
        data = new bool[capacity];
        for (int i = 0; i < length; ++i) {
            data[i] = other[i];
        }
    }

    //-----------------------------------

    /**
    * @brief Assignment operator that copies the contents of another BitArray.
    * @param other The BitArray to copy from.
    * @return A reference to the modified BitArray.
    */
    BitArray &operator=(const BitArray &other);

    /**
     * @brief Swaps the contents of the current BitArray with another BitArray.
     * @param b Another BitArray to swap with.
     */
    void swap(BitArray &b);

    /**
     * @brief Adds a new bit to the end of the BitArray. Resizes the array if necessary.
     * @param bit The bit value (true for 1, false for 0) to add.
     */
    void push_back(bool bit);

    /**
     * @brief Resizes the BitArray to a new size, initializing any new bits to a specified value.
     * @param num_bits The new number of bits in the array.
     * @param value The value to initialize any new bits (if the array is expanded).
     */
    void resize(int num_bits, bool value = false);

    /**
     * @brief Clears all bits in the BitArray by setting them to false.
     */
    void clear();

    /**
     * @brief Checks if any bit in the BitArray is set to true (1).
     * @return true if at least one bit is true, false otherwise.
     */
    bool any() const;

    /**
     * @brief Checks if all bits in the BitArray are set to false (0).
     * @return true if all bits are false, false otherwise.
     */
    bool none() const;

    /**
     * @brief Counts the number of bits set to true (1) in the BitArray.
     * @return The number of bits set to true.
     */
    int count() const;

    /**
     * @brief Returns the number of bits in the BitArray.
     * @return The length of the BitArray.
     */
    int size() const;

    /**
     * @brief Checks if the BitArray is empty (has no bits).
     * @return true if the BitArray has zero bits, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Sets a bit at a specified index to a given value.
     * @param n The index of the bit to set.
     * @param val The value to set the bit (true for 1, false for 0).
     * @return A reference to the modified BitArray.
     * @throw std::out_of_range if the index is out of bounds.
     */
    BitArray &set(int n, bool val = true);

    /**
     * @brief Sets all bits in the BitArray to true (1).
     * @return A reference to the modified BitArray.
     */
    BitArray &set();

    /**
     * @brief Resets a bit at a specified index to false (0).
     * @param n The index of the bit to reset.
     * @return A reference to the modified BitArray.
     * @throw std::out_of_range if the index is out of bounds.
     */
    BitArray &reset(int n);

    /**
     * @brief Resets all bits in the BitArray to false (0).
     * @return A reference to the modified BitArray.
     */
    BitArray &reset();

    /**
     * @brief Bitwise NOT operator that inverts all bits in the BitArray.
     * @return A new BitArray with all bits inverted.
     */
    BitArray operator~() const;

    /**
     * @brief Bitwise AND assignment operator that performs a bitwise AND with another BitArray.
     * @param b The BitArray to AND with.
     * @return A reference to the modified BitArray.
     * @throw std::invalid_argument if the sizes of the BitArrays do not match.
     */
    BitArray &operator&=(const BitArray &b);

    /**
     * @brief Bitwise OR assignment operator that performs a bitwise OR with another BitArray.
     * @param b The BitArray to OR with.
     * @return A reference to the modified BitArray.
     * @throw std::invalid_argument if the sizes of the BitArrays do not match.
     */
    BitArray &operator|=(const BitArray &b);

    /**
     * @brief Bitwise XOR assignment operator that performs a bitwise XOR with another BitArray.
     * @param b The BitArray to XOR with.
     * @return A reference to the modified BitArray.
     * @throw std::invalid_argument if the sizes of the BitArrays do not match.
     */
    BitArray &operator^=(const BitArray &b);

    /**
     * @brief Left shift assignment operator that shifts the bits left by a specified number of positions.
     * @param n The number of positions to shift left.
     * @return A reference to the modified BitArray.
     */
    BitArray &operator<<=(int n);

    /**
     * @brief Right shift assignment operator that shifts the bits right by a specified number of positions.
     * @param n The number of positions to shift right.
     * @return A reference to the modified BitArray.
     */
    BitArray &operator>>=(int n);

    /**
     * @brief Accesses the value of a bit at a specified index.
     * @param i The index of the bit to access.
     * @return The value of the bit at the specified index.
     * @throw std::out_of_range if the index is out of bounds.
     */
    bool operator[](int i) const;

    /**
     * @brief Returns a string representation of the BitArray.
     * @return A string of '0's and '1's representing the bit values in the array.
     */
    std::string to_string() const;

    /**
     * @brief Left shift operator that returns a new BitArray shifted by a specified number of positions.
     *
     * This operator creates a new BitArray where each bit is shifted left by `n` positions.
     * Bits shifted beyond the array length are discarded, and new positions are filled with false (0).
     *
     * @param n The number of positions to shift left.
     * @return A new BitArray with bits shifted left by `n` positions.
     */
    BitArray operator<<(int n) const;

    /**
     * @brief Right shift operator that returns a new BitArray shifted by a specified number of positions.
     *
     * This operator creates a new BitArray where each bit is shifted right by `n` positions.
     * Bits shifted beyond the array length are discarded, and new positions are filled with false (0).
     *
     * @param n The number of positions to shift right.
     * @return A new BitArray with bits shifted right by `n` positions.
     */
    BitArray operator>>(int n) const;
};
/**
 * @brief Equality operator that checks if two BitArrays are identical.
 *
 * This operator compares two BitArrays element by element. Two BitArrays are considered
 * equal if they have the same length and each corresponding bit has the same value.
 *
 * @param a The first BitArray to compare.
 * @param b The second BitArray to compare.
 * @return true if the BitArrays are equal, false otherwise.
 */
    bool operator==(const BitArray& a, const BitArray& b);

/**
 * @brief Inequality operator that checks if two BitArrays are different.
 *
 * This operator compares two BitArrays element by element. Two BitArrays are considered
 * different if they have different lengths or if at least one corresponding bit has a different value.
 *
 * @param a The first BitArray to compare.
 * @param b The second BitArray to compare.
 * @return true if the BitArrays are not equal, false otherwise.
 */
    bool operator!=(const BitArray& a, const BitArray& b);

/**
 * @brief Bitwise AND operator that performs an element-wise AND between two BitArrays.
 *
 * This operator creates a new BitArray where each bit is the result of the AND operation
 * between corresponding bits of the two input BitArrays. Both BitArrays must have the same length.
 *
 * @param b1 The first BitArray for the AND operation.
 * @param b2 The second BitArray for the AND operation.
 * @return A new BitArray with the result of the AND operation.
 * @throw std::invalid_argument if the BitArrays have different lengths.
 */
    BitArray operator&(const BitArray& b1, const BitArray& b2);

/**
 * @brief Bitwise OR operator that performs an element-wise OR between two BitArrays.
 *
 * This operator creates a new BitArray where each bit is the result of the OR operation
 * between corresponding bits of the two input BitArrays. Both BitArrays must have the same length.
 *
 * @param b1 The first BitArray for the OR operation.
 * @param b2 The second BitArray for the OR operation.
 * @return A new BitArray with the result of the OR operation.
 * @throw std::invalid_argument if the BitArrays have different lengths.
 */
    BitArray operator|(const BitArray& b1, const BitArray& b2);

/**
 * @brief Bitwise XOR operator that performs an element-wise XOR between two BitArrays.
 *
 * This operator creates a new BitArray where each bit is the result of the XOR operation
 * between corresponding bits of the two input BitArrays. Both BitArrays must have the same length.
 *
 * @param b1 The first BitArray for the XOR operation.
 * @param b2 The second BitArray for the XOR operation.
 * @return A new BitArray with the result of the XOR operation.
 * @throw std::invalid_argument if the BitArrays have different lengths.
 */
    BitArray operator^(const BitArray& b1, const BitArray& b2);



//    //Обменивает значения двух битовых массивов.
//    void swap(BitArray& b);
//
//    BitArray& operator=(const BitArray& b);
//
//
//    //Изменяет размер массива. В случае расширения, новые элементы
//    //инициализируются значением value.
//    void resize(int num_bits, bool value = false);
//    //Очищает массив.
//    void clear();
//    //Добавляет новый бит в конец массива. В случае необходимости
//    //происходит перераспределение памяти.
//    void push_back(bool bit);
//
//
//    //Битовые операции над массивами.
//    //Работают только на массивах одинакового размера.
//    //Обоснование реакции на параметр неверного размера входит в задачу.
//    BitArray& operator&=(const BitArray& b);
//    BitArray& operator|=(const BitArray& b);
//    BitArray& operator^=(const BitArray& b);
//
//    //Битовый сдвиг с заполнением нулями.
//    BitArray& operator<<=(int n);
//    BitArray& operator>>=(int n);


//-----------------------------------
//
//
//    //Устанавливает бит с индексом n в значение val.
//    BitArray& set(int n, bool val = true);
//    //Заполняет массив истиной.
//    BitArray& set();
//
//    //Устанавливает бит с индексом n в значение false.
//    BitArray& reset(int n);
//    //Заполняет массив ложью.
//    BitArray& reset();
//
//    //true, если массив содержит истинный бит.
//    bool any() const;
//    //true, если все биты массива ложны.
//    bool none() const;
//    //Битовая инверсия
//    BitArray operator~() const;
//    //Подсчитывает количество единичных бит.
//    int count() const;
//
//
//    //Возвращает значение бита по индексу i.
//    bool operator[](int i) const;
//
//    int size() const;
//    bool empty() const;
//
//    //Возвращает строковое представление массива.
//    std::string to_string() const;
//};
//


#endif //LAB1_BITARRAY_H
