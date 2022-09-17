#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <cstdint>

#include "utils/Image.h"
#include "utils/EyePatterns.h"

class Solution {
private:
  static constexpr uint32_t RED_EYE_THRESHOLD = 200;
  static constexpr uint32_t RED_EYE_REDUCE = 150;
  static constexpr char WHITESPACE_CHAR = ' ';

  static void fixRedEye(StrideImage &img, uint32_t row, uint32_t col, EyePattern eyePattern);
  static bool findPattern(StrideImage &img, uint32_t row, uint32_t col, EyePattern eyePattern);
  static void processImage(StrideImage &img);

public:
  void compute([[maybe_unused]]std::vector<PackedImage> &images);
  void compute([[maybe_unused]]std::vector<StrideImage> &images);
};

#endif /* SOLUTION_H_ */
