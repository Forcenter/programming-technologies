#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>

#include "dataStructComp.h"
#include "basicStructs.h"
#include "ioOperators.h"

int main()
{
  std::vector<mitkov::dataStruct> data;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< mitkov::dataStruct >(std::cin),
      std::istream_iterator< mitkov::dataStruct >(),
      std::back_inserter(data)
    );
    if (std::cin.rdstate() == std::ios::failbit)
    {
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cin.clear();
    }
  }
  std::sort(data.begin(), data.end(), mitkov::compLess());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< mitkov::dataStruct >(std::cout, "\n")
  );
  return 0;
}