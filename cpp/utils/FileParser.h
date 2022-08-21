#ifndef FILEPARSER_H_
#define FILEPARSER_H_

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "CommonDefines.h"
#include "FunctionTracer.h"

namespace {
void clearValues(std::string &line, std::istringstream &istr) {
  line.clear();
  istr.clear();
  istr.str("");
}
}

template <typename T>
class FileParser {
public:
  FileParser() = delete;

  static int32_t generateData(std::vector<T> &outInputData,
                              std::vector<T> &outOutputData) {
    FunctionTracer<std::chrono::milliseconds> tracer(__func__,
        "ms //not included into solution timings");

    constexpr auto inputFile = "input.bin";
    int32_t err = FileParser<T>::parseFile(inputFile, outInputData);
    if (EXIT_SUCCESS != err) {
      std::cerr << "FileParser::parseFile() failed for file: " << inputFile
                << std::endl;
      return EXIT_FAILURE;
    }

    constexpr auto outputFile = "output.bin";
    err = FileParser<T>::parseFile(outputFile, outOutputData);
    if (EXIT_SUCCESS != err) {
      std::cerr << "FileWritter::generateFile() failed for file: " << inputFile
                << std::endl;
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  static int32_t parseFile(const std::string &fileLocation,
                           std::vector<T> &outData) {
    std::ifstream ifstream(fileLocation, std::ios::in | std::ios::binary);
    if (!ifstream) {
      std::cout << "Error, could not load file: " << fileLocation << std::endl;
      return EXIT_FAILURE;
    }

    std::string line;
    std::getline(ifstream, line);
    std::istringstream istr(line);

    int32_t itemsCount = 0;
    istr >> itemsCount;

    outData.reserve(itemsCount);
    clearValues(line, istr);

    Resolution res;
    for (int32_t i = 0; i < itemsCount; ++i) {
      std::getline(ifstream, line);
      istr.str(line);

      //parse resolution
      istr >> res.width >> res.height;
      clearValues(line, istr);

      //create item
      T &item = outData.emplace_back(res);

      std::getline(ifstream, line);
      istr.str(line);

      //fill item data
      istr >> item;

      clearValues(line, istr);
    }

    return EXIT_SUCCESS;
  }
};

#endif /* FILEPARSER_H_ */
