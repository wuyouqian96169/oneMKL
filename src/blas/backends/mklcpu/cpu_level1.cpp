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

void asum(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<float, 1> &x, int64_t incx,
          cl::sycl::buffer<float, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_sasum>(cgh, [=]() {
            accessor_result[0] =
                ::sasum((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx);
        });
    });
}

void asum(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<double, 1> &x, int64_t incx,
          cl::sycl::buffer<double, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_dasum>(cgh, [=]() {
            accessor_result[0] =
                ::dasum((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx);
        });
    });
}

void asum(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<float>, 1> &x,
          int64_t incx, cl::sycl::buffer<float, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_scasum>(cgh, [=]() {
            accessor_result[0] =
                ::scasum((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx);
        });
    });
}

void asum(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<double>, 1> &x,
          int64_t incx, cl::sycl::buffer<double, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_dzasum>(cgh, [=]() {
            accessor_result[0] =
                ::dzasum((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx);
        });
    });
}

void axpy(cl::sycl::queue &queue, int64_t n, float alpha, cl::sycl::buffer<float, 1> &x,
          int64_t incx, cl::sycl::buffer<float, 1> &y, int64_t incy) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_saxpy>(cgh, [=]() {
            ::saxpy((const MKL_INT *)&n, (const float *)&alpha, accessor_x.get_pointer(),
                    (const MKL_INT *)&incx, accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void axpy(cl::sycl::queue &queue, int64_t n, double alpha, cl::sycl::buffer<double, 1> &x,
          int64_t incx, cl::sycl::buffer<double, 1> &y, int64_t incy) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_daxpy>(cgh, [=]() {
            ::daxpy((const MKL_INT *)&n, (const double *)&alpha, accessor_x.get_pointer(),
                    (const MKL_INT *)&incx, accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void axpy(cl::sycl::queue &queue, int64_t n, std::complex<float> alpha,
          cl::sycl::buffer<std::complex<float>, 1> &x, int64_t incx,
          cl::sycl::buffer<std::complex<float>, 1> &y, int64_t incy) {
    queue.submit([&](cl::sycl::handler &cgh) {
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_caxpy>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            ::caxpy((const MKL_INT *)&n, (const MKL_Complex8 *)&alpha_, accessor_x.get_pointer(),
                    (const MKL_INT *)&incx, accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void axpy(cl::sycl::queue &queue, int64_t n, std::complex<double> alpha,
          cl::sycl::buffer<std::complex<double>, 1> &x, int64_t incx,
          cl::sycl::buffer<std::complex<double>, 1> &y, int64_t incy) {
    queue.submit([&](cl::sycl::handler &cgh) {
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zaxpy>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            ::zaxpy((const MKL_INT *)&n, (const MKL_Complex16 *)&alpha_, accessor_x.get_pointer(),
                    (const MKL_INT *)&incx, accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void copy(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<float, 1> &x, int64_t incx,
          cl::sycl::buffer<float, 1> &y, int64_t incy) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_scopy>(cgh, [=]() {
            ::scopy((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                    accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void copy(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<double, 1> &x, int64_t incx,
          cl::sycl::buffer<double, 1> &y, int64_t incy) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_dcopy>(cgh, [=]() {
            ::dcopy((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                    accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void copy(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<float>, 1> &x,
          int64_t incx, cl::sycl::buffer<std::complex<float>, 1> &y, int64_t incy) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_ccopy>(cgh, [=]() {
            ::ccopy((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                    accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void copy(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<double>, 1> &x,
          int64_t incx, cl::sycl::buffer<std::complex<double>, 1> &y, int64_t incy) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zcopy>(cgh, [=]() {
            ::zcopy((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                    accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void dot(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<float, 1> &x, int64_t incx,
         cl::sycl::buffer<float, 1> &y, int64_t incy, cl::sycl::buffer<float, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_sdot>(cgh, [=]() {
            accessor_result[0] =
                ::sdot((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                       accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void dot(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<double, 1> &x, int64_t incx,
         cl::sycl::buffer<double, 1> &y, int64_t incy, cl::sycl::buffer<double, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_ddot>(cgh, [=]() {
            accessor_result[0] =
                ::ddot((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                       accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void dot(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<float, 1> &x, int64_t incx,
         cl::sycl::buffer<float, 1> &y, int64_t incy, cl::sycl::buffer<double, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_dsdot>(cgh, [=]() {
            accessor_result[0] =
                ::dsdot((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                        accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void dotc(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<float>, 1> &x,
          int64_t incx, cl::sycl::buffer<std::complex<float>, 1> &y, int64_t incy,
          cl::sycl::buffer<std::complex<float>, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_cdotc>(cgh, [=]() {
            ::cdotc(accessor_result.get_pointer(), (const MKL_INT *)&n, accessor_x.get_pointer(),
                    (const MKL_INT *)&incx, accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void dotc(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<double>, 1> &x,
          int64_t incx, cl::sycl::buffer<std::complex<double>, 1> &y, int64_t incy,
          cl::sycl::buffer<std::complex<double>, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zdotc>(cgh, [=]() {
            ::zdotc(accessor_result.get_pointer(), (const MKL_INT *)&n, accessor_x.get_pointer(),
                    (const MKL_INT *)&incx, accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void dotu(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<float>, 1> &x,
          int64_t incx, cl::sycl::buffer<std::complex<float>, 1> &y, int64_t incy,
          cl::sycl::buffer<std::complex<float>, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_cdotu>(cgh, [=]() {
            ::cdotu(accessor_result.get_pointer(), (const MKL_INT *)&n, accessor_x.get_pointer(),
                    (const MKL_INT *)&incx, accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void dotu(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<double>, 1> &x,
          int64_t incx, cl::sycl::buffer<std::complex<double>, 1> &y, int64_t incy,
          cl::sycl::buffer<std::complex<double>, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zdotu>(cgh, [=]() {
            ::zdotu(accessor_result.get_pointer(), (const MKL_INT *)&n, accessor_x.get_pointer(),
                    (const MKL_INT *)&incx, accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void iamin(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<float, 1> &x, int64_t incx,
           cl::sycl::buffer<int64_t, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_isamin>(cgh, [=]() {
            accessor_result[0] =
                ::cblas_isamin((MKL_INT)n, accessor_x.get_pointer(), (MKL_INT)incx);
        });
    });
}

void iamin(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<double, 1> &x, int64_t incx,
           cl::sycl::buffer<int64_t, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.template get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.template get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_idamin>(cgh, [=]() {
            accessor_result[0] =
                ::cblas_idamin((const MKL_INT)n, accessor_x.get_pointer(), (const MKL_INT)incx);
        });
    });
}

void iamin(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<float>, 1> &x,
           int64_t incx, cl::sycl::buffer<int64_t, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_icamin>(cgh, [=]() {
            accessor_result[0] =
                ::cblas_icamin((MKL_INT)n, accessor_x.get_pointer(), (MKL_INT)incx);
        });
    });
}

void iamin(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<double>, 1> &x,
           int64_t incx, cl::sycl::buffer<int64_t, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_izamin>(cgh, [=]() {
            accessor_result[0] =
                ::cblas_izamin((MKL_INT)n, accessor_x.get_pointer(), (MKL_INT)incx);
        });
    });
}

void iamax(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<float, 1> &x, int64_t incx,
           cl::sycl::buffer<int64_t, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_isamax>(cgh, [=]() {
            accessor_result[0] =
                ::cblas_isamax((MKL_INT)n, accessor_x.get_pointer(), (MKL_INT)incx);
        });
    });
}

void iamax(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<double, 1> &x, int64_t incx,
           cl::sycl::buffer<int64_t, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_idamax>(cgh, [=]() {
            accessor_result[0] =
                ::cblas_idamax((MKL_INT)n, accessor_x.get_pointer(), (MKL_INT)incx);
        });
    });
}

void iamax(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<float>, 1> &x,
           int64_t incx, cl::sycl::buffer<int64_t, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_icamax>(cgh, [=]() {
            accessor_result[0] =
                ::cblas_icamax((MKL_INT)n, accessor_x.get_pointer(), (MKL_INT)incx);
        });
    });
}

void iamax(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<double>, 1> &x,
           int64_t incx, cl::sycl::buffer<int64_t, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_izamax>(cgh, [=]() {
            accessor_result[0] =
                ::cblas_izamax((MKL_INT)n, accessor_x.get_pointer(), (MKL_INT)incx);
        });
    });
}

void nrm2(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<float, 1> &x, int64_t incx,
          cl::sycl::buffer<float, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.template get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.template get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_snrm2>(cgh, [=]() {
            accessor_result[0] =
                ::snrm2((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx);
        });
    });
}

void nrm2(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<double, 1> &x, int64_t incx,
          cl::sycl::buffer<double, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_dnrm2>(cgh, [=]() {
            accessor_result[0] =
                ::dnrm2((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx);
        });
    });
}

void nrm2(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<float>, 1> &x,
          int64_t incx, cl::sycl::buffer<float, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_scnrm2>(cgh, [=]() {
            accessor_result[0] =
                ::scnrm2((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx);
        });
    });
}

void nrm2(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<double>, 1> &x,
          int64_t incx, cl::sycl::buffer<double, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_dznrm2>(cgh, [=]() {
            accessor_result[0] =
                ::dznrm2((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx);
        });
    });
}

void rot(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<float, 1> &x, int64_t incx,
         cl::sycl::buffer<float, 1> &y, int64_t incy, float c, float s) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_srot>(cgh, [=]() {
            ::srot((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                   accessor_y.get_pointer(), (const MKL_INT *)&incy, &c, &s);
        });
    });
}

void rot(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<double, 1> &x, int64_t incx,
         cl::sycl::buffer<double, 1> &y, int64_t incy, double c, double s) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_drot>(cgh, [=]() {
            ::drot((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                   accessor_y.get_pointer(), (const MKL_INT *)&incy, &c, &s);
        });
    });
}

void rot(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<float>, 1> &x,
         int64_t incx, cl::sycl::buffer<std::complex<float>, 1> &y, int64_t incy, float c,
         float s) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_csrot>(cgh, [=]() {
            ::csrot((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                    accessor_y.get_pointer(), (const MKL_INT *)&incy, &c, &s);
        });
    });
}

void rot(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<double>, 1> &x,
         int64_t incx, cl::sycl::buffer<std::complex<double>, 1> &y, int64_t incy, double c,
         double s) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zdrot>(cgh, [=]() {
            ::zdrot((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                    accessor_y.get_pointer(), (const MKL_INT *)&incy, &c, &s);
        });
    });
}

void rotg(cl::sycl::queue &queue, cl::sycl::buffer<float, 1> &a, cl::sycl::buffer<float, 1> &b,
          cl::sycl::buffer<float, 1> &c, cl::sycl::buffer<float, 1> &s) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_a = a.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_s = s.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_srotg>(cgh, [=]() {
            ::srotg(accessor_a.get_pointer(), accessor_b.get_pointer(), accessor_c.get_pointer(),
                    accessor_s.get_pointer());
        });
    });
}

void rotg(cl::sycl::queue &queue, cl::sycl::buffer<double, 1> &a, cl::sycl::buffer<double, 1> &b,
          cl::sycl::buffer<double, 1> &c, cl::sycl::buffer<double, 1> &s) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_a = a.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_s = s.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_drotg>(cgh, [=]() {
            ::drotg(accessor_a.get_pointer(), accessor_b.get_pointer(), accessor_c.get_pointer(),
                    accessor_s.get_pointer());
        });
    });
}

void rotg(cl::sycl::queue &queue, cl::sycl::buffer<std::complex<float>, 1> &a,
          cl::sycl::buffer<std::complex<float>, 1> &b, cl::sycl::buffer<float, 1> &c,
          cl::sycl::buffer<std::complex<float>, 1> &s) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_a = a.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_s = s.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_crotg>(cgh, [=]() {
            ::crotg(accessor_a.get_pointer(), accessor_b.get_pointer(), accessor_c.get_pointer(),
                    accessor_s.get_pointer());
        });
    });
}

void rotg(cl::sycl::queue &queue, cl::sycl::buffer<std::complex<double>, 1> &a,
          cl::sycl::buffer<std::complex<double>, 1> &b, cl::sycl::buffer<double, 1> &c,
          cl::sycl::buffer<std::complex<double>, 1> &s) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_a = a.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_b = b.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_c = c.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_s = s.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zrotg>(cgh, [=]() {
            ::zrotg(accessor_a.get_pointer(), accessor_b.get_pointer(), accessor_c.get_pointer(),
                    accessor_s.get_pointer());
        });
    });
}

void rotm(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<float, 1> &x, int64_t incx,
          cl::sycl::buffer<float, 1> &y, int64_t incy, cl::sycl::buffer<float, 1> &param) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_param = param.get_access<cl::sycl::access::mode::read>(cgh);
        host_task<class mkl_kernel_srotm>(cgh, [=]() {
            ::srotm((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                    accessor_y.get_pointer(), (const MKL_INT *)&incy, accessor_param.get_pointer());
        });
    });
}

void rotm(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<double, 1> &x, int64_t incx,
          cl::sycl::buffer<double, 1> &y, int64_t incy, cl::sycl::buffer<double, 1> &param) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_param = param.get_access<cl::sycl::access::mode::read>(cgh);
        host_task<class mkl_kernel_drotm>(cgh, [=]() {
            ::drotm((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                    accessor_y.get_pointer(), (const MKL_INT *)&incy, accessor_param.get_pointer());
        });
    });
}

void rotmg(cl::sycl::queue &queue, cl::sycl::buffer<float, 1> &d1, cl::sycl::buffer<float, 1> &d2,
           cl::sycl::buffer<float, 1> &x1, float y1, cl::sycl::buffer<float, 1> &param) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_d1 = d1.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_d2 = d2.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_x1 = x1.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_param = param.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_srotmg>(cgh, [=]() {
            ::srotmg(accessor_d1.get_pointer(), accessor_d2.get_pointer(),
                     accessor_x1.get_pointer(), (float *)&y1, accessor_param.get_pointer());
        });
    });
}

void rotmg(cl::sycl::queue &queue, cl::sycl::buffer<double, 1> &d1, cl::sycl::buffer<double, 1> &d2,
           cl::sycl::buffer<double, 1> &x1, double y1, cl::sycl::buffer<double, 1> &param) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_d1 = d1.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_d2 = d2.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_x1 = x1.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_param = param.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_drotmg>(cgh, [=]() {
            ::drotmg(accessor_d1.get_pointer(), accessor_d2.get_pointer(),
                     accessor_x1.get_pointer(), (double *)&y1, accessor_param.get_pointer());
        });
    });
}

void scal(cl::sycl::queue &queue, int64_t n, float alpha, cl::sycl::buffer<float, 1> &x,
          int64_t incx) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_sscal>(cgh, [=]() {
            ::sscal((const MKL_INT *)&n, (const float *)&alpha, accessor_x.get_pointer(),
                    (const MKL_INT *)&incx);
        });
    });
}

void scal(cl::sycl::queue &queue, int64_t n, double alpha, cl::sycl::buffer<double, 1> &x,
          int64_t incx) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_dscal>(cgh, [=]() {
            ::dscal((const MKL_INT *)&n, (const double *)&alpha, accessor_x.get_pointer(),
                    (const MKL_INT *)&incx);
        });
    });
}

void scal(cl::sycl::queue &queue, int64_t n, std::complex<float> alpha,
          cl::sycl::buffer<std::complex<float>, 1> &x, int64_t incx) {
    queue.submit([&](cl::sycl::handler &cgh) {
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_cscal>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            ::cscal((const MKL_INT *)&n, (const MKL_Complex8 *)&alpha_, accessor_x.get_pointer(),
                    (const MKL_INT *)&incx);
        });
    });
}

void scal(cl::sycl::queue &queue, int64_t n, float alpha,
          cl::sycl::buffer<std::complex<float>, 1> &x, int64_t incx) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_csscal>(cgh, [=]() {
            ::csscal((const MKL_INT *)&n, (const float *)&alpha, accessor_x.get_pointer(),
                     (const MKL_INT *)&incx);
        });
    });
}

