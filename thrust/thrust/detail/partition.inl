/*
 *  Copyright 2008-2013 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include <thrust/detail/config.h>

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header
#include <thrust/iterator/iterator_traits.h>
#include <thrust/partition.h>
#include <thrust/system/detail/adl/partition.h>
#include <thrust/system/detail/generic/partition.h>
#include <thrust/system/detail/generic/select_system.h>

THRUST_NAMESPACE_BEGIN

_CCCL_EXEC_CHECK_DISABLE
template <typename DerivedPolicy, typename ForwardIterator, typename Predicate>
_CCCL_HOST_DEVICE ForwardIterator partition(
  const thrust::detail::execution_policy_base<DerivedPolicy>& exec,
  ForwardIterator first,
  ForwardIterator last,
  Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::partition");
  using thrust::system::detail::generic::partition;
  return partition(thrust::detail::derived_cast(thrust::detail::strip_const(exec)), first, last, pred);
} // end partition()

_CCCL_EXEC_CHECK_DISABLE
template <typename DerivedPolicy, typename ForwardIterator, typename InputIterator, typename Predicate>
_CCCL_HOST_DEVICE ForwardIterator partition(
  const thrust::detail::execution_policy_base<DerivedPolicy>& exec,
  ForwardIterator first,
  ForwardIterator last,
  InputIterator stencil,
  Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::partition");
  using thrust::system::detail::generic::partition;
  return partition(thrust::detail::derived_cast(thrust::detail::strip_const(exec)), first, last, stencil, pred);
} // end partition()

_CCCL_EXEC_CHECK_DISABLE
template <typename DerivedPolicy,
          typename InputIterator,
          typename OutputIterator1,
          typename OutputIterator2,
          typename Predicate>
_CCCL_HOST_DEVICE thrust::pair<OutputIterator1, OutputIterator2> partition_copy(
  const thrust::detail::execution_policy_base<DerivedPolicy>& exec,
  InputIterator first,
  InputIterator last,
  OutputIterator1 out_true,
  OutputIterator2 out_false,
  Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::partition_copy");
  using thrust::system::detail::generic::partition_copy;
  return partition_copy(
    thrust::detail::derived_cast(thrust::detail::strip_const(exec)), first, last, out_true, out_false, pred);
} // end partition_copy()

_CCCL_EXEC_CHECK_DISABLE
template <typename DerivedPolicy,
          typename InputIterator1,
          typename InputIterator2,
          typename OutputIterator1,
          typename OutputIterator2,
          typename Predicate>
_CCCL_HOST_DEVICE thrust::pair<OutputIterator1, OutputIterator2> partition_copy(
  const thrust::detail::execution_policy_base<DerivedPolicy>& exec,
  InputIterator1 first,
  InputIterator1 last,
  InputIterator2 stencil,
  OutputIterator1 out_true,
  OutputIterator2 out_false,
  Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::partition_copy");
  using thrust::system::detail::generic::partition_copy;
  return partition_copy(
    thrust::detail::derived_cast(thrust::detail::strip_const(exec)), first, last, stencil, out_true, out_false, pred);
} // end partition_copy()

_CCCL_EXEC_CHECK_DISABLE
template <typename DerivedPolicy, typename ForwardIterator, typename Predicate>
_CCCL_HOST_DEVICE ForwardIterator stable_partition(
  const thrust::detail::execution_policy_base<DerivedPolicy>& exec,
  ForwardIterator first,
  ForwardIterator last,
  Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::stable_partition");
  using thrust::system::detail::generic::stable_partition;
  return stable_partition(thrust::detail::derived_cast(thrust::detail::strip_const(exec)), first, last, pred);
} // end stable_partition()

_CCCL_EXEC_CHECK_DISABLE
template <typename DerivedPolicy, typename ForwardIterator, typename InputIterator, typename Predicate>
_CCCL_HOST_DEVICE ForwardIterator stable_partition(
  const thrust::detail::execution_policy_base<DerivedPolicy>& exec,
  ForwardIterator first,
  ForwardIterator last,
  InputIterator stencil,
  Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::stable_partition");
  using thrust::system::detail::generic::stable_partition;
  return stable_partition(thrust::detail::derived_cast(thrust::detail::strip_const(exec)), first, last, stencil, pred);
} // end stable_partition()

_CCCL_EXEC_CHECK_DISABLE
template <typename DerivedPolicy,
          typename InputIterator,
          typename OutputIterator1,
          typename OutputIterator2,
          typename Predicate>
_CCCL_HOST_DEVICE thrust::pair<OutputIterator1, OutputIterator2> stable_partition_copy(
  const thrust::detail::execution_policy_base<DerivedPolicy>& exec,
  InputIterator first,
  InputIterator last,
  OutputIterator1 out_true,
  OutputIterator2 out_false,
  Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::stable_partition_copy");
  using thrust::system::detail::generic::stable_partition_copy;
  return stable_partition_copy(
    thrust::detail::derived_cast(thrust::detail::strip_const(exec)), first, last, out_true, out_false, pred);
} // end stable_partition_copy()

_CCCL_EXEC_CHECK_DISABLE
template <typename DerivedPolicy,
          typename InputIterator1,
          typename InputIterator2,
          typename OutputIterator1,
          typename OutputIterator2,
          typename Predicate>
_CCCL_HOST_DEVICE thrust::pair<OutputIterator1, OutputIterator2> stable_partition_copy(
  const thrust::detail::execution_policy_base<DerivedPolicy>& exec,
  InputIterator1 first,
  InputIterator1 last,
  InputIterator2 stencil,
  OutputIterator1 out_true,
  OutputIterator2 out_false,
  Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::stable_partition_copy");
  using thrust::system::detail::generic::stable_partition_copy;
  return stable_partition_copy(
    thrust::detail::derived_cast(thrust::detail::strip_const(exec)), first, last, stencil, out_true, out_false, pred);
} // end stable_partition_copy()

_CCCL_EXEC_CHECK_DISABLE
template <typename DerivedPolicy, typename ForwardIterator, typename Predicate>
_CCCL_HOST_DEVICE ForwardIterator partition_point(
  const thrust::detail::execution_policy_base<DerivedPolicy>& exec,
  ForwardIterator first,
  ForwardIterator last,
  Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::partition_point");
  using thrust::system::detail::generic::partition_point;
  return partition_point(thrust::detail::derived_cast(thrust::detail::strip_const(exec)), first, last, pred);
} // end partition_point()

_CCCL_EXEC_CHECK_DISABLE
template <typename DerivedPolicy, typename InputIterator, typename Predicate>
_CCCL_HOST_DEVICE bool is_partitioned(
  const thrust::detail::execution_policy_base<DerivedPolicy>& exec,
  InputIterator first,
  InputIterator last,
  Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::is_partitioned");
  using thrust::system::detail::generic::is_partitioned;
  return is_partitioned(thrust::detail::derived_cast(thrust::detail::strip_const(exec)), first, last, pred);
} // end is_partitioned()

template <typename ForwardIterator, typename Predicate>
ForwardIterator partition(ForwardIterator first, ForwardIterator last, Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::partition");
  using thrust::system::detail::generic::select_system;

  using System = typename thrust::iterator_system<ForwardIterator>::type;

  System system;

  return thrust::partition(select_system(system), first, last, pred);
} // end partition()

template <typename ForwardIterator, typename InputIterator, typename Predicate>
ForwardIterator partition(ForwardIterator first, ForwardIterator last, InputIterator stencil, Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::partition");
  using thrust::system::detail::generic::select_system;

  using System1 = typename thrust::iterator_system<ForwardIterator>::type;
  using System2 = typename thrust::iterator_system<InputIterator>::type;

  System1 system1;
  System2 system2;

  return thrust::partition(select_system(system1, system2), first, last, stencil, pred);
} // end partition()

template <typename ForwardIterator, typename Predicate>
ForwardIterator stable_partition(ForwardIterator first, ForwardIterator last, Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::stable_partition");
  using thrust::system::detail::generic::select_system;

  using System = typename thrust::iterator_system<ForwardIterator>::type;

  System system;

  return thrust::stable_partition(select_system(system), first, last, pred);
} // end stable_partition()

template <typename ForwardIterator, typename InputIterator, typename Predicate>
ForwardIterator stable_partition(ForwardIterator first, ForwardIterator last, InputIterator stencil, Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::stable_partition");
  using thrust::system::detail::generic::select_system;

  using System1 = typename thrust::iterator_system<ForwardIterator>::type;
  using System2 = typename thrust::iterator_system<InputIterator>::type;

  System1 system1;
  System2 system2;

  return thrust::stable_partition(select_system(system1, system2), first, last, stencil, pred);
} // end stable_partition()

template <typename InputIterator, typename OutputIterator1, typename OutputIterator2, typename Predicate>
thrust::pair<OutputIterator1, OutputIterator2> partition_copy(
  InputIterator first, InputIterator last, OutputIterator1 out_true, OutputIterator2 out_false, Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::partition_copy");
  using thrust::system::detail::generic::select_system;

  using System1 = typename thrust::iterator_system<InputIterator>::type;
  using System2 = typename thrust::iterator_system<OutputIterator1>::type;
  using System3 = typename thrust::iterator_system<OutputIterator2>::type;

  System1 system1;
  System2 system2;
  System3 system3;

  return thrust::partition_copy(select_system(system1, system2, system3), first, last, out_true, out_false, pred);
} // end partition_copy()

template <typename InputIterator1,
          typename InputIterator2,
          typename OutputIterator1,
          typename OutputIterator2,
          typename Predicate>
thrust::pair<OutputIterator1, OutputIterator2> partition_copy(
  InputIterator1 first,
  InputIterator1 last,
  InputIterator2 stencil,
  OutputIterator1 out_true,
  OutputIterator2 out_false,
  Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::partition_copy");
  using thrust::system::detail::generic::select_system;

  using System1 = typename thrust::iterator_system<InputIterator1>::type;
  using System2 = typename thrust::iterator_system<InputIterator1>::type;
  using System3 = typename thrust::iterator_system<OutputIterator1>::type;
  using System4 = typename thrust::iterator_system<OutputIterator2>::type;

  System1 system1;
  System2 system2;
  System3 system3;
  System4 system4;

  return thrust::partition_copy(
    select_system(system1, system2, system3, system4), first, last, stencil, out_true, out_false, pred);
} // end partition_copy()

template <typename InputIterator, typename OutputIterator1, typename OutputIterator2, typename Predicate>
thrust::pair<OutputIterator1, OutputIterator2> stable_partition_copy(
  InputIterator first, InputIterator last, OutputIterator1 out_true, OutputIterator2 out_false, Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::stable_partition_copy");
  using thrust::system::detail::generic::select_system;

  using System1 = typename thrust::iterator_system<InputIterator>::type;
  using System2 = typename thrust::iterator_system<OutputIterator1>::type;
  using System3 = typename thrust::iterator_system<OutputIterator2>::type;

  System1 system1;
  System2 system2;
  System3 system3;

  return thrust::stable_partition_copy(select_system(system1, system2, system3), first, last, out_true, out_false, pred);
} // end stable_partition_copy()

template <typename InputIterator1,
          typename InputIterator2,
          typename OutputIterator1,
          typename OutputIterator2,
          typename Predicate>
thrust::pair<OutputIterator1, OutputIterator2> stable_partition_copy(
  InputIterator1 first,
  InputIterator1 last,
  InputIterator2 stencil,
  OutputIterator1 out_true,
  OutputIterator2 out_false,
  Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::stable_partition_copy");
  using thrust::system::detail::generic::select_system;

  using System1 = typename thrust::iterator_system<InputIterator1>::type;
  using System2 = typename thrust::iterator_system<InputIterator2>::type;
  using System3 = typename thrust::iterator_system<OutputIterator1>::type;
  using System4 = typename thrust::iterator_system<OutputIterator2>::type;

  System1 system1;
  System2 system2;
  System3 system3;
  System4 system4;

  return thrust::stable_partition_copy(
    select_system(system1, system2, system3, system4), first, last, stencil, out_true, out_false, pred);
} // end stable_partition_copy()

template <typename ForwardIterator, typename Predicate>
ForwardIterator partition_point(ForwardIterator first, ForwardIterator last, Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::partition_point");
  using thrust::system::detail::generic::select_system;

  using System = typename thrust::iterator_system<ForwardIterator>::type;

  System system;

  return thrust::partition_point(select_system(system), first, last, pred);
} // end partition_point()

template <typename InputIterator, typename Predicate>
bool is_partitioned(InputIterator first, InputIterator last, Predicate pred)
{
  _CCCL_NVTX_RANGE_SCOPE("thrust::is_partitioned");
  using thrust::system::detail::generic::select_system;

  using System = typename thrust::iterator_system<InputIterator>::type;

  System system;

  return thrust::is_partitioned(select_system(system), first, last, pred);
} // end is_partitioned()

THRUST_NAMESPACE_END
