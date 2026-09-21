#pragma once

#include <cmath>

#include <simde/x86/sse.h>
#include <simde/x86/avx2.h>
#include <simde/x86/fma.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace engine::core::simd {
    using __m256 = simde__m256;
    using __m128 = simde__m128;

    namespace OFFSET_256 {
        constexpr static std::size_t vec4 = 32 / sizeof(glm::vec4);
    };


    inline __m256 _mm256_alignf_vec4(float a, float b) {
        return simde_mm256_set_m128(_mm_set1_ps(b), _mm_set1_ps(a));
    }

    inline __m256 _mm256_loadu_vec4(const glm::vec4* arr_vec) {
        return simde_mm256_loadu_ps(glm::value_ptr(*arr_vec));
    }

    inline void _mm256_storeu_vec4(glm::vec4* arr_vec, __m256 val) {
        simde_mm256_storeu_ps(glm::value_ptr(*arr_vec), val);
    }

    inline __m256 _mm256_set1_vec4(glm::vec4 vec) {
        __m128 v128 = simde_mm_loadu_ps(&vec.x);
        return simde_mm256_broadcast_ps(&v128);
    }

    inline __m256 _mm256_set1_vec4(float scalar) {
        return _mm256_set1_vec4(glm::vec4(scalar));
    }

    inline __m256 _mm256_add_vec4(__m256 a, __m256 b) {
        return simde_mm256_add_ps(a, b);
    }

    inline __m256 _mm256_sub_vec4(__m256 a, __m256 b) {
        return simde_mm256_sub_ps(a, b);
    }

    inline __m256 _mm256_mul_vec4(__m256 a, __m256 b) {
        return simde_mm256_mul_ps(a, b);
    }

    inline __m256 _mm256_div_vec4(__m256 a, __m256 b) {
        return simde_mm256_div_ps(a, b);
    }

    inline __m256 _mm256_fmadd_vec4(__m256 a, __m256 b, __m256 c) {
        return simde_mm256_fmadd_ps(a, b, c);
    }

    inline __m256 _mm256_length2_vec4(__m256 v) {
        __m256 sq    = simde_mm256_mul_ps(v, v);
        __m256 shuf1 = simde_mm256_shuffle_ps(sq, sq, _MM_SHUFFLE(2, 3, 0, 1));
        __m256 sums  = simde_mm256_add_ps(sq, shuf1);
        __m256 shuf2 = simde_mm256_shuffle_ps(sums, sums, _MM_SHUFFLE(1, 0, 3, 2));
        return simde_mm256_add_ps(sums, shuf2);
    }

    inline __m256 _mm256_length_vec4(__m256 v) {
        __m256 dot = _mm256_length2_vec4(v);
        return simde_mm256_sqrt_ps(dot);
    }

    inline __m256 _mm256_norm_vec4(__m256 v) {
        return simde_mm256_div_ps(v, _mm256_length_vec4(v));
    }
}