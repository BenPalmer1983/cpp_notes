
#include <iostream>
#include <cstdint>
#include <bit>      // C++20: has_single_bit, popcount, rotl, rotr
#include <array>
#include <cstddef>  // std::byte

int main()
{
    
    // Example 1 - four bits:
    {
        constexpr auto four_bits   = 0b1010u;                   // decimal 10
        static_assert(four_bits == 10);
    }
    
    // Example 2 - one byte:
    {
        constexpr auto one_byte = 0b1111'0000u;                 // 240 (hex 0xF0)
        static_assert(one_byte == 0xF0);
        static_assert(one_byte == 240);
        static_assert(one_byte == 0b1111'0000u);
    }
    
    // Example 3 - mixed byte:
    {
        constexpr auto mixed_byte = 0b1001'0110u;               // 150 (0x96)
        static_assert(mixed_byte == 0x96);
        static_assert(mixed_byte == 150);
        static_assert(mixed_byte == 0b1001'0110u);
    }
    
    // Example 4 - two_bytes:
    {
        constexpr auto two_bytes = 0b0000'0001'1111'0000u;      // 0x01F0 (496)
        static_assert(two_bytes == 0x01F0);
        static_assert(two_bytes == 496);
        static_assert(two_bytes == 0b0000'0001'1111'0000u);
    }




    // Store into explicitly-sized integers:
    /*
    constexpr std::uint8_t  u8  = 0b1101'0110;            // fits in 8 bits
    constexpr std::uint16_t u16 = 0b0000'1111'1010'0001;  // 0x0FA1
    constexpr std::uint32_t u32 = 0b0000'0001'0010'0011'0100'0101'0110'0111u; // 0x01234567
    constexpr std::uint64_t u64 = 0b1ull << 40;           // wide binary via shift + suffix
    */



    return 0;
}





