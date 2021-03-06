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

#include "blas/function_table.hpp"
#include "oneapi/mkl/blas/detail/mklgpu/onemkl_blas_mklgpu.hpp"

#define WRAPPER_VERSION 1

extern "C" ONEMKL_EXPORT function_table_t mkl_blas_table = {
    WRAPPER_VERSION,
    oneapi::mkl::mklgpu::asum,
    oneapi::mkl::mklgpu::asum,
    oneapi::mkl::mklgpu::asum,
    oneapi::mkl::mklgpu::asum,
    oneapi::mkl::mklgpu::axpy,
    oneapi::mkl::mklgpu::axpy,
    oneapi::mkl::mklgpu::axpy,
    oneapi::mkl::mklgpu::axpy,
    oneapi::mkl::mklgpu::copy,
    oneapi::mkl::mklgpu::copy,
    oneapi::mkl::mklgpu::copy,
    oneapi::mkl::mklgpu::copy,
    oneapi::mkl::mklgpu::dot,
    oneapi::mkl::mklgpu::dot,
    oneapi::mkl::mklgpu::dot,
    oneapi::mkl::mklgpu::dotc,
    oneapi::mkl::mklgpu::dotc,
    oneapi::mkl::mklgpu::dotu,
    oneapi::mkl::mklgpu::dotu,
    oneapi::mkl::mklgpu::iamin,
    oneapi::mkl::mklgpu::iamin,
    oneapi::mkl::mklgpu::iamin,
    oneapi::mkl::mklgpu::iamin,
    oneapi::mkl::mklgpu::iamax,
    oneapi::mkl::mklgpu::iamax,
    oneapi::mkl::mklgpu::iamax,
    oneapi::mkl::mklgpu::iamax,
    oneapi::mkl::mklgpu::nrm2,
    oneapi::mkl::mklgpu::nrm2,
    oneapi::mkl::mklgpu::nrm2,
    oneapi::mkl::mklgpu::nrm2,
    oneapi::mkl::mklgpu::rot,
    oneapi::mkl::mklgpu::rot,
    oneapi::mkl::mklgpu::rot,
    oneapi::mkl::mklgpu::rot,
    oneapi::mkl::mklgpu::rotg,
    oneapi::mkl::mklgpu::rotg,
    oneapi::mkl::mklgpu::rotg,
    oneapi::mkl::mklgpu::rotg,
    oneapi::mkl::mklgpu::rotm,
    oneapi::mkl::mklgpu::rotm,
    oneapi::mkl::mklgpu::rotmg,
    oneapi::mkl::mklgpu::rotmg,
    oneapi::mkl::mklgpu::scal,
    oneapi::mkl::mklgpu::scal,
    oneapi::mkl::mklgpu::scal,
    oneapi::mkl::mklgpu::scal,
    oneapi::mkl::mklgpu::scal,
    oneapi::mkl::mklgpu::scal,
    oneapi::mkl::mklgpu::sdsdot,
    oneapi::mkl::mklgpu::swap,
    oneapi::mkl::mklgpu::swap,
    oneapi::mkl::mklgpu::swap,
    oneapi::mkl::mklgpu::swap,
    oneapi::mkl::mklgpu::gbmv,
    oneapi::mkl::mklgpu::gbmv,
    oneapi::mkl::mklgpu::gbmv,
    oneapi::mkl::mklgpu::gbmv,
    oneapi::mkl::mklgpu::gemv,
    oneapi::mkl::mklgpu::gemv,
    oneapi::mkl::mklgpu::gemv,
    oneapi::mkl::mklgpu::gemv,
    oneapi::mkl::mklgpu::ger,
    oneapi::mkl::mklgpu::ger,
    oneapi::mkl::mklgpu::gerc,
    oneapi::mkl::mklgpu::gerc,
    oneapi::mkl::mklgpu::geru,
    oneapi::mkl::mklgpu::geru,
    oneapi::mkl::mklgpu::hbmv,
    oneapi::mkl::mklgpu::hbmv,
    oneapi::mkl::mklgpu::hemv,
    oneapi::mkl::mklgpu::hemv,
    oneapi::mkl::mklgpu::her,
    oneapi::mkl::mklgpu::her,
    oneapi::mkl::mklgpu::her2,
    oneapi::mkl::mklgpu::her2,
    oneapi::mkl::mklgpu::hpmv,
    oneapi::mkl::mklgpu::hpmv,
    oneapi::mkl::mklgpu::hpr,
    oneapi::mkl::mklgpu::hpr,
    oneapi::mkl::mklgpu::hpr2,
    oneapi::mkl::mklgpu::hpr2,
    oneapi::mkl::mklgpu::sbmv,
    oneapi::mkl::mklgpu::sbmv,
    oneapi::mkl::mklgpu::spmv,
    oneapi::mkl::mklgpu::spmv,
    oneapi::mkl::mklgpu::spr,
    oneapi::mkl::mklgpu::spr,
    oneapi::mkl::mklgpu::spr2,
    oneapi::mkl::mklgpu::spr2,
    oneapi::mkl::mklgpu::symv,
    oneapi::mkl::mklgpu::symv,
    oneapi::mkl::mklgpu::syr,
    oneapi::mkl::mklgpu::syr,
    oneapi::mkl::mklgpu::syr2,
    oneapi::mkl::mklgpu::syr2,
    oneapi::mkl::mklgpu::tbmv,
    oneapi::mkl::mklgpu::tbmv,
    oneapi::mkl::mklgpu::tbmv,
    oneapi::mkl::mklgpu::tbmv,
    oneapi::mkl::mklgpu::tbsv,
    oneapi::mkl::mklgpu::tbsv,
    oneapi::mkl::mklgpu::tbsv,
    oneapi::mkl::mklgpu::tbsv,
    oneapi::mkl::mklgpu::tpmv,
    oneapi::mkl::mklgpu::tpmv,
    oneapi::mkl::mklgpu::tpmv,
    oneapi::mkl::mklgpu::tpmv,
    oneapi::mkl::mklgpu::tpsv,
    oneapi::mkl::mklgpu::tpsv,
    oneapi::mkl::mklgpu::tpsv,
    oneapi::mkl::mklgpu::tpsv,
    oneapi::mkl::mklgpu::trmv,
    oneapi::mkl::mklgpu::trmv,
    oneapi::mkl::mklgpu::trmv,
    oneapi::mkl::mklgpu::trmv,
    oneapi::mkl::mklgpu::trsv,
    oneapi::mkl::mklgpu::trsv,
    oneapi::mkl::mklgpu::trsv,
    oneapi::mkl::mklgpu::trsv,
    oneapi::mkl::mklgpu::gemm,
    oneapi::mkl::mklgpu::gemm,
    oneapi::mkl::mklgpu::gemm,
    oneapi::mkl::mklgpu::gemm,
    oneapi::mkl::mklgpu::gemm,
    oneapi::mkl::mklgpu::hemm,
    oneapi::mkl::mklgpu::hemm,
    oneapi::mkl::mklgpu::herk,
    oneapi::mkl::mklgpu::herk,
    oneapi::mkl::mklgpu::her2k,
    oneapi::mkl::mklgpu::her2k,
    oneapi::mkl::mklgpu::symm,
    oneapi::mkl::mklgpu::symm,
    oneapi::mkl::mklgpu::symm,
    oneapi::mkl::mklgpu::symm,
    oneapi::mkl::mklgpu::syrk,
    oneapi::mkl::mklgpu::syrk,
    oneapi::mkl::mklgpu::syrk,
    oneapi::mkl::mklgpu::syrk,
    oneapi::mkl::mklgpu::syr2k,
    oneapi::mkl::mklgpu::syr2k,
    oneapi::mkl::mklgpu::syr2k,
    oneapi::mkl::mklgpu::syr2k,
    oneapi::mkl::mklgpu::trmm,
    oneapi::mkl::mklgpu::trmm,
    oneapi::mkl::mklgpu::trmm,
    oneapi::mkl::mklgpu::trmm,
    oneapi::mkl::mklgpu::trsm,
    oneapi::mkl::mklgpu::trsm,
    oneapi::mkl::mklgpu::trsm,
    oneapi::mkl::mklgpu::trsm,
    oneapi::mkl::mklgpu::gemm_batch,
    oneapi::mkl::mklgpu::gemm_batch,
    oneapi::mkl::mklgpu::gemm_batch,
    oneapi::mkl::mklgpu::gemm_batch,
    oneapi::mkl::mklgpu::trsm_batch,
    oneapi::mkl::mklgpu::trsm_batch,
    oneapi::mkl::mklgpu::trsm_batch,
    oneapi::mkl::mklgpu::trsm_batch,
    oneapi::mkl::mklgpu::gemmt,
    oneapi::mkl::mklgpu::gemmt,
    oneapi::mkl::mklgpu::gemmt,
    oneapi::mkl::mklgpu::gemmt,
    oneapi::mkl::mklgpu::gemm_ext,
    oneapi::mkl::mklgpu::gemm_ext,
    oneapi::mkl::mklgpu::gemm_ext,
    oneapi::mkl::mklgpu::gemm_ext,
    oneapi::mkl::mklgpu::gemm_ext,
    oneapi::mkl::mklgpu::gemm_ext,
    oneapi::mkl::mklgpu::gemm_ext,
    oneapi::mkl::mklgpu::asum,
    oneapi::mkl::mklgpu::asum,
    oneapi::mkl::mklgpu::asum,
    oneapi::mkl::mklgpu::asum,
    oneapi::mkl::mklgpu::axpy,
    oneapi::mkl::mklgpu::axpy,
    oneapi::mkl::mklgpu::axpy,
    oneapi::mkl::mklgpu::axpy,
    oneapi::mkl::mklgpu::axpy_batch,
    oneapi::mkl::mklgpu::axpy_batch,
    oneapi::mkl::mklgpu::axpy_batch,
    oneapi::mkl::mklgpu::axpy_batch,
    oneapi::mkl::mklgpu::copy,
    oneapi::mkl::mklgpu::copy,
    oneapi::mkl::mklgpu::copy,
    oneapi::mkl::mklgpu::copy,
    oneapi::mkl::mklgpu::dot,
    oneapi::mkl::mklgpu::dot,
    oneapi::mkl::mklgpu::dot,
    oneapi::mkl::mklgpu::dotc,
    oneapi::mkl::mklgpu::dotc,
    oneapi::mkl::mklgpu::dotu,
    oneapi::mkl::mklgpu::dotu,
    oneapi::mkl::mklgpu::iamin,
    oneapi::mkl::mklgpu::iamin,
    oneapi::mkl::mklgpu::iamin,
    oneapi::mkl::mklgpu::iamin,
    oneapi::mkl::mklgpu::iamax,
    oneapi::mkl::mklgpu::iamax,
    oneapi::mkl::mklgpu::iamax,
    oneapi::mkl::mklgpu::iamax,
    oneapi::mkl::mklgpu::nrm2,
    oneapi::mkl::mklgpu::nrm2,
    oneapi::mkl::mklgpu::nrm2,
    oneapi::mkl::mklgpu::nrm2,
    oneapi::mkl::mklgpu::rot,
    oneapi::mkl::mklgpu::rot,
    oneapi::mkl::mklgpu::rot,
    oneapi::mkl::mklgpu::rot,
    oneapi::mkl::mklgpu::rotg,
    oneapi::mkl::mklgpu::rotg,
    oneapi::mkl::mklgpu::rotg,
    oneapi::mkl::mklgpu::rotg,
    oneapi::mkl::mklgpu::rotm,
    oneapi::mkl::mklgpu::rotm,
    oneapi::mkl::mklgpu::rotmg,
    oneapi::mkl::mklgpu::rotmg,
    oneapi::mkl::mklgpu::scal,
    oneapi::mkl::mklgpu::scal,
    oneapi::mkl::mklgpu::scal,
    oneapi::mkl::mklgpu::scal,
    oneapi::mkl::mklgpu::scal,
    oneapi::mkl::mklgpu::scal,
    oneapi::mkl::mklgpu::sdsdot,
    oneapi::mkl::mklgpu::swap,
    oneapi::mkl::mklgpu::swap,
    oneapi::mkl::mklgpu::swap,
    oneapi::mkl::mklgpu::swap,
    oneapi::mkl::mklgpu::gbmv,
    oneapi::mkl::mklgpu::gbmv,
    oneapi::mkl::mklgpu::gbmv,
    oneapi::mkl::mklgpu::gbmv,
    oneapi::mkl::mklgpu::gemv,
    oneapi::mkl::mklgpu::gemv,
    oneapi::mkl::mklgpu::gemv,
    oneapi::mkl::mklgpu::gemv,
    oneapi::mkl::mklgpu::ger,
    oneapi::mkl::mklgpu::ger,
    oneapi::mkl::mklgpu::gerc,
    oneapi::mkl::mklgpu::gerc,
    oneapi::mkl::mklgpu::geru,
    oneapi::mkl::mklgpu::geru,
    oneapi::mkl::mklgpu::hbmv,
    oneapi::mkl::mklgpu::hbmv,
    oneapi::mkl::mklgpu::hemv,
    oneapi::mkl::mklgpu::hemv,
    oneapi::mkl::mklgpu::her,
    oneapi::mkl::mklgpu::her,
    oneapi::mkl::mklgpu::her2,
    oneapi::mkl::mklgpu::her2,
    oneapi::mkl::mklgpu::hpmv,
    oneapi::mkl::mklgpu::hpmv,
    oneapi::mkl::mklgpu::hpr,
    oneapi::mkl::mklgpu::hpr,
    oneapi::mkl::mklgpu::hpr2,
    oneapi::mkl::mklgpu::hpr2,
    oneapi::mkl::mklgpu::sbmv,
    oneapi::mkl::mklgpu::sbmv,
    oneapi::mkl::mklgpu::spmv,
    oneapi::mkl::mklgpu::spmv,
    oneapi::mkl::mklgpu::spr,
    oneapi::mkl::mklgpu::spr,
    oneapi::mkl::mklgpu::spr2,
    oneapi::mkl::mklgpu::spr2,
    oneapi::mkl::mklgpu::symv,
    oneapi::mkl::mklgpu::symv,
    oneapi::mkl::mklgpu::syr,
    oneapi::mkl::mklgpu::syr,
    oneapi::mkl::mklgpu::syr2,
    oneapi::mkl::mklgpu::syr2,
    oneapi::mkl::mklgpu::tbmv,
    oneapi::mkl::mklgpu::tbmv,
    oneapi::mkl::mklgpu::tbmv,
    oneapi::mkl::mklgpu::tbmv,
    oneapi::mkl::mklgpu::tbsv,
    oneapi::mkl::mklgpu::tbsv,
    oneapi::mkl::mklgpu::tbsv,
    oneapi::mkl::mklgpu::tbsv,
    oneapi::mkl::mklgpu::tpmv,
    oneapi::mkl::mklgpu::tpmv,
    oneapi::mkl::mklgpu::tpmv,
    oneapi::mkl::mklgpu::tpmv,
    oneapi::mkl::mklgpu::tpsv,
    oneapi::mkl::mklgpu::tpsv,
    oneapi::mkl::mklgpu::tpsv,
    oneapi::mkl::mklgpu::tpsv,
    oneapi::mkl::mklgpu::trmv,
    oneapi::mkl::mklgpu::trmv,
    oneapi::mkl::mklgpu::trmv,
    oneapi::mkl::mklgpu::trmv,
    oneapi::mkl::mklgpu::trsv,
    oneapi::mkl::mklgpu::trsv,
    oneapi::mkl::mklgpu::trsv,
    oneapi::mkl::mklgpu::trsv,
    oneapi::mkl::mklgpu::gemm,
    oneapi::mkl::mklgpu::gemm,
    oneapi::mkl::mklgpu::gemm,
    oneapi::mkl::mklgpu::gemm,
    oneapi::mkl::mklgpu::hemm,
    oneapi::mkl::mklgpu::hemm,
    oneapi::mkl::mklgpu::herk,
    oneapi::mkl::mklgpu::herk,
    oneapi::mkl::mklgpu::her2k,
    oneapi::mkl::mklgpu::her2k,
    oneapi::mkl::mklgpu::symm,
    oneapi::mkl::mklgpu::symm,
    oneapi::mkl::mklgpu::symm,
    oneapi::mkl::mklgpu::symm,
    oneapi::mkl::mklgpu::syrk,
    oneapi::mkl::mklgpu::syrk,
    oneapi::mkl::mklgpu::syrk,
    oneapi::mkl::mklgpu::syrk,
    oneapi::mkl::mklgpu::syr2k,
    oneapi::mkl::mklgpu::syr2k,
    oneapi::mkl::mklgpu::syr2k,
    oneapi::mkl::mklgpu::syr2k,
    oneapi::mkl::mklgpu::trmm,
    oneapi::mkl::mklgpu::trmm,
    oneapi::mkl::mklgpu::trmm,
    oneapi::mkl::mklgpu::trmm,
    oneapi::mkl::mklgpu::trsm,
    oneapi::mkl::mklgpu::trsm,
    oneapi::mkl::mklgpu::trsm,
    oneapi::mkl::mklgpu::trsm,
    oneapi::mkl::mklgpu::gemm_batch,
    oneapi::mkl::mklgpu::gemm_batch,
    oneapi::mkl::mklgpu::gemm_batch,
    oneapi::mkl::mklgpu::gemm_batch,
    oneapi::mkl::mklgpu::gemm_batch,
    oneapi::mkl::mklgpu::gemm_batch,
    oneapi::mkl::mklgpu::gemm_batch,
    oneapi::mkl::mklgpu::gemm_batch,
    oneapi::mkl::mklgpu::gemmt,
    oneapi::mkl::mklgpu::gemmt,
    oneapi::mkl::mklgpu::gemmt,
    oneapi::mkl::mklgpu::gemmt,
};
