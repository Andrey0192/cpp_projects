#include <iostream>
#include "bitarray.cpp"
int main() {
    std::cout << "Hello, World!" << std::endl;
    auto bitarray = BitArray(4,0b1101);
    std::cout<<bitarray.to_string()<<"\n";
    bitarray.operator|=(BitArray(4,4));
    bitarray.resize(8);
    std::cout<<bitarray.to_string()<<"\n";



    return 0;
}
