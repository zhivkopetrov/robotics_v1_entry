#include <thread>

#include "Solution.h"
#include "utils/FunctionTracer.h"

void Solution::compute([[maybe_unused]]std::vector<PackedImage> &images) {
  FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
  //TODO: fill solution
}

void Solution::fixRedEye(StrideImage &img, uint32_t row, uint32_t col, EyePattern eyePattern) {
  for (uint32_t patternRow = 0; patternRow < EYE_PATTERN_COL_SIZE; ++patternRow) {
    for (uint32_t patternCol = 0; patternCol < EYE_PATTERN_COL_SIZE; ++patternCol) {
      if (eyePattern[patternRow][patternCol] != WHITESPACE_CHAR) {
        img.redPixels[(row + patternRow) * img.resolution.width + (col + patternCol)] -= RED_EYE_REDUCE;
      }
    }
  }
}

bool Solution::findPattern(StrideImage &img, uint32_t row, uint32_t col, EyePattern eyePattern) {
  for (uint32_t patternRow = 0; patternRow < EYE_PATTERN_COL_SIZE; ++patternRow) {
    for (uint32_t patternCol = 0; patternCol < EYE_PATTERN_COL_SIZE; ++patternCol) {
      if ((eyePattern[patternRow][patternCol] != WHITESPACE_CHAR) && (img.redPixels[(row + patternRow) * img.resolution.width + (col + patternCol)] < RED_EYE_THRESHOLD)) {
          return false;
      }
    }
  }

  return true;
}

void Solution::processImage(StrideImage &img) {
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

void Solution::compute([[maybe_unused]]std::vector<StrideImage> &images) {
  FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");

  std::vector<std::thread> threads;
  uint32_t thread_count = std::thread::hardware_concurrency();
  uint32_t image_count = images.size();
  uint32_t image_idx = 0;

  while (image_idx < (image_count - 1)) {
    if ((image_idx + thread_count) > image_count) {
        thread_count = image_count - image_idx;
    }

    for (uint32_t idx = 0; idx < thread_count; ++idx) {
      threads.push_back(std::thread(processImage, std::ref(images[image_idx + idx])));
    }

    for (uint32_t idx = image_idx; idx < image_idx + thread_count; ++idx) {
      threads[idx].join();
    }

    image_idx += thread_count;
  }
}
