//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <chrono>
// class month;

// constexpr bool ok() const noexcept;
//  Returns: 1 <= d_ && d_ <= 12

#include <cuda/std/cassert>
#include <cuda/std/chrono>
#include <cuda/std/type_traits>

#include "test_macros.h"

int main(int, char**)
{
  using month = cuda::std::chrono::month;

  static_assert(noexcept(cuda::std::declval<const month>().ok()));
  static_assert(cuda::std::is_same_v<bool, decltype(cuda::std::declval<const month>().ok())>);

  static_assert(!month{0}.ok(), "");
  static_assert(month{1}.ok(), "");

  assert(!month{0}.ok());
  for (unsigned i = 1; i <= 12; ++i)
  {
    assert(month{i}.ok());
  }
  for (unsigned i = 13; i <= 255; ++i)
  {
    assert(!month{i}.ok());
  }

  return 0;
}
