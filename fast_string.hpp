/**
 * @file fast_string.hpp
 * @brief FastString is a C++ class that provides a fast and optimized way to store and compare fixed-length strings.
 * @author Aaron Qiu
 * @date 2023-04-18
 */

#ifndef FAST_STRING_HPP
#define FAST_STRING_HPP

#include <immintrin.h> // AVX2 header
#include <xmmintrin.h> // SSE header

template <int N>
class alignas(64) FastString {
public:
    /**
     * @brief Constructor.
     * @param str The input C-style string to be copied to the FastString object.
     * @note The length of the input string should be no greater than N.
     */
    FastString(const char* str) {
        static_assert(N > 0, "N must be greater than 0");
        static_assert(N <= 64, "N must be less than or equal to 64");
        std::char_traits<char>::copy(data_, str, N); // Zero-copy the input string to the first N bytes of the character array
    }

    /**
     * @brief Equality operator.
     * @param other The FastString object to be compared with.
     * @return true if the FastString objects are equal, false otherwise.
     */
    bool operator==(const FastString& other) const {
        return compare(other, std::integral_constant<bool, (N <= 16)>());
    }

private:
    // Helper function for SSE comparison
    constexpr bool sseCompare(const FastString& other) const {
        __m128i xmm1 = _mm_load_si128(reinterpret_cast<const __m128i*>(data_));
        __m128i xmm2 = _mm_load_si128(reinterpret_cast<const __m128i*>(other.data_));
        __m128i result = _mm_cmpeq_epi8(xmm1, xmm2);
        int mask = _mm_movemask_epi8(result);
        return mask == 0xFFFF;
    }

    // Helper function for AVX comparison
    constexpr bool avxCompare(const FastString& other) const {
        __m256i ymm1 = _mm256_load_si256(reinterpret_cast<const __m256i*>(data_));
        __m256i ymm2 = _mm256_load_si256(reinterpret_cast<const __m256i*>(other.data_));
        __m256i result = _mm256_cmpeq_epi8(ymm1, ymm2);
        int mask = _mm256_movemask_epi8(result);
        return mask == 0xFFFFFFFF;
    }

    // Compare using SSE or AVX instructions depending on N
    constexpr bool compare(const FastString& other, std::true_type /* use SSE */) const {
        return sseCompare(other);
    }

    constexpr bool compare(const FastString& other, std::false_type /* use AVX */) const {
        return avxCompare(other);
    }

private:
    alignas(64) char data_[64]; // Character array aligned to cache line, fixed size of 64 bytes
};

#endif // FAST_STRING_HPP
