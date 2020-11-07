/**
 * @file MemoryPool.h
 * @author simin tao (taosm@pcl.ac.cn)
 * @brief
 * @version 0.1
 * @date 2020-11-07
 *
 * @copyright Copyright (c) 2020 PCL EDA
 */

#pragma once

#include "boost/pool/object_pool.hpp"
#include "boost/pool/poolfwd.hpp"

namespace pcl {

/**
 * @brief A memory pool for store object.It is a wrapper of boost::object_pool.
 * The memory pool can reduce the memory allocate and deallocate time and
 * improve the memory usage.
 *
 * @tparam T object type.
 */
template <typename T>
class ObjectPool
    : public boost::object_pool<T, boost::default_user_allocator_new_delete> {
 public:
  using Base = typename ObjectPool::object_pool;
  using size_type = typename Base::size_type;
  using difference_type = typename Base::difference_type;
  using element_type = T;

  /*constructor and destructor*/
  using Base::Base;
  ~ObjectPool() = default;

  /*construct the object*/
  using Base::construct;

  /*destory the object*/
  using Base::destroy;
};

}  // namespace pcl
