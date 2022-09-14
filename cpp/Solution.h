#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <cstdint>
#include <thread>

#include "utils/Image.h"
#include "utils/EyePatterns.h"
#include "utils/FunctionTracer.h"

class Solution {
private:
  static constexpr uint32_t RED_EYE_THRESHOLD = 200;
  static constexpr uint32_t RED_EYE_REDUCE = 150;
  static constexpr char WHITESPACE_CHAR = ' ';

public:
  void compute([[maybe_unused]]std::vector<PackedImage> &images) {
    FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
    //TODO: fill solution
  }

  static void fixRedEye(StrideImage &img, uint32_t row, uint32_t col, EyePattern eyePattern) {
    for (uint32_t patternRow = 0; patternRow < EYE_PATTERN_COL_SIZE; ++patternRow) {
      for (uint32_t patternCol = 0; patternCol < EYE_PATTERN_COL_SIZE; ++patternCol) {
        if (eyePattern[patternRow][patternCol] != WHITESPACE_CHAR) {
          img.redPixels[(row + patternRow) * img.resolution.width + (col + patternCol)] -= RED_EYE_REDUCE;
        }
      }
    }
  }

  static bool findPattern(StrideImage &img, uint32_t row, uint32_t col, EyePattern eyePattern) {
    for (uint32_t patternRow = 0; patternRow < EYE_PATTERN_COL_SIZE; ++patternRow) {
      for (uint32_t patternCol = 0; patternCol < EYE_PATTERN_COL_SIZE; ++patternCol) {
        if ((eyePattern[patternRow][patternCol] != WHITESPACE_CHAR) && (img.redPixels[(row + patternRow) * img.resolution.width + (col + patternCol)] < RED_EYE_THRESHOLD)) {
            return false;
        }
      }
    }

    return true;
  }

  static void processImage(StrideImage &img) {
    for (uint32_t row = 0; row <= static_cast<uint32_t>(img.resolution.height - EYE_PATTERN_COL_SIZE); ++row) {
      for (uint32_t col = 0; col <= static_cast<uint32_t>(img.resolution.width - EYE_PATTERN_COL_SIZE); ++col) {
        for (int32_t idx = EYE_PATTERNS.size() - 1; idx >=0; --idx) {
          if (findPattern(img, row, col, EYE_PATTERNS[idx])) {
            fixRedEye(img, row, col, EYE_PATTERNS[idx]);
          }
        }
      }
    }
  }

  void compute([[maybe_unused]]std::vector<StrideImage> &images) {
    FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");

    std::vector<std::thread> threads;

    for (uint32_t idx = 0; idx < images.size(); ++idx) {
      threads.push_back(std::thread(processImage, std::ref(images[idx])));
    }

    for (uint32_t idx = 0; idx < images.size(); ++idx) {
      threads[idx].join();
    }
  }
};

#endif /* SOLUTION_H_ */
