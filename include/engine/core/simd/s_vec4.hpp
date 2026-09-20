#pragma once

#include <immintrin.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace engine::core::simd {
    struct OFFSET_256 {
        constexpr static std::size_t vec4 = 32 / sizeof(glm::vec4);
    };

    inline __m256 _mm256_alignf_vec4(float a, float b) {
        return _mm256_set_m128(_mm_set1_ps(b), _mm_set1_ps(a));
    }

    inline __m256 _mm256_load_vec4(glm::vec4* arr_vec) {
        return _mm256_loadu_ps(glm::value_ptr(*arr_vec));
    }

    inline void _mm256_store_vec4(glm::vec4* arr_vec, __m256 val) {
        _mm256_storeu_ps(glm::value_ptr(*arr_vec), val);
    }

    inline __m256 _mm256_set1_vec4(glm::vec4 vec) {
        __m128 v128 = _mm_loadu_ps(&vec.x);
        return _mm256_broadcast_ps(&v128);
    }

    inline __m256 _mm256_set1_vec4(float scalar) {
        return _mm256_set1_vec4(glm::vec4(scalar));
    }

    inline __m256 _mm256_add_vec4(__m256 a, __m256 b) {
        return _mm256_add_ps(a, b);
    }

    inline __m256 _mm256_sub_vec4(__m256 a, __m256 b) {
        return _mm256_sub_ps(a, b);
    }

    inline __m256 _mm256_mul_vec4(__m256 a, __m256 b) {
        return _mm256_mul_ps(a, b);
    }

    inline __m256 _mm256_div_vec4(__m256 a, __m256 b) {
        return _mm256_div_ps(a, b);
    }

    inline __m256 _mm256_length_vec4(__m256 v) {
        __m256 sq  = _mm256_mul_ps(v, v);
        __m256 sum = _mm256_hadd_ps(sq, sq);
        sum = _mm256_hadd_ps(sum, sum);
        return _mm256_sqrt_ps(sum);
    }

    inline __m256 _mm256_length2_vec4(__m256 v) {
        __m256 sq  = _mm256_mul_ps(v, v);
        __m256 sum = _mm256_hadd_ps(sq, sq);
        return _mm256_hadd_ps(sum, sum);
    }

    inline __m256 _mm256_norm_vec4(__m256 v) {
        return _mm256_div_ps(v, _mm256_length_vec4(v));
    }
}