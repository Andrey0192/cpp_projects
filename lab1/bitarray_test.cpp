#include <gtest/gtest.h>
#include "bitarray.h"

TEST(BitArrayTest, ConstructorAndToString) {
    BitArray array1(5, true);
    EXPECT_EQ(array1.to_string(), "11111");

    BitArray array2(5, false);
    EXPECT_EQ(array2.to_string(), "00000");
}

TEST(BitArrayTest, AssignmentOperator) {
    BitArray array1(5, true);
    BitArray array2(5, false);
    array2 = array1;
    EXPECT_EQ(array2.to_string(), "11111");
}

TEST(BitArrayTest, ClearMethod) {
    BitArray array(5, true);
    array.clear();
    EXPECT_EQ(array.to_string(), "00000");
    EXPECT_EQ(array.size(), 5);
}

TEST(BitArrayTest, PushBackMethod) {
    BitArray array(5, false);
    array.push_back(true);
    array.push_back(false);
    EXPECT_EQ(array.to_string(), "0000010");
    EXPECT_EQ(array.size(), 7);
}

TEST(BitArrayTest, ResizeMethod) {
    BitArray array(5, true);
    array.resize(10, false);
    EXPECT_EQ(array.to_string(), "1111100000");
    EXPECT_EQ(array.size(), 10);

    array.resize(3);
    EXPECT_EQ(array.to_string(), "111");
    EXPECT_EQ(array.size(), 3);
}

TEST(BitArrayTest, AnyAndNoneMethods) {
    BitArray array(5, false);
    EXPECT_FALSE(array.any());
    EXPECT_TRUE(array.none());

    array.set(2, true);
    EXPECT_TRUE(array.any());
    EXPECT_FALSE(array.none());
}

TEST(BitArrayTest, SetAndResetMethods) {
    BitArray array(5, false);
    array.set(2, true);
    EXPECT_EQ(array.to_string(), "00100");

    array.set();
    EXPECT_EQ(array.to_string(), "11111");

    array.reset(2);
    EXPECT_EQ(array.to_string(), "11011");

    array.reset();
    EXPECT_EQ(array.to_string(), "00000");
}

TEST(BitArrayTest, BitwiseOperations) {
    BitArray array1(5, true);
    BitArray array2(5, false);

    array1 &= array2;
    EXPECT_EQ(array1.to_string(), "00000");

    array1.set();
    array1 |= array2;
    EXPECT_EQ(array1.to_string(), "11111");

    array1 ^= array2;
    EXPECT_EQ(array1.to_string(), "11111");
}

TEST(BitArrayTest, BitwiseNOT) {
    BitArray array(5, true);
    BitArray result = ~array;
    EXPECT_EQ(result.to_string(), "00000");

    array.reset();
    result = ~array;
    EXPECT_EQ(result.to_string(), "11111");
}

TEST(BitArrayTest, ShiftOperators) {
    BitArray array(5, true);
    array <<= 2;
    EXPECT_EQ(array.to_string(), "11100");

    array >>= 2;
    EXPECT_EQ(array.to_string(), "00111");
}

TEST(BitArrayTest, EqualityOperators) {
    BitArray array1(5, true);
    BitArray array2(5, true);
    EXPECT_TRUE(array1 == array2);

    array2.set(2, false);
    EXPECT_TRUE(array1 != array2);
}

TEST(BitArrayTest, CountMethod) {
    BitArray array(5, true);
    EXPECT_EQ(array.count(), 5);

    array.set(2, false);
    EXPECT_EQ(array.count(), 4);

    array.reset();
    EXPECT_EQ(array.count(), 0);
}

TEST(BitArrayTest, SwapMethod) {
    BitArray array1(3, true);
    BitArray array2(3, false);
    array1.swap(array2);
    EXPECT_EQ(array1.to_string(), "000");
    EXPECT_EQ(array2.to_string(), "111");
}

TEST(BitArrayTest, SizeAndEmptyMethods) {
    BitArray array(5, false);
    EXPECT_EQ(array.size(), 5);
    EXPECT_FALSE(array.empty());

    array.clear();
    EXPECT_EQ(array.size(), 5);
    EXPECT_EQ(array.to_string(), "00000");

    BitArray emptyArray(0);
    EXPECT_EQ(emptyArray.size(), 0);
    EXPECT_TRUE(emptyArray.empty());
}

TEST(BitArrayTest, ConstructorWithVariousValues) {
    BitArray array1(0);
    EXPECT_EQ(array1.size(), 0);
    EXPECT_TRUE(array1.empty());

    BitArray array2(10, true);
    EXPECT_EQ(array2.size(), 10);
    EXPECT_EQ(array2.to_string(), "1111111111");

    BitArray array3(10, false);
    EXPECT_EQ(array3.size(), 10);
    EXPECT_EQ(array3.to_string(), "0000000000");
}

TEST(BitArrayTest, SetAndResetBoundaryValues) {
    BitArray array(5, false);

    array.set(0, true);
    EXPECT_EQ(array.to_string(), "10000");
    array.reset(0);
    EXPECT_EQ(array.to_string(), "00000");

    array.set(4, true);
    EXPECT_EQ(array.to_string(), "00001");
    array.reset(4);
    EXPECT_EQ(array.to_string(), "00000");

    EXPECT_THROW(array.set(5, true), std::out_of_range);
    EXPECT_THROW(array.reset(5), std::out_of_range);
}

