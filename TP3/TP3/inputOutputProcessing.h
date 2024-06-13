#ifndef INPUT_OUTPUT_PROC
#define INPUT_OUTPUT_PROC
#include <ios>
#include "base-structs.h"
#include "delimeter.h"

namespace mitkov {
  Polygon getPolygonFromLine(std::string line);
  Point getPointFromWord(const std::string& word);

  std::string getWord(std::string& source);
}

#endif