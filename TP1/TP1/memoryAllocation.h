#ifndef MEMORY_ALLOC_HPP
#define MEMORY_ALLOC_HPP

#include <memory>
#include <stdexcept>

namespace mitkov {
  template < class T >
  size_t enlargeArray(std::unique_ptr< std::unique_ptr< T >[] >& arr, size_t oldSize, size_t newSize)
  {
    if (newSize < oldSize) {
      throw std::logic_error("Tried to convert array to smaller");
    }
    std::unique_ptr< std::unique_ptr< T >[] > temp = std::make_unique< std::unique_ptr< T >[] >(newSize);

    for (size_t i = 0; i < oldSize; ++i) {
      temp[i].swap(arr[i]);
    }

    arr.swap(temp);
    return newSize;
  }
}

#endif