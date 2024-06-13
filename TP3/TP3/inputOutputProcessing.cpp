#include "inputOutputProcessing.h"
#include <algorithm>
#include <iterator>
#include <istream>
#include <iostream>
#include <string>

mitkov::Polygon mitkov::getPolygonFromLine(std::string line) {
  std::string word = getWord(line);
  int vertexAmount;
  try {
    vertexAmount = std::stoi(word);
    if (vertexAmount < 3) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  catch (...) {
    return Polygon();
  }
  Polygon result;
  for (int i = 0; i < vertexAmount; ++i) {
    try {
      result.points.push_back(getPointFromWord(getWord(line)));
    }
    catch(...){
      return Polygon();
    }
  }
  if (line.size() != 0) {
    return Polygon{};
  }
  return result;
}

mitkov::Point mitkov::getPointFromWord(const std::string& word) {
  static const char* INVALID_COMMAND_ERROR = "<INVALID COMMAND>";
  size_t semicolon = word.find(';', 1);
  if (word[0] != '(' || semicolon == word.npos) {
    throw std::invalid_argument(INVALID_COMMAND_ERROR);
  }
  int a;
  try {
    a = std::stoi(word.substr(1, semicolon - 1));
  }
  catch(...){
    throw std::invalid_argument(INVALID_COMMAND_ERROR);
  }
  size_t parenthesis = word.find(')', semicolon + 1);
  if (parenthesis == word.npos) {
    throw std::invalid_argument(INVALID_COMMAND_ERROR);
  }
  int b;
  try {
    b = std::stoi(word.substr(semicolon + 1, parenthesis - semicolon - 1));
  }
  catch(...) {
    throw std::invalid_argument(INVALID_COMMAND_ERROR);
  }
  return Point{ a, b };
}

std::string mitkov::getWord(std::string& source) {
  std::string result;
  size_t pos = source.find(' ');
  if (pos == source.npos) {
    result = source;
    source = "";
    return result;
  }
  result = source.substr(0, pos);
  source.erase(0, pos + 1);
  return result;
}

