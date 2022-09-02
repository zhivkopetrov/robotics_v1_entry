#ifndef RED_EYE_UTILS_IMAGE
#define RED_EYE_UTILS_IMAGE

#include <cstdint>
#include <vector>
#include <iosfwd>

#include "CommonDefines.hpp"

struct PackedImage {
  PackedImage(const Resolution& res);

  bool operator==(const PackedImage& other) const;
  friend std::istream& operator>>(std::istream& istream, PackedImage& img);

  Resolution resolution;
  std::vector<Pixel> pixels;
};

struct StrideImage {
  StrideImage(const Resolution& res);

  bool operator==(const StrideImage& other) const;
  friend std::istream& operator>>(std::istream& istream, StrideImage& img);

  Resolution resolution;
  std::vector<uint8_t> redPixels;
  std::vector<uint8_t> greenPixels;
  std::vector<uint8_t> bluePixels;
  std::vector<uint8_t> alphaPixels;
};

#endif // RED_EYE_UTILS_IMAGE
