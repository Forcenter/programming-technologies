#ifndef CONSOLE_COMMANDS
#define CONSOLE_COMMANDS
#include <vector>
#include <string>
#include "base-structs.h"

namespace mitkov {
  double areaFunction(const std::vector< Polygon >& arr, const std::string& key);
  double maxAreaFunction(const std::vector< Polygon >& arr);
  size_t maxVertexesFunction(const std::vector< Polygon >& arr);
  double minAreaFunction(const std::vector< Polygon >& arr);
  size_t minVertexesFunction(const std::vector< Polygon >& arr);
  int countFunction(const std::vector< Polygon >& arr, const std::string& key);
  int rectsFunction(const std::vector< Polygon >& arr);
  bool inframeFunction(const std::vector< Polygon >& arr, const Polygon& pol);

  void processConsoleCommand(const std::string& command, std::istream& istream, const std::vector<Polygon>& arr, std::ostream& ostream);
}

#endif