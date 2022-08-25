#!/usr/bin/env python3

from typing import List
from utils.resolution import Resolution
from utils.pixel import Pixel
from enum import Enum

class ImageType(Enum):
    PackedImageType = 0
    StrideImageType = 1

class PackedImage:
    def __init__(self, resolution: Resolution, pixels: List[Pixel]):
        self.resolution: Resolution = resolution
        self.pixels: List[Pixel] = pixels
    
    def __str__ (self):
        return str(self.resolution) + '\n' + ' '.join(str(p) for p in self.pixels)

    def __eq__(self, other):
        return self.resolution == other.resolution and self.pixels == other.pixels

class StrideImage:
    def __init__(self, resolution: Resolution, pixels: List[Pixel]):
        self.resolution: Resolution = resolution
        self.pixels_red: List[int] = []
        self.pixels_green: List[int] = []
        self.pixels_blue: List[int] = []
        self.pixels_alpha: List[int] = []
        
        self.__split_pixel_components(pixels)

    def merge_pixel_components(self) -> List[Pixel]:
        pixels: List[Pixel] = []
        for i in range(len(self.pixels_red)):
            red: int = self.pixels_red[i]
            green: int = self.pixels_green[i]
            blue: int = self.pixels_blue[i]
            alpha: int = self.pixels_alpha[i]
            pixel: Pixel = Pixel(red, green, blue, alpha)
            pixels.append(pixel)
        return pixels
    
    def __split_pixel_components(self, pixels: List[Pixel]):
        for pixel in pixels:
            self.pixels_red.append(pixel.red)
            self.pixels_green.append(pixel.green)
            self.pixels_blue.append(pixel.blue)
            self.pixels_alpha.append(pixel.alpha)
    
    def __str__ (self):
        return str(self.resolution) + '\n' + \
            ' '.join(str(p) for p in self.pixels_red) + \
            ' '.join(str(p) for p in self.pixels_green) + \
            ' '.join(str(p) for p in self.pixels_blue) + \
            ' '.join(str(p) for p in self.pixels_alpha)

    def __eq__(self, other):
        return self.resolution == other.resolution and \
            self.pixels_red == other.pixels_red and \
            self.pixels_green == other.pixels_green and \
            self.pixels_blue == other.pixels_blue and \
            self.pixels_alpha == other.pixels_alpha

def to_stride_image(image: PackedImage) -> StrideImage:
    return StrideImage(image.resolution, image.pixels)

def to_image(stride_image: StrideImage) -> PackedImage:
    return PackedImage(stride_image.resolution, stride_image.merge_pixel_components())