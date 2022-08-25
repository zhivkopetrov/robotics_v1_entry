#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <cstdint>

#include "utils/Image.h"
#include "utils/FunctionTracer.h"

class Solution {
public:
  void compute([[maybe_unused]]std::vector<PackedImage> &images) {
    FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
    //TODO: fill solution
  }

  void compute([[maybe_unused]]std::vector<StrideImage> &images) {
    FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
    //TODO: fill solution
  }
};

#endif /* SOLUTION_H_ */
