#ifndef READERS_HPP
#define READERS_HPP

#include <complex>
#include <string>
#include <iosfwd>

namespace mitkov
{
  struct ullIO {
    unsigned long long& value;
  };
  struct complexIO {
    std::complex< double >& value;
  };
  struct stringIO {
    std::string& value;
  };
  struct dataStruct
  {
    unsigned long long key1;
    std::complex< double > key2;
    std::string key3;
  };
}

#endif