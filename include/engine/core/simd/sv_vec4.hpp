#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tracy/Tracy.hpp>
#include "util.hpp"

#include "s_vec4.hpp"


namespace engine::core::simd {
    inline void clear(std::vector<glm::vec4>& a) {
        const std::size_t items = a.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        __m256 zero = _mm256_set1_vec4(0.0f);

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            _mm256_storeu_vec4(&a[i], zero);
        }

        for (std::size_t i = tail; i < items; i++) {
            a[i] = glm::vec4(0.0f);
        }
    }

    inline std::vector<glm::vec4>& add(std::vector<glm::vec4>& a, const std::vector<glm::vec4>& b) {
        const std::size_t items = a.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 vec_1 = _mm256_loadu_vec4(&a[i]);
            __m256 vec_2 = _mm256_loadu_vec4(&b[i]);

            vec_1 = _mm256_add_vec4(vec_1, vec_2);
            _mm256_storeu_vec4(&a[i], vec_1);
        }

        for (std::size_t i = tail; i < items; i++)
            a[i] += b[i];

        return a;
    }

    inline std::vector<glm::vec4>& add(std::vector<glm::vec4>& a, glm::vec4 b) {
        const std::size_t items = a.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        __m256 vec_2 = _mm256_set1_vec4(b);

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 vec_1 = _mm256_loadu_vec4(&a[i]);

            vec_1 = _mm256_add_vec4(vec_1, vec_2);
            _mm256_storeu_vec4(&a[i], vec_1);
        }

        for (std::size_t i = tail; i < items; i++)
            a[i] += b;

        return a;
    }

    inline std::vector<glm::vec4>& sub(std::vector<glm::vec4>& a, const std::vector<glm::vec4>& b) {
        const std::size_t items = a.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 vec_1 = _mm256_loadu_vec4(&a[i]);
            __m256 vec_2 = _mm256_loadu_vec4(&b[i]);

            vec_1 = _mm256_sub_vec4(vec_1, vec_2);
            _mm256_storeu_vec4(&a[i], vec_1);
        }

        for (std::size_t i = tail; i < items; i++)
            a[i] -= b[i];

        return a;
    }

    inline std::vector<glm::vec4>& sub(std::vector<glm::vec4>& a, glm::vec4 b) {
        const std::size_t items = a.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        __m256 vec_2 = _mm256_set1_vec4(b);

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 vec_1 = _mm256_loadu_vec4(&a[i]);

            vec_1 = _mm256_sub_vec4(vec_1, vec_2);
            _mm256_storeu_vec4(&a[i], vec_1);
        }

        for (std::size_t i = tail; i < items; i++)
            a[i] -= b;

        return a;
    }

    inline std::vector<glm::vec4>& mul(std::vector<glm::vec4>& a, const std::vector<glm::vec4>& b) {
        const std::size_t items = a.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 vec_1 = _mm256_loadu_vec4(&a[i]);
            __m256 vec_2 = _mm256_loadu_vec4(&b[i]);

            vec_1 = _mm256_mul_vec4(vec_1, vec_2);
            _mm256_storeu_vec4(&a[i], vec_1);
        }

        for (std::size_t i = tail; i < items; i++)
            a[i] *= b[i];

        return a;
    }

    inline std::vector<glm::vec4>& mul(std::vector<glm::vec4>& a, glm::vec4 b) {
        const std::size_t items = a.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        __m256 vec_2 = _mm256_set1_vec4(b);

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 vec_1 = _mm256_loadu_vec4(&a[i]);

            vec_1 = _mm256_mul_vec4(vec_1, vec_2);
            _mm256_storeu_vec4(&a[i], vec_1);
        }

        for (std::size_t i = tail; i < items; i++)
            a[i] *= b;

        return a;
    }

    inline std::vector<glm::vec4>& mul(std::vector<glm::vec4>& a, float b) {
        mul(a, glm::vec4(b));

        return a;
    }

    inline std::vector<glm::vec4>& mul(std::vector<glm::vec4>& a, const std::vector<float>& b) {
        const std::size_t items = a.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 vec_1 = _mm256_loadu_vec4(&a[i]);
            __m256 scalars = _mm256_alignf_vec4(b[i], b[i + 1]);

            vec_1 = _mm256_mul_vec4(vec_1, scalars);
            _mm256_storeu_vec4(&a[i], vec_1);
        }

        for (std::size_t i = tail; i < items; i++)
            a[i] *= b[i];

        return a;
    }

    inline std::vector<glm::vec4>& div(std::vector<glm::vec4>& a, const std::vector<glm::vec4>& b) {
        const std::size_t items = a.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 vec_1 = _mm256_loadu_vec4(&a[i]);
            __m256 vec_2 = _mm256_loadu_vec4(&b[i]);

            vec_1 = _mm256_div_vec4(vec_1, vec_2);
            _mm256_storeu_vec4(&a[i], vec_1);
        }

        for (std::size_t i = tail; i < items; i++)
            a[i] /= b[i];

        return a;
    }

    inline std::vector<glm::vec4>& div(std::vector<glm::vec4>& a, glm::vec4 b) {
        const std::size_t items = a.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        __m256 vec_2 = _mm256_set1_vec4(b);

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 vec_1 = _mm256_loadu_vec4(&a[i]);

            vec_1 = _mm256_div_vec4(vec_1, vec_2);
            _mm256_storeu_vec4(&a[i], vec_1);
        }

        for (std::size_t i = tail; i < items; i++)
            a[i] /= b;

        return a;
    }

    inline std::vector<glm::vec4>& div(std::vector<glm::vec4>& a, float b) {
        div(a, glm::vec4(b));

        return a;
    }

    inline std::vector<glm::vec4>& div(std::vector<glm::vec4>& a, const std::vector<float>& b) {
        const std::size_t items = a.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 vec_1 = _mm256_loadu_vec4(&a[i]);
            __m256 scalars = _mm256_alignf_vec4(b[i], b[i + 1]);

            vec_1 = _mm256_div_vec4(vec_1, scalars);
            _mm256_storeu_vec4(&a[i], vec_1);
        }

        for (std::size_t i = tail; i < items; i++)
            a[i] /= b[i];

        return a;
    }

    inline std::vector<glm::vec4>& magnitude_squared(std::vector<glm::vec4>& dest, const std::vector<glm::vec4>& src) {
        const std::size_t items = src.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 v = _mm256_loadu_vec4(&src[i]);
            __m256 sq = _mm256_length2_vec4(v);

            _mm256_storeu_vec4(&dest[i], sq);
        }

        for (std::size_t i = tail; i < items; i++)
            dest[i] = glm::vec4(glm::dot(src[i], src[i]));

        return dest;
    }

    inline std::vector<glm::vec4>& magnitude(std::vector<glm::vec4>& dest, const std::vector<glm::vec4>& src) {
        const std::size_t items = src.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 v = _mm256_loadu_vec4(&src[i]);
            __m256 len = _mm256_length_vec4(v);

            _mm256_storeu_vec4(&dest[i], len);
        }

        for (std::size_t i = tail; i < items; i++)
            dest[i] = glm::vec4(glm::length(src[i]));

        return dest;
    }

    inline std::vector<glm::vec4>& normalize(std::vector<glm::vec4>& dest, const std::vector<glm::vec4>& src) {
        const std::size_t items = src.size();
        const std::size_t tail = items - items % OFFSET_256::vec4;

        for (std::size_t i = 0; i < tail; i += OFFSET_256::vec4) {
            __m256 v = _mm256_loadu_vec4(&src[i]);
            __m256 result = _mm256_norm_vec4(v);

            _mm256_storeu_vec4(&dest[i], result);
        }

        for (std::size_t i = tail; i < items; i++)
            dest[i] = glm::normalize(src[i]);

        return dest;
    }
}