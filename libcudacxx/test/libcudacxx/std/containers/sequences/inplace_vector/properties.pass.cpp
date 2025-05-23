//===----------------------------------------------------------------------===//
//
// Part of libcu++, the C++ Standard Library for your entire system,
// under the Apache License v2.0 with LLVM Exceptions.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES.
//
//===----------------------------------------------------------------------===//

#include <cuda/std/__algorithm_>
#include <cuda/std/cassert>
#include <cuda/std/initializer_list>
#include <cuda/std/inplace_vector>
#include <cuda/std/iterator>
#include <cuda/std/limits>
#include <cuda/std/type_traits>

#include "test_macros.h"
#include "types.h"

__host__ __device__ void test()
{
  // Ensure that we pack the inplace_vector as tight as possible
  static_assert(cuda::std::is_empty<cuda::std::inplace_vector<int, 0>>::value, "");
  static_assert(cuda::std::is_empty<cuda::std::inplace_vector<Trivial, 0>>::value, "");
  static_assert(cuda::std::is_empty<cuda::std::inplace_vector<NonTrivial, 0>>::value, "");

  static_assert(cuda::std::is_trivial<cuda::std::inplace_vector<int, 0>>::value, "");
  static_assert(cuda::std::is_trivial<cuda::std::inplace_vector<Trivial, 0>>::value, "");
  static_assert(cuda::std::is_trivial<cuda::std::inplace_vector<NonTrivial, 0>>::value, "");

  static_assert(sizeof(cuda::std::inplace_vector<char, 4>) == 4 + sizeof(cuda::std::uint8_t), "");
  static_assert(sizeof(cuda::std::inplace_vector<char, cuda::std::numeric_limits<cuda::std::uint8_t>::max()>)
                  == cuda::std::numeric_limits<cuda::std::uint8_t>::max() + sizeof(cuda::std::uint8_t),
                "");
  static_assert(sizeof(cuda::std::inplace_vector<char, cuda::std::numeric_limits<cuda::std::uint8_t>::max() + 1>)
                  == cuda::std::numeric_limits<cuda::std::uint8_t>::max() + 1 + sizeof(cuda::std::uint16_t),
                "");
  static_assert(sizeof(cuda::std::inplace_vector<char, cuda::std::numeric_limits<cuda::std::uint16_t>::max()>)
                  == cuda::std::numeric_limits<cuda::std::uint16_t>::max() + 1 + sizeof(cuda::std::uint16_t),
                "");
  static_assert(sizeof(cuda::std::inplace_vector<char, cuda::std::numeric_limits<cuda::std::uint16_t>::max() + 1>)
                  == cuda::std::numeric_limits<cuda::std::uint16_t>::max() + 1 + sizeof(cuda::std::uint32_t),
                "");

#if !TEST_COMPILER(MSVC) // too large array
  // There is an overflow issue when using cuda::std::numeric_limits<cuda::std::uint32_t>::max() directly
  constexpr size_t uint32_t_max = cuda::std::numeric_limits<cuda::std::uint32_t>::max();
  static_assert(sizeof(cuda::std::inplace_vector<char, uint32_t_max>) == uint32_t_max + 1 + sizeof(cuda::std::uint32_t),
                "");
  static_assert(
    sizeof(cuda::std::inplace_vector<char, uint32_t_max + 1>) == uint32_t_max + 1 + sizeof(cuda::std::uint64_t), "");
#endif // !TEST_COMPILER(MSVC)

  // Check the type aliases
  using inplace_vector = cuda::std::inplace_vector<int, 42>;
  static_assert(cuda::std::is_same<int, typename inplace_vector::value_type>::value, "");
  static_assert(cuda::std::is_same<cuda::std::size_t, typename inplace_vector::size_type>::value, "");
  static_assert(cuda::std::is_same<cuda::std::ptrdiff_t, typename inplace_vector::difference_type>::value, "");
  static_assert(cuda::std::is_same<int*, typename inplace_vector::pointer>::value, "");
  static_assert(cuda::std::is_same<const int*, typename inplace_vector::const_pointer>::value, "");
  static_assert(cuda::std::is_same<int&, typename inplace_vector::reference>::value, "");
  static_assert(cuda::std::is_same<const int&, typename inplace_vector::const_reference>::value, "");
  static_assert(cuda::std::is_same<int*, typename inplace_vector::iterator>::value, "");
  static_assert(cuda::std::is_same<const int*, typename inplace_vector::const_iterator>::value, "");
  static_assert(cuda::std::is_same<cuda::std::reverse_iterator<int*>, typename inplace_vector::reverse_iterator>::value,
                "");
  static_assert(
    cuda::std::is_same<cuda::std::reverse_iterator<const int*>, typename inplace_vector::const_reverse_iterator>::value,
    "");

  static_assert(cuda::std::ranges::contiguous_range<inplace_vector>);

  // Ensure we uphoold the guarantees about triviality in [inplace.vector.overview]
  // * If is_trivially_copy_constructible_v<T> is true, then IV has a trivial copy constructor.
  static_assert(
    cuda::std::is_trivially_copy_constructible<cuda::std::inplace_vector<ThrowingDefaultConstruct, 42>>::value, "");
  static_assert(
    !cuda::std::is_trivially_copy_constructible<cuda::std::inplace_vector<ThrowingCopyConstructor, 42>>::value, "");
  static_assert(
    cuda::std::is_trivially_copy_constructible<cuda::std::inplace_vector<ThrowingMoveConstructor, 42>>::value, "");
  static_assert(
    cuda::std::is_trivially_copy_constructible<cuda::std::inplace_vector<ThrowingCopyAssignment, 42>>::value, "");
  static_assert(
    cuda::std::is_trivially_copy_constructible<cuda::std::inplace_vector<ThrowingMoveAssignment, 42>>::value, "");
  static_assert(!cuda::std::is_trivially_copy_constructible<cuda::std::inplace_vector<NonTrivialDestructor, 42>>::value,
                "");

  // * If is_trivially_move_constructible_v<T> is true, then IV has a trivial move constructor
  static_assert(
    cuda::std::is_trivially_move_constructible<cuda::std::inplace_vector<ThrowingDefaultConstruct, 42>>::value, "");
  static_assert(
    cuda::std::is_trivially_move_constructible<cuda::std::inplace_vector<ThrowingCopyConstructor, 42>>::value, "");
  static_assert(
    !cuda::std::is_trivially_move_constructible<cuda::std::inplace_vector<ThrowingMoveConstructor, 42>>::value, "");
  static_assert(
    cuda::std::is_trivially_move_constructible<cuda::std::inplace_vector<ThrowingCopyAssignment, 42>>::value, "");
  static_assert(
    cuda::std::is_trivially_move_constructible<cuda::std::inplace_vector<ThrowingMoveAssignment, 42>>::value, "");
  static_assert(!cuda::std::is_trivially_move_constructible<cuda::std::inplace_vector<NonTrivialDestructor, 42>>::value,
                "");

  // * If is_trivially_destructible_v<T> is true, then IV has a trivial destructor
  static_assert(cuda::std::is_trivially_destructible<cuda::std::inplace_vector<ThrowingDefaultConstruct, 42>>::value,
                "");
  static_assert(cuda::std::is_trivially_destructible<cuda::std::inplace_vector<ThrowingCopyConstructor, 42>>::value,
                "");
  static_assert(cuda::std::is_trivially_destructible<cuda::std::inplace_vector<ThrowingMoveConstructor, 42>>::value,
                "");
  static_assert(cuda::std::is_trivially_destructible<cuda::std::inplace_vector<ThrowingCopyAssignment, 42>>::value, "");
  static_assert(cuda::std::is_trivially_destructible<cuda::std::inplace_vector<ThrowingMoveAssignment, 42>>::value, "");
  static_assert(!cuda::std::is_trivially_destructible<cuda::std::inplace_vector<NonTrivialDestructor, 42>>::value, "");

  // * If is_trivially_destructible_v<T> is true,
  // if is_trivially_copy_constructible_v<T> && is_trivially_copy_assignable_v<T> is true, then IV has a trivial copy
  // assignment operator
  static_assert(cuda::std::is_trivially_copy_assignable<cuda::std::inplace_vector<ThrowingDefaultConstruct, 42>>::value,
                "");
  static_assert(!cuda::std::is_trivially_copy_assignable<cuda::std::inplace_vector<ThrowingCopyConstructor, 42>>::value,
                "");
  static_assert(cuda::std::is_trivially_copy_assignable<cuda::std::inplace_vector<ThrowingMoveConstructor, 42>>::value,
                "");
  static_assert(!cuda::std::is_trivially_copy_assignable<cuda::std::inplace_vector<ThrowingCopyAssignment, 42>>::value,
                "");
  static_assert(cuda::std::is_trivially_copy_assignable<cuda::std::inplace_vector<ThrowingMoveAssignment, 42>>::value,
                "");
  static_assert(!cuda::std::is_trivially_copy_assignable<cuda::std::inplace_vector<NonTrivialDestructor, 42>>::value,
                "");

  // * If is_trivially_destructible_v<T> is true,
  // if is_trivially_move_constructible_v<T> && is_trivially_move_assignable_v<T> is true, then IV has a trivial move
  // assignment operator
  static_assert(cuda::std::is_trivially_move_assignable<cuda::std::inplace_vector<ThrowingDefaultConstruct, 42>>::value,
                "");
  static_assert(cuda::std::is_trivially_move_assignable<cuda::std::inplace_vector<ThrowingCopyConstructor, 42>>::value,
                "");
  static_assert(!cuda::std::is_trivially_move_assignable<cuda::std::inplace_vector<ThrowingMoveConstructor, 42>>::value,
                "");
  static_assert(cuda::std::is_trivially_move_assignable<cuda::std::inplace_vector<ThrowingCopyAssignment, 42>>::value,
                "");
  static_assert(!cuda::std::is_trivially_move_assignable<cuda::std::inplace_vector<ThrowingMoveAssignment, 42>>::value,
                "");
  static_assert(!cuda::std::is_trivially_move_assignable<cuda::std::inplace_vector<NonTrivialDestructor, 42>>::value,
                "");

  // Implicit: * If is_trivially_destructible_v<T> is true, then IV has is_trivially_copyable
  static_assert(cuda::std::is_trivially_copyable<cuda::std::inplace_vector<ThrowingDefaultConstruct, 42>>::value, "");
  static_assert(!cuda::std::is_trivially_copyable<cuda::std::inplace_vector<ThrowingCopyConstructor, 42>>::value, "");
  static_assert(!cuda::std::is_trivially_copyable<cuda::std::inplace_vector<ThrowingMoveConstructor, 42>>::value, "");
  static_assert(!cuda::std::is_trivially_copyable<cuda::std::inplace_vector<ThrowingCopyAssignment, 42>>::value, "");
  static_assert(!cuda::std::is_trivially_copyable<cuda::std::inplace_vector<ThrowingMoveAssignment, 42>>::value, "");
  static_assert(!cuda::std::is_trivially_copyable<cuda::std::inplace_vector<NonTrivialDestructor, 42>>::value, "");
}

int main(int, char**)
{
  return 0;
}
