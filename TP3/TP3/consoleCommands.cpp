#include "consoleCommands.h"
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>
#include "inputOutputProcessing.h"
#include "consoleCommandsSubFunctions.h"

double mitkov::areaFunction(const std::vector<Polygon>& arr, const std::string& key)
{
  std::vector< Polygon > sorted(0);
  double koef = 1;

  bool flag = true;

  if (key == "MEAN") {
    sorted = arr;
    koef = sorted.size();
    if (!koef) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    flag = false;
  }

  using namespace std::placeholders;
  if (key == "EVEN") {
    if (arr.size() == 0) {
      return 0.0;
    }
    std::function< bool(const Polygon&) > hasEvenVertexesAmount = std::bind(std::logical_not< bool >(), std::bind(hasOddVertexesAmount, _1));
    std::copy_if(arr.begin(), arr.end(), std::back_inserter(sorted), hasEvenVertexesAmount);
  }
  if (key == "ODD") {
    if (arr.size() == 0) {
      return 0.0;
    }
    std::function< bool(const Polygon&) > hasOddVertAmount = std::bind(hasOddVertexesAmount, _1);
    std::copy_if(arr.begin(), arr.end(), std::back_inserter(sorted), hasOddVertAmount);
  }
  if (sorted.size() == 0) {
    size_t vertAmount = std::stoul(key);
    if (vertAmount <= 2) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    std::function< bool(const Polygon&) > func = std::bind(hasNVertexes, _1, vertAmount);
    std::copy_if(arr.begin(), arr.end(), std::back_inserter(sorted), func);
  }
  return std::accumulate(sorted.begin(), sorted.end(), 0.0, std::bind(getArea, _1, _2)) / koef;
}

double mitkov::maxAreaFunction(const std::vector<Polygon>& arr)
{
  if (arr.size() == 0) {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  return getArea(0.0, *std::max_element(arr.begin(), arr.end(), std::bind(isAreaSmaller, _1, _2)));
}

size_t mitkov::maxVertexesFunction(const std::vector<Polygon>& arr)
{
  using namespace std::placeholders;
  return std::max_element(arr.begin(), arr.end(), std::bind(hasLessVertexes, _1, _2))->points.size();
}

double mitkov::minAreaFunction(const std::vector<Polygon>& arr)
{
  if (arr.size() == 0) {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  return getArea(0.0, *std::min_element(arr.begin(), arr.end(), std::bind(isAreaSmaller, _1, _2)));
}

size_t mitkov::minVertexesFunction(const std::vector<Polygon>& arr)
{
  using namespace std::placeholders;
  return std::min_element(arr.begin(), arr.end(), std::bind(hasLessVertexes, _1, _2))->points.size();
}

int mitkov::countFunction(const std::vector<Polygon>& arr, const std::string& key)
{
  if (key == "EVEN") {
    using namespace std::placeholders;
    return std::count_if(arr.begin(), arr.end(), std::bind(std::logical_not< bool >{}, std::bind(hasOddVertexesAmount, _1)));
  }
  if (key == "ODD") {
    return std::count_if(arr.begin(), arr.end(), hasOddVertexesAmount);
  }
  size_t vertAmount = std::stoul(key);
  if (vertAmount <= 2) {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  return std::count_if(arr.begin(), arr.end(), std::bind(hasNVertexes, _1, vertAmount));
}

int mitkov::rectsFunction(const std::vector<Polygon>& arr)
{
  return count_if(arr.begin(), arr.end(), isRect);
}

bool mitkov::inframeFunction(const std::vector<Polygon>& arr, const Polygon& pol)
{
  int frameX = arr[0].points[0].x;
  int frameY = arr[0].points[0].y;
  int frameWidth = 0;
  int frameHeight = 0;

  using namespace std::placeholders;
  frameX = std::accumulate(arr.begin(), arr.end(), 0, std::bind(getMinPolygonX, _1, _2));
  frameY = std::accumulate(arr.begin(), arr.end(), 0, std::bind(getMinPolygonY, _1, _2));
  frameWidth = std::accumulate(arr.begin(), arr.end(), 0, std::bind(getMaxPolygonX, _1, _2)) - frameX;
  frameHeight = std::accumulate(arr.begin(), arr.end(), 0, std::bind(getMaxPolygonY, _1, _2)) - frameY;

  auto condition = std::bind(isPointInframe, _1, frameX, frameY, frameWidth, frameHeight);
  return static_cast< long unsigned int >(std::count_if(pol.points.begin(), pol.points.end(), condition)) == pol.points.size();
}

using vect = std::vector< mitkov::Polygon >;
using str = std::string;
void mitkov::processConsoleCommand(const str& command, std::istream& istream, const vect& arr, std::ostream& ostream)
{
  const char* INVALID_COMMAND_ERROR = "<INVALID COMMAND>";
  if (command == "AREA") {
    std::string key;
    istream >> key;
    ostream.precision(1);
    ostream << std::fixed << areaFunction(arr, key) << std::endl;
    return;
  }
  if (command == "MAX") {
    std::string key;
    istream >> key;

    if (arr.size() == 0) {
      throw std::invalid_argument(INVALID_COMMAND_ERROR);
    }

    if (key == "AREA") {
      ostream.precision(1);
      ostream << std::fixed << maxAreaFunction(arr) << std::endl;
      return;
    }
    if (key == "VERTEXES") {
      ostream << maxVertexesFunction(arr) << std::endl;
      return;
    }
    throw std::invalid_argument(INVALID_COMMAND_ERROR);
  }
  if (command == "MIN") {
    std::string key;
    istream >> key;
    if (key == "AREA") {
      ostream.precision(1);
      ostream << std::fixed << minAreaFunction(arr) << std::endl;
      return;
    }
    if (key == "VERTEXES") {
      ostream << minVertexesFunction(arr) << std::endl;
      return;
    }
    throw std::invalid_argument(INVALID_COMMAND_ERROR);
  }
  if (command == "COUNT") {
    std::string key;
    istream >> key;
    ostream << countFunction(arr, key) << std::endl;
    return;
  }
  if (command == "RECTS") {
    ostream << rectsFunction(arr) << '\n';
    return;
  }
  if (command == "INFRAME") {
    std::string pol;
    std::getline(istream, pol);
    Polygon key = getPolygonFromLine(pol);
    if (!std::cin || key.points.size() == 0) {
      throw std::invalid_argument(INVALID_COMMAND_ERROR);
    }
    if (inframeFunction(arr, key)) {
      ostream << "<TRUE>\n";
    }
    else {
      ostream << "<FALSE>\n";
    }
    return;
  }
  throw std::invalid_argument(INVALID_COMMAND_ERROR);
}