void scal(cl::sycl::queue &queue, int64_t n, std::complex<double> alpha,
          cl::sycl::buffer<std::complex<double>, 1> &x, int64_t incx) {
    queue.submit([&](cl::sycl::handler &cgh) {
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zscal>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            ::zscal((const MKL_INT *)&n, (const MKL_Complex16 *)&alpha_, accessor_x.get_pointer(),
                    (const MKL_INT *)&incx);
        });
    });
}

void scal(cl::sycl::queue &queue, int64_t n, double alpha,
          cl::sycl::buffer<std::complex<double>, 1> &x, int64_t incx) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zdscal>(cgh, [=]() {
            ::zdscal((const MKL_INT *)&n, (const double *)&alpha, accessor_x.get_pointer(),
                     (const MKL_INT *)&incx);
        });
    });
}

void sdsdot(cl::sycl::queue &queue, int64_t n, float sb, cl::sycl::buffer<float, 1> &x,
            int64_t incx, cl::sycl::buffer<float, 1> &y, int64_t incy,
            cl::sycl::buffer<float, 1> &result) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read>(cgh);
        auto accessor_result = result.get_access<cl::sycl::access::mode::write>(cgh);
        host_task<class mkl_kernel_sdsdot>(cgh, [=]() {
            accessor_result[0] =
                ::sdsdot((const MKL_INT *)&n, (const float *)&sb, accessor_x.get_pointer(),
                         (const MKL_INT *)&incx, accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void swap(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<float, 1> &x, int64_t incx,
          cl::sycl::buffer<float, 1> &y, int64_t incy) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_sswap>(cgh, [=]() {
            ::sswap((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                    accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void swap(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<double, 1> &x, int64_t incx,
          cl::sycl::buffer<double, 1> &y, int64_t incy) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_dswap>(cgh, [=]() {
            ::dswap((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                    accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void swap(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<float>, 1> &x,
          int64_t incx, cl::sycl::buffer<std::complex<float>, 1> &y, int64_t incy) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_cswap>(cgh, [=]() {
            ::cswap((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                    accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

void swap(cl::sycl::queue &queue, int64_t n, cl::sycl::buffer<std::complex<double>, 1> &x,
          int64_t incx, cl::sycl::buffer<std::complex<double>, 1> &y, int64_t incy) {
    queue.submit([&](cl::sycl::handler &cgh) {
        auto accessor_x = x.get_access<cl::sycl::access::mode::read_write>(cgh);
        auto accessor_y = y.get_access<cl::sycl::access::mode::read_write>(cgh);
        host_task<class mkl_kernel_zswap>(cgh, [=]() {
            ::zswap((const MKL_INT *)&n, accessor_x.get_pointer(), (const MKL_INT *)&incx,
                    accessor_y.get_pointer(), (const MKL_INT *)&incy);
        });
    });
}

// USM APIs

cl::sycl::event asum(cl::sycl::queue &queue, int64_t n, const float *x, int64_t incx, float *result,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_sasum_usm>(
            cgh, [=]() { result[0] = ::sasum((const MKL_INT *)&n, x, (const MKL_INT *)&incx); });
    });
    return done;
}

cl::sycl::event asum(cl::sycl::queue &queue, int64_t n, const double *x, int64_t incx,
                     double *result, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_dasum_usm>(
            cgh, [=]() { result[0] = ::dasum((const MKL_INT *)&n, x, (const MKL_INT *)&incx); });
    });
    return done;
}

cl::sycl::event asum(cl::sycl::queue &queue, int64_t n, const std::complex<float> *x, int64_t incx,
                     float *result, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_scasum_usm>(
            cgh, [=]() { result[0] = ::scasum((const MKL_INT *)&n, x, (const MKL_INT *)&incx); });
    });
    return done;
}

cl::sycl::event asum(cl::sycl::queue &queue, int64_t n, const std::complex<double> *x, int64_t incx,
                     double *result, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_dzasum_usm>(
            cgh, [=]() { result[0] = ::dzasum((const MKL_INT *)&n, x, (const MKL_INT *)&incx); });
    });
    return done;
}

cl::sycl::event axpy(cl::sycl::queue &queue, int64_t n, float alpha, const float *x, int64_t incx,
                     float *y, int64_t incy,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_saxpy_usm>(cgh, [=]() {
            ::saxpy((const MKL_INT *)&n, (const float *)&alpha, x, (const MKL_INT *)&incx, y,
                    (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event axpy(cl::sycl::queue &queue, int64_t n, double alpha, const double *x, int64_t incx,
                     double *y, int64_t incy,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_daxpy_usm>(cgh, [=]() {
            ::daxpy((const MKL_INT *)&n, (const double *)&alpha, x, (const MKL_INT *)&incx, y,
                    (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event axpy(cl::sycl::queue &queue, int64_t n, std::complex<float> alpha,
                     const std::complex<float> *x, int64_t incx, std::complex<float> *y,
                     int64_t incy, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        host_task<class mkl_kernel_caxpy_usm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            ::caxpy((const MKL_INT *)&n, (const MKL_Complex8 *)&alpha_, x, (const MKL_INT *)&incx,
                    y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event axpy(cl::sycl::queue &queue, int64_t n, std::complex<double> alpha,
                     const std::complex<double> *x, int64_t incx, std::complex<double> *y,
                     int64_t incy, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        host_task<class mkl_kernel_zaxpy_usm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            ::zaxpy((const MKL_INT *)&n, (const MKL_Complex16 *)&alpha_, x, (const MKL_INT *)&incx,
                    y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event copy(cl::sycl::queue &queue, int64_t n, const float *x, int64_t incx, float *y,
                     int64_t incy, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_scopy_usm>(cgh, [=]() {
            ::scopy((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event copy(cl::sycl::queue &queue, int64_t n, const double *x, int64_t incx, double *y,
                     int64_t incy, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_dcopy_usm>(cgh, [=]() {
            ::dcopy((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event copy(cl::sycl::queue &queue, int64_t n, const std::complex<float> *x, int64_t incx,
                     std::complex<float> *y, int64_t incy,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_ccopy_usm>(cgh, [=]() {
            ::ccopy((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event copy(cl::sycl::queue &queue, int64_t n, const std::complex<double> *x, int64_t incx,
                     std::complex<double> *y, int64_t incy,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_zcopy_usm>(cgh, [=]() {
            ::zcopy((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event dot(cl::sycl::queue &queue, int64_t n, const float *x, int64_t incx, const float *y,
                    int64_t incy, float *result,
                    const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_sdot_usm>(cgh, [=]() {
            result[0] =
                ::sdot((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event dot(cl::sycl::queue &queue, int64_t n, const double *x, int64_t incx,
                    const double *y, int64_t incy, double *result,
                    const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_ddot_usm>(cgh, [=]() {
            result[0] =
                ::ddot((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event dot(cl::sycl::queue &queue, int64_t n, const float *x, int64_t incx, const float *y,
                    int64_t incy, double *result,
                    const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_dsdot_usm>(cgh, [=]() {
            result[0] =
                ::dsdot((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event dotc(cl::sycl::queue &queue, int64_t n, const std::complex<float> *x, int64_t incx,
                     const std::complex<float> *y, int64_t incy, std::complex<float> *result,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_cdotc_usm>(cgh, [=]() {
            ::cdotc(result, (const MKL_INT *)&n, x, (const MKL_INT *)&incx, y,
                    (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event dotc(cl::sycl::queue &queue, int64_t n, const std::complex<double> *x, int64_t incx,
                     const std::complex<double> *y, int64_t incy, std::complex<double> *result,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_zdotc_usm>(cgh, [=]() {
            ::zdotc(result, (const MKL_INT *)&n, x, (const MKL_INT *)&incx, y,
                    (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event dotu(cl::sycl::queue &queue, int64_t n, const std::complex<float> *x, int64_t incx,
                     const std::complex<float> *y, int64_t incy, std::complex<float> *result,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_cdotu_usm>(cgh, [=]() {
            ::cdotu(result, (const MKL_INT *)&n, x, (const MKL_INT *)&incx, y,
                    (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event dotu(cl::sycl::queue &queue, int64_t n, const std::complex<double> *x, int64_t incx,
                     const std::complex<double> *y, int64_t incy, std::complex<double> *result,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_zdotu_usm>(cgh, [=]() {
            ::zdotu(result, (const MKL_INT *)&n, x, (const MKL_INT *)&incx, y,
                    (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event iamin(cl::sycl::queue &queue, int64_t n, const float *x, int64_t incx,
                      int64_t *result,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_isamin_usm>(
            cgh, [=]() { result[0] = ::cblas_isamin((MKL_INT)n, x, (MKL_INT)incx); });
    });
    return done;
}

cl::sycl::event iamin(cl::sycl::queue &queue, int64_t n, const double *x, int64_t incx,
                      int64_t *result,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_idamin_usm>(
            cgh, [=]() { result[0] = ::cblas_idamin((const MKL_INT)n, x, (const MKL_INT)incx); });
    });
    return done;
}

cl::sycl::event iamin(cl::sycl::queue &queue, int64_t n, const std::complex<float> *x, int64_t incx,
                      int64_t *result,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_icamin_usm>(
            cgh, [=]() { result[0] = ::cblas_icamin((MKL_INT)n, x, (MKL_INT)incx); });
    });
    return done;
}

cl::sycl::event iamin(cl::sycl::queue &queue, int64_t n, const std::complex<double> *x,
                      int64_t incx, int64_t *result,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_izamin_usm>(
            cgh, [=]() { result[0] = ::cblas_izamin((MKL_INT)n, x, (MKL_INT)incx); });
    });
    return done;
}

cl::sycl::event iamax(cl::sycl::queue &queue, int64_t n, const float *x, int64_t incx,
                      int64_t *result,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_isamax_usm>(
            cgh, [=]() { result[0] = ::cblas_isamax((MKL_INT)n, x, (MKL_INT)incx); });
    });
    return done;
}

cl::sycl::event iamax(cl::sycl::queue &queue, int64_t n, const double *x, int64_t incx,
                      int64_t *result,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_idamax_usm>(
            cgh, [=]() { result[0] = ::cblas_idamax((MKL_INT)n, x, (MKL_INT)incx); });
    });
    return done;
}

cl::sycl::event iamax(cl::sycl::queue &queue, int64_t n, const std::complex<float> *x, int64_t incx,
                      int64_t *result,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_icamax_usm>(
            cgh, [=]() { result[0] = ::cblas_icamax((MKL_INT)n, x, (MKL_INT)incx); });
    });
    return done;
}

cl::sycl::event iamax(cl::sycl::queue &queue, int64_t n, const std::complex<double> *x,
                      int64_t incx, int64_t *result,
                      const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_izamax_usm>(
            cgh, [=]() { result[0] = ::cblas_izamax((MKL_INT)n, x, (MKL_INT)incx); });
    });
    return done;
}

cl::sycl::event nrm2(cl::sycl::queue &queue, int64_t n, const float *x, int64_t incx, float *result,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_snrm2_usm>(
            cgh, [=]() { result[0] = ::snrm2((const MKL_INT *)&n, x, (const MKL_INT *)&incx); });
    });
    return done;
}

cl::sycl::event nrm2(cl::sycl::queue &queue, int64_t n, const double *x, int64_t incx,
                     double *result, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_dnrm2_usm>(
            cgh, [=]() { result[0] = ::dnrm2((const MKL_INT *)&n, x, (const MKL_INT *)&incx); });
    });
    return done;
}

cl::sycl::event nrm2(cl::sycl::queue &queue, int64_t n, const std::complex<float> *x, int64_t incx,
                     float *result, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_scnrm2_usm>(
            cgh, [=]() { result[0] = ::scnrm2((const MKL_INT *)&n, x, (const MKL_INT *)&incx); });
    });
    return done;
}

cl::sycl::event nrm2(cl::sycl::queue &queue, int64_t n, const std::complex<double> *x, int64_t incx,
                     double *result, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_dznrm2_usm>(
            cgh, [=]() { result[0] = ::dznrm2((const MKL_INT *)&n, x, (const MKL_INT *)&incx); });
    });
    return done;
}

cl::sycl::event rot(cl::sycl::queue &queue, int64_t n, float *x, int64_t incx, float *y,
                    int64_t incy, float c, float s,
                    const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_srot_usm>(cgh, [=]() {
            ::srot((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy, &c,
                   &s);
        });
    });
    return done;
}

cl::sycl::event rot(cl::sycl::queue &queue, int64_t n, double *x, int64_t incx, double *y,
                    int64_t incy, double c, double s,
                    const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_drot_usm>(cgh, [=]() {
            ::drot((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy, &c,
                   &s);
        });
    });
    return done;
}

cl::sycl::event rot(cl::sycl::queue &queue, int64_t n, std::complex<float> *x, int64_t incx,
                    std::complex<float> *y, int64_t incy, float c, float s,
                    const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_csrot_usm>(cgh, [=]() {
            ::csrot((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy, &c,
                    &s);
        });
    });
    return done;
}

cl::sycl::event rot(cl::sycl::queue &queue, int64_t n, std::complex<double> *x, int64_t incx,
                    std::complex<double> *y, int64_t incy, double c, double s,
                    const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_zdrot_usm>(cgh, [=]() {
            ::zdrot((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy, &c,
                    &s);
        });
    });
    return done;
}

cl::sycl::event rotg(cl::sycl::queue &queue, float *a, float *b, float *c, float *s,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_srotg_usm>(cgh, [=]() { ::srotg(a, b, c, s); });
    });
    return done;
}

cl::sycl::event rotg(cl::sycl::queue &queue, double *a, double *b, double *c, double *s,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_drotg_usm>(cgh, [=]() { ::drotg(a, b, c, s); });
    });
    return done;
}

cl::sycl::event rotg(cl::sycl::queue &queue, std::complex<float> *a, std::complex<float> *b,
                     float *c, std::complex<float> *s,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_crotg_usm>(cgh, [=]() { ::crotg(a, b, c, s); });
    });
    return done;
}

cl::sycl::event rotg(cl::sycl::queue &queue, std::complex<double> *a, std::complex<double> *b,
                     double *c, std::complex<double> *s,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_zrotg_usm>(cgh, [=]() { ::zrotg(a, b, c, s); });
    });
    return done;
}

cl::sycl::event rotm(cl::sycl::queue &queue, int64_t n, float *x, int64_t incx, float *y,
                     int64_t incy, float *param,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_srotm_usm>(cgh, [=]() {
            ::srotm((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy,
                    param);
        });
    });
    return done;
}

cl::sycl::event rotm(cl::sycl::queue &queue, int64_t n, double *x, int64_t incx, double *y,
                     int64_t incy, double *param,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_drotm_usm>(cgh, [=]() {
            ::drotm((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy,
                    param);
        });
    });
    return done;
}

cl::sycl::event rotmg(cl::sycl::queue &queue, float *d1, float *d2, float *x1, float y1,
                      float *param, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_srotmg_usm>(
            cgh, [=]() { ::srotmg(d1, d2, x1, (float *)&y1, param); });
    });
    return done;
}

cl::sycl::event rotmg(cl::sycl::queue &queue, double *d1, double *d2, double *x1, double y1,
                      double *param, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_drotmg_usm>(
            cgh, [=]() { ::drotmg(d1, d2, x1, (double *)&y1, param); });
    });
    return done;
}

cl::sycl::event scal(cl::sycl::queue &queue, int64_t n, float alpha, float *x, int64_t incx,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_sscal_usm>(cgh, [=]() {
            ::sscal((const MKL_INT *)&n, (const float *)&alpha, x, (const MKL_INT *)&incx);
        });
    });
    return done;
}

cl::sycl::event scal(cl::sycl::queue &queue, int64_t n, double alpha, double *x, int64_t incx,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_dscal_usm>(cgh, [=]() {
            ::dscal((const MKL_INT *)&n, (const double *)&alpha, x, (const MKL_INT *)&incx);
        });
    });
    return done;
}

cl::sycl::event scal(cl::sycl::queue &queue, int64_t n, std::complex<float> alpha,
                     std::complex<float> *x, int64_t incx,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        float alpha_real = alpha.real(), alpha_imag = alpha.imag();
        host_task<class mkl_kernel_cscal_usm>(cgh, [=]() {
            MKL_Complex8 alpha_ = { alpha_real, alpha_imag };
            ::cscal((const MKL_INT *)&n, (const MKL_Complex8 *)&alpha_, x, (const MKL_INT *)&incx);
        });
    });
    return done;
}

cl::sycl::event scal(cl::sycl::queue &queue, int64_t n, float alpha, std::complex<float> *x,
                     int64_t incx, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_csscal_usm>(cgh, [=]() {
            ::csscal((const MKL_INT *)&n, (const float *)&alpha, x, (const MKL_INT *)&incx);
        });
    });
    return done;
}

cl::sycl::event scal(cl::sycl::queue &queue, int64_t n, std::complex<double> alpha,
                     std::complex<double> *x, int64_t incx,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        double alpha_real = alpha.real(), alpha_imag = alpha.imag();
        host_task<class mkl_kernel_zscal_usm>(cgh, [=]() {
            MKL_Complex16 alpha_ = { alpha_real, alpha_imag };
            ::zscal((const MKL_INT *)&n, (const MKL_Complex16 *)&alpha_, x, (const MKL_INT *)&incx);
        });
    });
    return done;
}

cl::sycl::event scal(cl::sycl::queue &queue, int64_t n, double alpha, std::complex<double> *x,
                     int64_t incx, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_zdscal_usm>(cgh, [=]() {
            ::zdscal((const MKL_INT *)&n, (const double *)&alpha, x, (const MKL_INT *)&incx);
        });
    });
    return done;
}

cl::sycl::event sdsdot(cl::sycl::queue &queue, int64_t n, float sb, const float *x, int64_t incx,
                       const float *y, int64_t incy, float *result,
                       const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_sdsdot_usm>(cgh, [=]() {
            result[0] = ::sdsdot((const MKL_INT *)&n, (const float *)&sb, x, (const MKL_INT *)&incx,
                                 y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event swap(cl::sycl::queue &queue, int64_t n, float *x, int64_t incx, float *y,
                     int64_t incy, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_sswap_usm>(cgh, [=]() {
            ::sswap((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event swap(cl::sycl::queue &queue, int64_t n, double *x, int64_t incx, double *y,
                     int64_t incy, const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_dswap_usm>(cgh, [=]() {
            ::dswap((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event swap(cl::sycl::queue &queue, int64_t n, std::complex<float> *x, int64_t incx,
                     std::complex<float> *y, int64_t incy,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_cswap_usm>(cgh, [=]() {
            ::cswap((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

cl::sycl::event swap(cl::sycl::queue &queue, int64_t n, std::complex<double> *x, int64_t incx,
                     std::complex<double> *y, int64_t incy,
                     const cl::sycl::vector_class<cl::sycl::event> &dependencies) {
    auto done = queue.submit([&](cl::sycl::handler &cgh) {
        int64_t num_events = dependencies.size();
        for (int64_t i = 0; i < num_events; i++) {
            cgh.depends_on(dependencies[i]);
        }
        host_task<class mkl_kernel_zswap_usm>(cgh, [=]() {
            ::zswap((const MKL_INT *)&n, x, (const MKL_INT *)&incx, y, (const MKL_INT *)&incy);
        });
    });
    return done;
}

} // namespace mklcpu
} // namespace mkl
} // namespace oneapi
