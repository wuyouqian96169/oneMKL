/*******************************************************************************
* Copyright 2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions
* and limitations under the License.
*
*
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#include <CL/sycl.hpp>

#include "cpu_common.hpp"
#include "oneapi/mkl/blas/detail/mklcpu/onemkl_blas_mklcpu.hpp"

namespace oneapi {
namespace mkl {
namespace mklcpu {

// Buffer APIs

void gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m, int64_t n,
          int64_t k, float alpha, cl::sycl::buffer<float, 1> &a, int64_t lda,
          cl::sycl::buffer<float, 1> &b, int64_t ldb, float beta, cl::sycl::buffer<float, 1> &c,
          int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char transa_ = *fortran_char(transa);
        const char transb_ = *fortran_char(transb);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_sgemm>(cgh, [=]() {
            ::sgemm((const char *)&transa_, (const char *)&transb_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_INT *)&k, (const float *)&alpha,
                    accessor_a.get_pointer(), (const MKL_INT *)&lda, accessor_b.get_pointer(),
                    (const MKL_INT *)&ldb, (const float *)&beta, accessor_c.get_pointer(),
                    (const MKL_INT *)&ldc);
        });
    });
}

void gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m, int64_t n,
          int64_t k, double alpha, cl::sycl::buffer<double, 1> &a, int64_t lda,
          cl::sycl::buffer<double, 1> &b, int64_t ldb, double beta, cl::sycl::buffer<double, 1> &c,
          int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char transa_ = *fortran_char(transa);
        const char transb_ = *fortran_char(transb);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_dgemm>(cgh, [=]() {
            ::dgemm((const char *)&transa_, (const char *)&transb_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_INT *)&k, (const double *)&alpha,
                    accessor_a.get_pointer(), (const MKL_INT *)&lda, accessor_b.get_pointer(),
                    (const MKL_INT *)&ldb, (const double *)&beta, accessor_c.get_pointer(),
                    (const MKL_INT *)&ldc);
        });
    });
}

void gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m, int64_t n,
          int64_t k, std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a,
          int64_t lda, cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb,
          std::complex<float> beta, cl::sycl::buffer<std::complex<float>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char transa_ = *fortran_char(transa);
        const char transb_ = *fortran_char(transb);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        float beta_real = beta.real(), beta_imag = beta.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_cgemm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex8 beta_ = { beta_real, beta_imag };
            ::cgemm((const char *)&transa_, (const char *)&transb_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_INT *)&k, (const MKL_Complex8 *)&alpha_,
                    accessor_a.get_pointer(), (const MKL_INT *)&lda, accessor_b.get_pointer(),
                    (const MKL_INT *)&ldb, (const MKL_Complex8 *)&beta_, accessor_c.get_pointer(),
                    (const MKL_INT *)&ldc);
        });
    });
}

void gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m, int64_t n,
          int64_t k, std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a,
          int64_t lda, cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb,
          std::complex<double> beta, cl::sycl::buffer<std::complex<double>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char transa_ = *fortran_char(transa);
        const char transb_ = *fortran_char(transb);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        double beta_real = beta.real(), beta_imag = beta.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zgemm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex16 beta_ = { beta_real, beta_imag };
            ::zgemm((const char *)&transa_, (const char *)&transb_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_INT *)&k, (const MKL_Complex16 *)&alpha_,
                    accessor_a.get_pointer(), (const MKL_INT *)&lda, accessor_b.get_pointer(),
                    (const MKL_INT *)&ldb, (const MKL_Complex16 *)&beta_, accessor_c.get_pointer(),
                    (const MKL_INT *)&ldc);
        });
    });
}

void hemm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
          std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
          cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb, std::complex<float> beta,
          cl::sycl::buffer<std::complex<float>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        float beta_real = beta.real(), beta_imag = beta.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_chemm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex8 beta_ = { beta_real, beta_imag };
            ::chemm((const char *)&left_right_, (const char *)&upper_lower_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_Complex8 *)&alpha_, accessor_a.get_pointer(),
                    (const MKL_INT *)&lda, accessor_b.get_pointer(), (const MKL_INT *)&ldb,
                    (const MKL_Complex8 *)&beta_, accessor_c.get_pointer(), (const MKL_INT *)&ldc);
        });
    });
}

void hemm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
          std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
          cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb, std::complex<double> beta,
          cl::sycl::buffer<std::complex<double>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        double beta_real = beta.real(), beta_imag = beta.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zhemm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex16 beta_ = { beta_real, beta_imag };
            ::zhemm((const char *)&left_right_, (const char *)&upper_lower_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_Complex16 *)&alpha_, accessor_a.get_pointer(),
                    (const MKL_INT *)&lda, accessor_b.get_pointer(), (const MKL_INT *)&ldb,
                    (const MKL_Complex16 *)&beta_, accessor_c.get_pointer(), (const MKL_INT *)&ldc);
        });
    });
}

void herk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
          float alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda, float beta,
          cl::sycl::buffer<std::complex<float>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_cherk>(cgh, [=]() {
            ::cherk((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                    (const MKL_INT *)&k, (const float *)&alpha, accessor_a.get_pointer(),
                    (const MKL_INT *)&lda, (const float *)&beta, accessor_c.get_pointer(),
                    (const MKL_INT *)&ldc);
        });
    });
}

void herk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
          double alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda, double beta,
          cl::sycl::buffer<std::complex<double>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zherk>(cgh, [=]() {
            ::zherk((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                    (const MKL_INT *)&k, (const double *)&alpha, accessor_a.get_pointer(),
                    (const MKL_INT *)&lda, (const double *)&beta, accessor_c.get_pointer(),
                    (const MKL_INT *)&ldc);
        });
    });
}

void her2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
           std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
           cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb, float beta,
           cl::sycl::buffer<std::complex<float>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_cher2k>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            ::cher2k((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                     (const MKL_INT *)&k, (const MKL_Complex8 *)&alpha_, accessor_a.get_pointer(),
                     (const MKL_INT *)&lda, accessor_b.get_pointer(), (const MKL_INT *)&ldb,
                     (const float *)&beta, accessor_c.get_pointer(), (const MKL_INT *)&ldc);
        });
    });
}

void her2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
           std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
           cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb, double beta,
           cl::sycl::buffer<std::complex<double>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zher2k>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            ::zher2k((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                     (const MKL_INT *)&k, (const MKL_Complex16 *)&alpha_, accessor_a.get_pointer(),
                     (const MKL_INT *)&lda, accessor_b.get_pointer(), (const MKL_INT *)&ldb,
                     (const double *)&beta, accessor_c.get_pointer(), (const MKL_INT *)&ldc);
        });
    });
}

void symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
          float alpha, cl::sycl::buffer<float, 1> &a, int64_t lda, cl::sycl::buffer<float, 1> &b,
          int64_t ldb, float beta, cl::sycl::buffer<float, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_ssymm>(cgh, [=]() {
            ::ssymm((const char *)&left_right_, (const char *)&upper_lower_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const float *)&alpha, accessor_a.get_pointer(),
                    (const MKL_INT *)&lda, accessor_b.get_pointer(), (const MKL_INT *)&ldb,
                    (const float *)&beta, accessor_c.get_pointer(), (const MKL_INT *)&ldc);
        });
    });
}

void symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
          double alpha, cl::sycl::buffer<double, 1> &a, int64_t lda, cl::sycl::buffer<double, 1> &b,
          int64_t ldb, double beta, cl::sycl::buffer<double, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_dsymm>(cgh, [=]() {
            ::dsymm((const char *)&left_right_, (const char *)&upper_lower_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const double *)&alpha, accessor_a.get_pointer(),
                    (const MKL_INT *)&lda, accessor_b.get_pointer(), (const MKL_INT *)&ldb,
                    (const double *)&beta, accessor_c.get_pointer(), (const MKL_INT *)&ldc);
        });
    });
}

void symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
          std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
          cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb, std::complex<float> beta,
          cl::sycl::buffer<std::complex<float>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        float beta_real = beta.real(), beta_imag = beta.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_csymm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex8 beta_ = { beta_real, beta_imag };
            ::csymm((const char *)&left_right_, (const char *)&upper_lower_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_Complex8 *)&alpha_, accessor_a.get_pointer(),
                    (const MKL_INT *)&lda, accessor_b.get_pointer(), (const MKL_INT *)&ldb,
                    (const MKL_Complex8 *)&beta_, accessor_c.get_pointer(), (const MKL_INT *)&ldc);
        });
    });
}

void symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m, int64_t n,
          std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
          cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb, std::complex<double> beta,
          cl::sycl::buffer<std::complex<double>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        double beta_real = beta.real(), beta_imag = beta.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zsymm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex16 beta_ = { beta_real, beta_imag };
            ::zsymm((const char *)&left_right_, (const char *)&upper_lower_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_Complex16 *)&alpha_, accessor_a.get_pointer(),
                    (const MKL_INT *)&lda, accessor_b.get_pointer(), (const MKL_INT *)&ldb,
                    (const MKL_Complex16 *)&beta_, accessor_c.get_pointer(), (const MKL_INT *)&ldc);
        });
    });
}

void syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
          float alpha, cl::sycl::buffer<float, 1> &a, int64_t lda, float beta,
          cl::sycl::buffer<float, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_ssyrk>(cgh, [=]() {
            ::ssyrk((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                    (const MKL_INT *)&k, (const float *)&alpha, accessor_a.get_pointer(),
                    (const MKL_INT *)&lda, (const float *)&beta, accessor_c.get_pointer(),
                    (const MKL_INT *)&ldc);
        });
    });
}

void syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
          double alpha, cl::sycl::buffer<double, 1> &a, int64_t lda, double beta,
          cl::sycl::buffer<double, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_dsyrk>(cgh, [=]() {
            ::dsyrk((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                    (const MKL_INT *)&k, (const double *)&alpha, accessor_a.get_pointer(),
                    (const MKL_INT *)&lda, (const double *)&beta, accessor_c.get_pointer(),
                    (const MKL_INT *)&ldc);
        });
    });
}

void syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
          std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
          std::complex<float> beta, cl::sycl::buffer<std::complex<float>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        float beta_real = beta.real(), beta_imag = beta.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_csyrk>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex8 beta_ = { beta_real, beta_imag };
            ::csyrk((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                    (const MKL_INT *)&k, (const MKL_Complex8 *)&alpha_, accessor_a.get_pointer(),
                    (const MKL_INT *)&lda, (const MKL_Complex8 *)&beta_, accessor_c.get_pointer(),
                    (const MKL_INT *)&ldc);
        });
    });
}

void syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
          std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
          std::complex<double> beta, cl::sycl::buffer<std::complex<double>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        double beta_real = beta.real(), beta_imag = beta.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zsyrk>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex16 beta_ = { beta_real, beta_imag };
            ::zsyrk((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                    (const MKL_INT *)&k, (const MKL_Complex16 *)&alpha_, accessor_a.get_pointer(),
                    (const MKL_INT *)&lda, (const MKL_Complex16 *)&beta_, accessor_c.get_pointer(),
                    (const MKL_INT *)&ldc);
        });
    });
}

void syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
           float alpha, cl::sycl::buffer<float, 1> &a, int64_t lda, cl::sycl::buffer<float, 1> &b,
           int64_t ldb, float beta, cl::sycl::buffer<float, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_ssyr2k>(cgh, [=]() {
            ::ssyr2k((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                     (const MKL_INT *)&k, (const float *)&alpha, accessor_a.get_pointer(),
                     (const MKL_INT *)&lda, accessor_b.get_pointer(), (const MKL_INT *)&ldb,
                     (const float *)&beta, accessor_c.get_pointer(), (const MKL_INT *)&ldc);
        });
    });
}

void syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
           double alpha, cl::sycl::buffer<double, 1> &a, int64_t lda,
           cl::sycl::buffer<double, 1> &b, int64_t ldb, double beta, cl::sycl::buffer<double, 1> &c,
           int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_dsyr2k>(cgh, [=]() {
            ::dsyr2k((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                     (const MKL_INT *)&k, (const double *)&alpha, accessor_a.get_pointer(),
                     (const MKL_INT *)&lda, accessor_b.get_pointer(), (const MKL_INT *)&ldb,
                     (const double *)&beta, accessor_c.get_pointer(), (const MKL_INT *)&ldc);
        });
    });
}

void syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
           std::complex<float> alpha, cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
           cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb, std::complex<float> beta,
           cl::sycl::buffer<std::complex<float>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        float beta_real = beta.real(), beta_imag = beta.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_csyr2k>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex8 beta_ = { beta_real, beta_imag };
            ::csyr2k((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                     (const MKL_INT *)&k, (const MKL_Complex8 *)&alpha_, accessor_a.get_pointer(),
                     (const MKL_INT *)&lda, accessor_b.get_pointer(), (const MKL_INT *)&ldb,
                     (const MKL_Complex8 *)&beta_, accessor_c.get_pointer(), (const MKL_INT *)&ldc);
        });
    });
}

void syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n, int64_t k,
           std::complex<double> alpha, cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
           cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb, std::complex<double> beta,
           cl::sycl::buffer<std::complex<double>, 1> &c, int64_t ldc) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        double beta_real = beta.real(), beta_imag = beta.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zsyr2k>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex16 beta_ = { beta_real, beta_imag };
            ::zsyr2k((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                     (const MKL_INT *)&k, (const MKL_Complex16 *)&alpha_, accessor_a.get_pointer(),
                     (const MKL_INT *)&lda, accessor_b.get_pointer(), (const MKL_INT *)&ldb,
                     (const MKL_Complex16 *)&beta_, accessor_c.get_pointer(),
                     (const MKL_INT *)&ldc);
        });
    });
}

void trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
          diag unit_diag, int64_t m, int64_t n, float alpha, cl::sycl::buffer<float, 1> &a,
          int64_t lda, cl::sycl::buffer<float, 1> &b, int64_t ldb) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_strmm>(cgh, [=]() {
            ::strmm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const float *)&alpha, accessor_a.get_pointer(), (const MKL_INT *)&lda,
                    accessor_b.get_pointer(), (const MKL_INT *)&ldb);
        });
    });
}

void trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
          diag unit_diag, int64_t m, int64_t n, double alpha, cl::sycl::buffer<double, 1> &a,
          int64_t lda, cl::sycl::buffer<double, 1> &b, int64_t ldb) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_dtrmm>(cgh, [=]() {
            ::dtrmm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const double *)&alpha, accessor_a.get_pointer(), (const MKL_INT *)&lda,
                    accessor_b.get_pointer(), (const MKL_INT *)&ldb);
        });
    });
}

void trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
          diag unit_diag, int64_t m, int64_t n, std::complex<float> alpha,
          cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
          cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_ctrmm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            ::ctrmm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const MKL_Complex8 *)&alpha_, accessor_a.get_pointer(), (const MKL_INT *)&lda,
                    accessor_b.get_pointer(), (const MKL_INT *)&ldb);
        });
    });
}

void trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
          diag unit_diag, int64_t m, int64_t n, std::complex<double> alpha,
          cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
          cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_ztrmm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            ::ztrmm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const MKL_Complex16 *)&alpha_, accessor_a.get_pointer(), (const MKL_INT *)&lda,
                    accessor_b.get_pointer(), (const MKL_INT *)&ldb);
        });
    });
}

void trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
          diag unit_diag, int64_t m, int64_t n, float alpha, cl::sycl::buffer<float, 1> &a,
          int64_t lda, cl::sycl::buffer<float, 1> &b, int64_t ldb) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_strsm>(cgh, [=]() {
            ::strsm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const float *)&alpha, accessor_a.get_pointer(), (const MKL_INT *)&lda,
                    accessor_b.get_pointer(), (const MKL_INT *)&ldb);
        });
    });
}

void trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
          diag unit_diag, int64_t m, int64_t n, double alpha, cl::sycl::buffer<double, 1> &a,
          int64_t lda, cl::sycl::buffer<double, 1> &b, int64_t ldb) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_dtrsm>(cgh, [=]() {
            ::dtrsm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const double *)&alpha, accessor_a.get_pointer(), (const MKL_INT *)&lda,
                    accessor_b.get_pointer(), (const MKL_INT *)&ldb);
        });
    });
}

void trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
          diag unit_diag, int64_t m, int64_t n, std::complex<float> alpha,
          cl::sycl::buffer<std::complex<float>, 1> &a, int64_t lda,
          cl::sycl::buffer<std::complex<float>, 1> &b, int64_t ldb) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_ctrsm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            ::ctrsm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const MKL_Complex8 *)&alpha_, accessor_a.get_pointer(), (const MKL_INT *)&lda,
                    accessor_b.get_pointer(), (const MKL_INT *)&ldb);
        });
    });
}

void trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
          diag unit_diag, int64_t m, int64_t n, std::complex<double> alpha,
          cl::sycl::buffer<std::complex<double>, 1> &a, int64_t lda,
          cl::sycl::buffer<std::complex<double>, 1> &b, int64_t ldb) {
    queue.submit([&](cl::sycl::handler &cgh) {
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        auto accessor_a = a.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_ztrsm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            ::ztrsm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const MKL_Complex16 *)&alpha_, accessor_a.get_pointer(), (const MKL_INT *)&lda,
                    accessor_b.get_pointer(), (const MKL_INT *)&ldb);
        });
    });
}

// USM APIs

cl::sycl::event gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m,
                     int64_t n, int64_t k, float alpha, const float *a, int64_t lda, const float *b,
                     int64_t ldb, float beta, float *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char transa_ = *fortran_char(transa);
        const char transb_ = *fortran_char(transb);
        host_task<class mkl_kernel_sgemm_usm>(cgh, [=]() {
            ::sgemm((const char *)&transa_, (const char *)&transb_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_INT *)&k, (const float *)&alpha, a,
                    (const MKL_INT *)&lda, b, (const MKL_INT *)&ldb, (const float *)&beta, c,
                    (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m,
                     int64_t n, int64_t k, double alpha, const double *a, int64_t lda,
                     const double *b, int64_t ldb, double beta, double *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char transa_ = *fortran_char(transa);
        const char transb_ = *fortran_char(transb);
        host_task<class mkl_kernel_dgemm_usm>(cgh, [=]() {
            ::dgemm((const char *)&transa_, (const char *)&transb_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_INT *)&k, (const double *)&alpha, a,
                    (const MKL_INT *)&lda, b, (const MKL_INT *)&ldb, (const double *)&beta, c,
                    (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m,
                     int64_t n, int64_t k, std::complex<float> alpha, const std::complex<float> *a,
                     int64_t lda, const std::complex<float> *b, int64_t ldb,
                     std::complex<float> beta, std::complex<float> *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char transa_ = *fortran_char(transa);
        const char transb_ = *fortran_char(transb);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        float beta_real = beta.real(), beta_imag = beta.imag();
        host_task<class mkl_kernel_cgemm_usm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex8 beta_ = { beta_real, beta_imag };
            ::cgemm((const char *)&transa_, (const char *)&transb_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_INT *)&k, (const MKL_Complex8 *)&alpha_, a,
                    (const MKL_INT *)&lda, b, (const MKL_INT *)&ldb, (const MKL_Complex8 *)&beta_,
                    c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event gemm(cl::sycl::queue &queue, transpose transa, transpose transb, int64_t m,
                     int64_t n, int64_t k, std::complex<double> alpha,
                     const std::complex<double> *a, int64_t lda, const std::complex<double> *b,
                     int64_t ldb, std::complex<double> beta, std::complex<double> *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char transa_ = *fortran_char(transa);
        const char transb_ = *fortran_char(transb);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        double beta_real = beta.real(), beta_imag = beta.imag();
        host_task<class mkl_kernel_zgemm_usm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex16 beta_ = { beta_real, beta_imag };
            ::zgemm((const char *)&transa_, (const char *)&transb_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_INT *)&k, (const MKL_Complex16 *)&alpha_, a,
                    (const MKL_INT *)&lda, b, (const MKL_INT *)&ldb, (const MKL_Complex16 *)&beta_,
                    c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event hemm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m,
                     int64_t n, std::complex<float> alpha, const std::complex<float> *a,
                     int64_t lda, const std::complex<float> *b, int64_t ldb,
                     std::complex<float> beta, std::complex<float> *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        float beta_real = beta.real(), beta_imag = beta.imag();
        host_task<class mkl_kernel_chemm_usm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex8 beta_ = { beta_real, beta_imag };
            ::chemm((const char *)&left_right_, (const char *)&upper_lower_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_Complex8 *)&alpha_, a, (const MKL_INT *)&lda, b,
                    (const MKL_INT *)&ldb, (const MKL_Complex8 *)&beta_, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event hemm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m,
                     int64_t n, std::complex<double> alpha, const std::complex<double> *a,
                     int64_t lda, const std::complex<double> *b, int64_t ldb,
                     std::complex<double> beta, std::complex<double> *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        double beta_real = beta.real(), beta_imag = beta.imag();
        host_task<class mkl_kernel_zhemm_usm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex16 beta_ = { beta_real, beta_imag };
            ::zhemm((const char *)&left_right_, (const char *)&upper_lower_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_Complex16 *)&alpha_, a, (const MKL_INT *)&lda,
                    b, (const MKL_INT *)&ldb, (const MKL_Complex16 *)&beta_, c,
                    (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event herk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n,
                     int64_t k, float alpha, const std::complex<float> *a, int64_t lda, float beta,
                     std::complex<float> *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        host_task<class mkl_kernel_cherk_usm>(cgh, [=]() {
            ::cherk((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                    (const MKL_INT *)&k, (const float *)&alpha, a, (const MKL_INT *)&lda,
                    (const float *)&beta, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event herk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n,
                     int64_t k, double alpha, const std::complex<double> *a, int64_t lda,
                     double beta, std::complex<double> *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        host_task<class mkl_kernel_zherk_usm>(cgh, [=]() {
            ::zherk((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                    (const MKL_INT *)&k, (const double *)&alpha, a, (const MKL_INT *)&lda,
                    (const double *)&beta, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event her2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n,
                      int64_t k, std::complex<float> alpha, const std::complex<float> *a,
                      int64_t lda, const std::complex<float> *b, int64_t ldb, float beta,
                      std::complex<float> *c, int64_t ldc,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        host_task<class mkl_kernel_cher2k_usm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            ::cher2k((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                     (const MKL_INT *)&k, (const MKL_Complex8 *)&alpha_, a, (const MKL_INT *)&lda,
                     b, (const MKL_INT *)&ldb, (const float *)&beta, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event her2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n,
                      int64_t k, std::complex<double> alpha, const std::complex<double> *a,
                      int64_t lda, const std::complex<double> *b, int64_t ldb, double beta,
                      std::complex<double> *c, int64_t ldc,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        host_task<class mkl_kernel_zher2k_usm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            ::zher2k((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                     (const MKL_INT *)&k, (const MKL_Complex16 *)&alpha_, a, (const MKL_INT *)&lda,
                     b, (const MKL_INT *)&ldb, (const double *)&beta, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m,
                     int64_t n, float alpha, const float *a, int64_t lda, const float *b,
                     int64_t ldb, float beta, float *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        host_task<class mkl_kernel_ssymm_usm>(cgh, [=]() {
            ::ssymm((const char *)&left_right_, (const char *)&upper_lower_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const float *)&alpha, a, (const MKL_INT *)&lda, b,
                    (const MKL_INT *)&ldb, (const float *)&beta, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m,
                     int64_t n, double alpha, const double *a, int64_t lda, const double *b,
                     int64_t ldb, double beta, double *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        host_task<class mkl_kernel_dsymm_usm>(cgh, [=]() {
            ::dsymm((const char *)&left_right_, (const char *)&upper_lower_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const double *)&alpha, a, (const MKL_INT *)&lda, b,
                    (const MKL_INT *)&ldb, (const double *)&beta, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m,
                     int64_t n, std::complex<float> alpha, const std::complex<float> *a,
                     int64_t lda, const std::complex<float> *b, int64_t ldb,
                     std::complex<float> beta, std::complex<float> *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        float beta_real = beta.real(), beta_imag = beta.imag();
        host_task<class mkl_kernel_csymm_usm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex8 beta_ = { beta_real, beta_imag };
            ::csymm((const char *)&left_right_, (const char *)&upper_lower_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_Complex8 *)&alpha_, a, (const MKL_INT *)&lda, b,
                    (const MKL_INT *)&ldb, (const MKL_Complex8 *)&beta_, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event symm(cl::sycl::queue &queue, side left_right, uplo upper_lower, int64_t m,
                     int64_t n, std::complex<double> alpha, const std::complex<double> *a,
                     int64_t lda, const std::complex<double> *b, int64_t ldb,
                     std::complex<double> beta, std::complex<double> *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        double beta_real = beta.real(), beta_imag = beta.imag();
        host_task<class mkl_kernel_zsymm_usm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex16 beta_ = { beta_real, beta_imag };
            ::zsymm((const char *)&left_right_, (const char *)&upper_lower_, (const MKL_INT *)&m,
                    (const MKL_INT *)&n, (const MKL_Complex16 *)&alpha_, a, (const MKL_INT *)&lda,
                    b, (const MKL_INT *)&ldb, (const MKL_Complex16 *)&beta_, c,
                    (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n,
                     int64_t k, float alpha, const float *a, int64_t lda, float beta, float *c,
                     int64_t ldc, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        host_task<class mkl_kernel_ssyrk_usm>(cgh, [=]() {
            ::ssyrk((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                    (const MKL_INT *)&k, (const float *)&alpha, a, (const MKL_INT *)&lda,
                    (const float *)&beta, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n,
                     int64_t k, double alpha, const double *a, int64_t lda, double beta, double *c,
                     int64_t ldc, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        host_task<class mkl_kernel_dsyrk_usm>(cgh, [=]() {
            ::dsyrk((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                    (const MKL_INT *)&k, (const double *)&alpha, a, (const MKL_INT *)&lda,
                    (const double *)&beta, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n,
                     int64_t k, std::complex<float> alpha, const std::complex<float> *a,
                     int64_t lda, std::complex<float> beta, std::complex<float> *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        float beta_real = beta.real(), beta_imag = beta.imag();
        host_task<class mkl_kernel_csyrk_usm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex8 beta_ = { beta_real, beta_imag };
            ::csyrk((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                    (const MKL_INT *)&k, (const MKL_Complex8 *)&alpha_, a, (const MKL_INT *)&lda,
                    (const MKL_Complex8 *)&beta_, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event syrk(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n,
                     int64_t k, std::complex<double> alpha, const std::complex<double> *a,
                     int64_t lda, std::complex<double> beta, std::complex<double> *c, int64_t ldc,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        double beta_real = beta.real(), beta_imag = beta.imag();
        host_task<class mkl_kernel_zsyrk_usm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex16 beta_ = { beta_real, beta_imag };
            ::zsyrk((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                    (const MKL_INT *)&k, (const MKL_Complex16 *)&alpha_, a, (const MKL_INT *)&lda,
                    (const MKL_Complex16 *)&beta_, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n,
                      int64_t k, float alpha, const float *a, int64_t lda, const float *b,
                      int64_t ldb, float beta, float *c, int64_t ldc,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        host_task<class mkl_kernel_ssyr2k_usm>(cgh, [=]() {
            ::ssyr2k((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                     (const MKL_INT *)&k, (const float *)&alpha, a, (const MKL_INT *)&lda, b,
                     (const MKL_INT *)&ldb, (const float *)&beta, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n,
                      int64_t k, double alpha, const double *a, int64_t lda, const double *b,
                      int64_t ldb, double beta, double *c, int64_t ldc,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        host_task<class mkl_kernel_dsyr2k_usm>(cgh, [=]() {
            ::dsyr2k((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                     (const MKL_INT *)&k, (const double *)&alpha, a, (const MKL_INT *)&lda, b,
                     (const MKL_INT *)&ldb, (const double *)&beta, c, (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n,
                      int64_t k, std::complex<float> alpha, const std::complex<float> *a,
                      int64_t lda, const std::complex<float> *b, int64_t ldb,
                      std::complex<float> beta, std::complex<float> *c, int64_t ldc,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        float beta_real = beta.real(), beta_imag = beta.imag();
        host_task<class mkl_kernel_csyr2k_usm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex8 beta_ = { beta_real, beta_imag };
            ::csyr2k((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                     (const MKL_INT *)&k, (const MKL_Complex8 *)&alpha_, a, (const MKL_INT *)&lda,
                     b, (const MKL_INT *)&ldb, (const MKL_Complex8 *)&beta_, c,
                     (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event syr2k(cl::sycl::queue &queue, uplo upper_lower, transpose trans, int64_t n,
                      int64_t k, std::complex<double> alpha, const std::complex<double> *a,
                      int64_t lda, const std::complex<double> *b, int64_t ldb,
                      std::complex<double> beta, std::complex<double> *c, int64_t ldc,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char upper_lower_ = *fortran_char(upper_lower);
        const char trans_ = *fortran_char(trans);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        double beta_real = beta.real(), beta_imag = beta.imag();
        host_task<class mkl_kernel_zsyr2k_usm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            MKL_Complex16 beta_ = { beta_real, beta_imag };
            ::zsyr2k((const char *)&upper_lower_, (const char *)&trans_, (const MKL_INT *)&n,
                     (const MKL_INT *)&k, (const MKL_Complex16 *)&alpha_, a, (const MKL_INT *)&lda,
                     b, (const MKL_INT *)&ldb, (const MKL_Complex16 *)&beta_, c,
                     (const MKL_INT *)&ldc);
        });
    });
    return done;
}

cl::sycl::event trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
                     diag unit_diag, int64_t m, int64_t n, float alpha, const float *a, int64_t lda,
                     float *b, int64_t ldb,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        host_task<class mkl_kernel_strmm_usm>(cgh, [=]() {
            ::strmm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const float *)&alpha, a, (const MKL_INT *)&lda, b, (const MKL_INT *)&ldb);
        });
    });
    return done;
}

cl::sycl::event trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
                     diag unit_diag, int64_t m, int64_t n, double alpha, const double *a,
                     int64_t lda, double *b, int64_t ldb,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        host_task<class mkl_kernel_dtrmm_usm>(cgh, [=]() {
            ::dtrmm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const double *)&alpha, a, (const MKL_INT *)&lda, b, (const MKL_INT *)&ldb);
        });
    });
    return done;
}

cl::sycl::event trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
                     diag unit_diag, int64_t m, int64_t n, std::complex<float> alpha,
                     const std::complex<float> *a, int64_t lda, std::complex<float> *b, int64_t ldb,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        host_task<class mkl_kernel_ctrmm_usm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            ::ctrmm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const MKL_Complex8 *)&alpha_, a, (const MKL_INT *)&lda, b,
                    (const MKL_INT *)&ldb);
        });
    });
    return done;
}

cl::sycl::event trmm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
                     diag unit_diag, int64_t m, int64_t n, std::complex<double> alpha,
                     const std::complex<double> *a, int64_t lda, std::complex<double> *b,
                     int64_t ldb, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        host_task<class mkl_kernel_ztrmm_usm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            ::ztrmm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const MKL_Complex16 *)&alpha_, a, (const MKL_INT *)&lda, b,
                    (const MKL_INT *)&ldb);
        });
    });
    return done;
}

cl::sycl::event trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
                     diag unit_diag, int64_t m, int64_t n, float alpha, const float *a, int64_t lda,
                     float *b, int64_t ldb,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        host_task<class mkl_kernel_strsm_usm>(cgh, [=]() {
            ::strsm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const float *)&alpha, a, (const MKL_INT *)&lda, b, (const MKL_INT *)&ldb);
        });
    });
    return done;
}

cl::sycl::event trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
                     diag unit_diag, int64_t m, int64_t n, double alpha, const double *a,
                     int64_t lda, double *b, int64_t ldb,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        host_task<class mkl_kernel_dtrsm_usm>(cgh, [=]() {
            ::dtrsm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const double *)&alpha, a, (const MKL_INT *)&lda, b, (const MKL_INT *)&ldb);
        });
    });
    return done;
}

cl::sycl::event trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
                     diag unit_diag, int64_t m, int64_t n, std::complex<float> alpha,
                     const std::complex<float> *a, int64_t lda, std::complex<float> *b, int64_t ldb,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        host_task<class mkl_kernel_ctrsm_usm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            ::ctrsm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const MKL_Complex8 *)&alpha_, a, (const MKL_INT *)&lda, b,
                    (const MKL_INT *)&ldb);
        });
    });
    return done;
}

cl::sycl::event trsm(cl::sycl::queue &queue, side left_right, uplo upper_lower, transpose transa,
                     diag unit_diag, int64_t m, int64_t n, std::complex<double> alpha,
                     const std::complex<double> *a, int64_t lda, std::complex<double> *b,
                     int64_t ldb, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        const char left_right_ = *fortran_char(left_right);
        const char upper_lower_ = *fortran_char(upper_lower);
        const char transa_ = *fortran_char(transa);
        const char unit_diag_ = *fortran_char(unit_diag);
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        host_task<class mkl_kernel_ztrsm_usm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            ::ztrsm((const char *)&left_right_, (const char *)&upper_lower_, (const char *)&transa_,
                    (const char *)&unit_diag_, (const MKL_INT *)&m, (const MKL_INT *)&n,
                    (const MKL_Complex16 *)&alpha_, a, (const MKL_INT *)&lda, b,
                    (const MKL_INT *)&ldb);
        });
    });
    return done;
}

} // namespace mklcpu
} // namespace mkl
} // namespace oneapi
