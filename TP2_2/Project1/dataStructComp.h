#ifndef DATA_STRUCT_COMPARE_HPP
#define DATA_STRUCT_COMPARE_HPP

#include "basicStructs.h"

namespace mitkov
{
  struct compLess
  {
    bool operator()(const dataStruct& lhs, const dataStruct& rhs);
  };
}

#endif