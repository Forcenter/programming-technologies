#include <iostream>
#include "Rectangle.h"
#include "Polygon.h"
#include "Diamond.h"
#include "memoryAllocation.h"
#include "pointOperations.h"

namespace mitkov {
  size_t getNumAmountInStr(const std::string& str) {
    size_t i = 0;
    while (str[i] == ' ') {
      ++i;
    }
    size_t result = 0;
    for (i = i; i < str.size(); ++i) {
      if (str[i] == ' ') {
        ++result;
      }
    }
    ++result;

    return result;
  }

  mitkov::point_t getPointFromStr(std::string& str) {
    if (*str.begin() == ' ')
      str.erase(str.begin());
    std::string localStr = str.substr(0, str.find(' '));

    double x = std::stod(localStr);
    str.erase(0, str.find(' ') + 1);
    localStr = str.substr(0, str.find(' '));
    double y = std::stod(localStr);
    str.erase(0, str.find(' ') + 1);
    return point_t{ x, y };
  }
}

int main()
{
  std::unique_ptr< std::unique_ptr< mitkov::Shape >[] > arr;
  size_t arrSize = 2;
  mitkov::enlargeArray(arr, 0, arrSize);
  size_t arrFilledSize = 0;

  std::cout.precision(1);

  bool scaleWasApplied = false;

  while (!std::cin.eof()) {
    try {
      std::string str = "";
      std::cin >> str;

      const std::string NOT_ENOUGH_DATA_ERROR = "Input string had not enough data to create shape";
      const std::string WRONG_DATA_FORMAT_ERROR = "Input line was in incorrect format";

      if (str == "RECTANGLE") {
        std::getline(std::cin, str);

        size_t pointAmount = mitkov::getNumAmountInStr(str);
        if (pointAmount % 2 != 0) {
          throw std::invalid_argument(WRONG_DATA_FORMAT_ERROR);
        }
        pointAmount /= 2;
        if (pointAmount != 2) {
          throw std::invalid_argument(NOT_ENOUGH_DATA_ERROR);
        }

        mitkov::point_t first;
        mitkov::point_t second;

        first = mitkov::getPointFromStr(str);
        second = mitkov::getPointFromStr(str);

        if (first.x > second.x || first.y > second.y) {
          throw std::invalid_argument("Input points were placed in wrong order");
        }

        arr[arrFilledSize++] = std::make_unique< mitkov::Rectangle >(first, second);
        if (arrFilledSize == arrSize) {
          arrSize = enlargeArray(arr, arrSize, arrSize * 3 / 2);
        }
        continue;
      }

      if (str == "DIAMOND") {
        std::getline(std::cin, str);

        size_t pointAmount = mitkov::getNumAmountInStr(str);
        if (pointAmount % 2 != 0) {
          throw std::invalid_argument(WRONG_DATA_FORMAT_ERROR);
        }
        pointAmount /= 2;
        if (pointAmount != 3) {
          throw std::invalid_argument(NOT_ENOUGH_DATA_ERROR);
        }

        mitkov::point_t first;
        mitkov::point_t second;
        mitkov::point_t third;

        first = mitkov::getPointFromStr(str);
        second = mitkov::getPointFromStr(str);
        third = mitkov::getPointFromStr(str);

        arr[arrFilledSize] = std::make_unique< mitkov::Diamond >(first, second, third);
        ++arrFilledSize;

        if (arrFilledSize == arrSize) {
          arrSize = enlargeArray(arr, arrSize, arrSize * 3 / 2);
        }
        continue;
      }

      if (str == "POLYGON") {
        std::getline(std::cin, str);

        size_t pointAmount = mitkov::getNumAmountInStr(str);
        if (pointAmount % 2 != 0) {
          throw std::invalid_argument(WRONG_DATA_FORMAT_ERROR);
        }
        pointAmount /= 2;
        if (pointAmount < 3) {
          throw std::invalid_argument(NOT_ENOUGH_DATA_ERROR);
        }

        std::unique_ptr< mitkov::point_t[] > ptr = std::make_unique< mitkov::point_t[] >(pointAmount);

        for (size_t i = 0; i < pointAmount; ++i) {
          ptr[i] = mitkov::getPointFromStr(str);
        }

        for (size_t i = 0; i < pointAmount; ++i) {
          for (size_t j = i + 1; j < pointAmount; ++j) {
            if (ptr[i].x == ptr[j].x && ptr[i].y == ptr[j].y) {
              throw std::invalid_argument("Same points in the definition of Polygon");
            }
          }
        }

        arr[arrFilledSize++] = std::make_unique< mitkov::Polygon >(std::move(ptr), pointAmount);
        if (arrFilledSize == arrSize) {
          arrSize = enlargeArray(arr, arrSize, arrSize * 3 / 2);
        }
        continue;
      }

      if (str == "SCALE") {
        std::getline(std::cin, str);

        mitkov::point_t center = mitkov::getPointFromStr(str);
        double ratio = std::stod(str);

        if (ratio <= 0) {
          throw std::logic_error("Scale ratio was not positive");
          return 1;
        }

        if (arrFilledSize == 0) {
          throw std::logic_error("Scale was applied to nothing");
          return 1;
        }

        double area = 0;

        for (size_t i = 0; i < arrFilledSize; ++i) {
          area += arr[i]->getArea();
        }

        std::cout << std::fixed << area;

        std::pair< mitkov::point_t, mitkov::point_t > pointPair;
        for (size_t i = 0; i < arrFilledSize; ++i) {
          pointPair = mitkov::getPointsOfRectangle(arr[i]->getFrameRect());
          std::cout << std::fixed << ' ' << pointPair.first << ' ' << pointPair.second;
          mitkov::point_t newCenter = arr[i]->getFrameRect().pos;
          arr[i]->move(center);
          mitkov::point_t oldCenter = arr[i]->getFrameRect().pos;
          arr[i]->scale(ratio);
          arr[i]->move((newCenter.x - oldCenter.x) * ratio, (newCenter.y - oldCenter.y) * ratio);
        }

        area = 0;

        for (size_t i = 0; i < arrFilledSize; ++i) {
          area += arr[i]->getArea();
        }

        std::cout << std::endl << std::fixed << area;

        for (size_t i = 0; i < arrFilledSize; ++i) {
          pointPair = mitkov::getPointsOfRectangle(arr[i]->getFrameRect());
          std::cout << std::fixed << ' ' << pointPair.first << ' ' << pointPair.second;
        }
        std::cout << std::endl;

        scaleWasApplied = true;

        break;
      }
      std::getline(std::cin, str);
    }
    catch (const std::invalid_argument& err) {
      std::cerr << err.what() << '\n';
    }
    catch (const std::logic_error& err) {
      std::cerr << err.what() << '\n';
      return 1;
    }
  }
  if (!scaleWasApplied) {
    std::cerr << "Program should end with SCALE function";
    return 1;
  }
  return 0;
}