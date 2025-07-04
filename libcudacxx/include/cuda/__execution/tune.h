//===----------------------------------------------------------------------===//
//
// Part of libcu++, the C++ Standard Library for your entire system,
// under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES.
//
//===----------------------------------------------------------------------===//

#ifndef __CUDA___EXECUTION_TUNE_H
#define __CUDA___EXECUTION_TUNE_H

#include <cuda/std/detail/__config>

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header

#include <cuda/std/__concepts/concept_macros.h>
#include <cuda/std/__execution/env.h>
#include <cuda/std/__type_traits/conjunction.h>
#include <cuda/std/__type_traits/is_base_of.h>
#include <cuda/std/__type_traits/is_empty.h>

#include <cuda/std/__cccl/prologue.h>

_LIBCUDACXX_BEGIN_NAMESPACE_CUDA_EXECUTION

struct __get_tuning_t
{
  _CCCL_EXEC_CHECK_DISABLE
  _CCCL_TEMPLATE(class _Env)
  _CCCL_REQUIRES(_CUDA_STD_EXEC::__queryable_with<_Env, __get_tuning_t>)
  [[nodiscard]] _CCCL_TRIVIAL_API constexpr auto operator()(const _Env& __env) const noexcept
  {
    static_assert(noexcept(__env.query(*this)));
    return __env.query(*this);
  }

  [[nodiscard]] _CCCL_TRIVIAL_API static constexpr auto query(_CUDA_STD_EXEC::forwarding_query_t) noexcept -> bool
  {
    return true;
  }
};

_CCCL_GLOBAL_CONSTANT auto __get_tuning = __get_tuning_t{};

template <class... _Tunings>
[[nodiscard]] _CCCL_TRIVIAL_API auto __tune(_Tunings...)
{
  static_assert((_CUDA_VSTD::is_empty_v<_Tunings> && ...), "Stateful tunings are not implemented");

  // clang < 19 doesn't like this code
  // since all the tunings are stateless, let's ignore incoming parameters
  _CUDA_STD_EXEC::env<_Tunings...> __env{};

  return _CUDA_STD_EXEC::prop{__get_tuning_t{}, __env};
}

_LIBCUDACXX_END_NAMESPACE_CUDA_EXECUTION

#include <cuda/std/__cccl/epilogue.h>

#endif // __CUDA___EXECUTION_TUNE_H
