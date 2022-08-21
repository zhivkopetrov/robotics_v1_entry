#include "Image.h"

#include <fstream>
#include <iostream>

namespace {
Pixel parsePixel(uint32_t inputRgba) {
  Pixel px;
  px.red = static_cast<uint8_t>( (inputRgba & 0xFF000000) >> 24);
  px.green = static_cast<uint8_t>( (inputRgba & 0x00FF0000) >> 16);
  px.blue = static_cast<uint8_t>( (inputRgba & 0x0000FF00) >> 8);
  px.alpha = static_cast<uint8_t>( (inputRgba & 0x000000FF));
  return px;
}
}

PackedImage::PackedImage(const Resolution &res)
    : resolution(res), pixels(res.width * res.height) {

}

bool PackedImage::operator==(const PackedImage &other) const {
  return (resolution == other.resolution) && (pixels == other.pixels);
}

std::istream& operator>>(std::istream &istream, PackedImage &img) {
  uint32_t pixelValue = 0;
  for (Pixel &pixel : img.pixels) {
    istream >> pixelValue;
    pixel = parsePixel(pixelValue);
  }

  return istream;
}

StrideImage::StrideImage(const Resolution &res)
    : resolution(res), redPixels(res.width * res.height),
      greenPixels(res.width * res.height), bluePixels(res.width * res.height),
      alphaPixels(res.width * res.height) {

}

bool StrideImage::operator==(const StrideImage &other) const {
  return (resolution == other.resolution) &&
         (redPixels == other.redPixels) &&
         (greenPixels == other.greenPixels) &&
         (bluePixels == other.bluePixels) &&
         (alphaPixels == other.alphaPixels);
}

std::istream& operator>>(std::istream &istream, StrideImage &img) {
  const int32_t totalPixels = img.resolution.width * img.resolution.height;
  uint32_t pixelValue = 0;
  Pixel currPixel;
  for (int32_t i = 0; i < totalPixels; ++i) {
    istream >> pixelValue;
    currPixel = parsePixel(pixelValue);
    img.redPixels[i] = currPixel.red;
    img.greenPixels[i] = currPixel.red;
    img.bluePixels[i] = currPixel.red;
    img.alphaPixels[i] = currPixel.red;
  }

  return istream;
}

