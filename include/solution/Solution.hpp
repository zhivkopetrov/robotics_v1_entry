#ifndef RED_EYE_SOLUTION_SOLUTION
#define RED_EYE_SOLUTION_SOLUTION

#include <cstdint>

#include "utils/Image.hpp"

class Solution {
public:
  void compute(std::vector<PackedImage> &images);
  void compute(std::vector<StrideImage> &images);
};

#endif // RED_EYE_SOLUTION_SOLUTION