TEST(BitArrayTest, ResizeBoundaryValues) {
    BitArray array(5, true);

    array.resize(100, false);
    EXPECT_EQ(array.size(), 100);
    EXPECT_EQ(array.to_string().substr(0, 5), "11111");
    EXPECT_EQ(array.to_string().substr(5), std::string(95, '0'));

    array.resize(1);
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.to_string(), "1");
}

TEST(BitArrayTest, PushBackMultipleElements) {
    BitArray array(0);

    for (int i = 0; i < 10; ++i) {
        array.push_back(i % 2 == 0);
    }
    EXPECT_EQ(array.size(), 10);
    EXPECT_EQ(array.to_string(), "1010101010");
}

TEST(BitArrayTest, AnyAndNoneEdgeCases) {
    BitArray array(5, false);
    EXPECT_FALSE(array.any());
    EXPECT_TRUE(array.none());

    array.set(2, true);
    EXPECT_TRUE(array.any());
    EXPECT_FALSE(array.none());

    array.reset(2);
    EXPECT_FALSE(array.any());
    EXPECT_TRUE(array.none());
}

TEST(BitArrayTest, BitwiseOperationsWithDifferentSizes) {
    BitArray array1(5, true);
    BitArray array2(3, false);

    EXPECT_THROW(array1 &= array2, std::invalid_argument);
    EXPECT_THROW(array1 |= array2, std::invalid_argument);
    EXPECT_THROW(array1 ^= array2, std::invalid_argument);
}

TEST(BitArrayTest, BitwiseNOTEdgeCases) {
    BitArray emptyArray(0);
    BitArray result = ~emptyArray;
    EXPECT_EQ(result.size(), 0);
    EXPECT_TRUE(result.empty());

    BitArray singleElementArray(1, true);
    result = ~singleElementArray;
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.to_string(), "0");

    singleElementArray.reset();
    result = ~singleElementArray;
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.to_string(), "1");
}

TEST(BitArrayTest, ShiftOperationsBoundaryValues) {
    BitArray array(5, true);

    array <<= 5;
    EXPECT_EQ(array.to_string(), "00000");

    array.set();
    array >>= 5;
    EXPECT_EQ(array.to_string(), "00000");

    array.set();
    array <<= 2;
    EXPECT_EQ(array.to_string(), "11100");

    array >>= 2;
    EXPECT_EQ(array.to_string(), "00111");
}

TEST(BitArrayTest, EqualityOperatorsBoundaryValues) {
    BitArray emptyArray1(0);
    BitArray emptyArray2(0);
    EXPECT_TRUE(emptyArray1 == emptyArray2);

    BitArray singleElementArray1(1, true);
    BitArray singleElementArray2(1, true);
    EXPECT_TRUE(singleElementArray1 == singleElementArray2);

    singleElementArray2.reset(0);
    EXPECT_TRUE(singleElementArray1 != singleElementArray2);
}

TEST(BitArrayTest, CountMethodEdgeCases) {
    BitArray emptyArray(0);
    EXPECT_EQ(emptyArray.count(), 0);

    BitArray singleTrueArray(1, true);
    EXPECT_EQ(singleTrueArray.count(), 1);

    BitArray singleFalseArray(1, false);
    EXPECT_EQ(singleFalseArray.count(), 0);

    BitArray alternatingArray(10);
    for (int i = 0; i < 10; i += 2) {
        alternatingArray.set(i, true);
    }
    EXPECT_EQ(alternatingArray.count(), 5);
}

TEST(BitArrayTest, SwapMethodEdgeCases) {
    BitArray emptyArray1(0);
    BitArray emptyArray2(0);
    emptyArray1.swap(emptyArray2);
    EXPECT_TRUE(emptyArray1.empty());
    EXPECT_TRUE(emptyArray2.empty());

    BitArray singleElementArray1(1, true);
    BitArray singleElementArray2(1, false);
    singleElementArray1.swap(singleElementArray2);
    EXPECT_EQ(singleElementArray1.to_string(), "0");
    EXPECT_EQ(singleElementArray2.to_string(), "1");
}

TEST(BitArrayTest, LeftShiftOperator) {
    BitArray array(5);
    array.set(0, true);
    array.set(2, true);
    array.set(4, true);

    BitArray result1 = array << 1;
    EXPECT_EQ(result1.to_string(), "01010");

    BitArray result2 = array << 2;
    EXPECT_EQ(result2.to_string(), "10100");

    BitArray result3 = array << 5;
    EXPECT_EQ(result3.to_string(), "00000");
}

TEST(BitArrayTest, RightShiftOperator) {
    BitArray array(5);
    array.set(0, true);
    array.set(2, true);
    array.set(4, true);

    BitArray result1 = array >> 1;
    EXPECT_EQ(result1.to_string(), "01010");

    BitArray result2 = array >> 2;
    EXPECT_EQ(result2.to_string(), "00101");

    BitArray result3 = array >> 5;
    EXPECT_EQ(result3.to_string(), "00000");
}

TEST(BitArrayTest, ShiftOperatorsBoundaryValues) {
    BitArray array(5, true);

    BitArray resultLeft0 = array << 0;
    EXPECT_EQ(resultLeft0.to_string(), "11111");

    BitArray resultRight0 = array >> 0;
    EXPECT_EQ(resultRight0.to_string(), "11111");

    BitArray resultLeftOverflow = array << 10;
    BitArray resultRightOverflow = array >> 10;
    EXPECT_EQ(resultLeftOverflow.to_string(), "00000");
    EXPECT_EQ(resultRightOverflow.to_string(), "00000");
}
