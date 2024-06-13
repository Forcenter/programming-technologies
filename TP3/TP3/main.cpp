#include <iostream>
#include <iterator>
#include <limits>
#include <fstream>
#include <sstream>
#include "base-structs.h"
#include "consoleCommands.h"
#include "inputOutputProcessing.h"

int main(int argc, char* argv[])
{
  std::ifstream fin;
  /*if (argc != 2) {
    std::cerr << "too many arguments";
    return 2;
  }
  fin.open(argv[1]);
  if (!fin.is_open()) {
    std::cerr << "unable to open the file";
    return 1;
  }*/

  fin.open("a.txt");

  std::vector< mitkov::Polygon > shapes;

  while (!fin.eof()) {
    std::string commandLine;
    std::getline(fin, commandLine);
    mitkov::Polygon pol = mitkov::getPolygonFromLine(commandLine);
    if (pol.points.size() > 0) {
      shapes.push_back(pol);
    }
  }

  while (!std::cin.eof()) {
    try {
      std::string command;
      std::cin >> command;
      if (command.size() != 0) {
        mitkov::processConsoleCommand(command, std::cin, shapes, std::cout);
      }
    }
    catch (const std::invalid_argument& err) {
      std::cout << err.what() << '\n';
      if (!std::cin.eof()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
  }
}