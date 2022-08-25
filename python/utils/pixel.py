#!/usr/bin/env python3

class Pixel:
    def __init__(self, red: int, green: int, blue: int, alpha: int):
        self.red: int = red
        self.green: int = green
        self.blue: int = blue
        self.alpha: int = alpha

    def __str__ (self):
        return '(' + str(self.red) + ', ' + str(self.green) + ', ' + str(self.blue) + ', ' + str(self.alpha) + ')'

    def __eq__(self, other):
        return self.red == other.red and self.green == other.green and \
            self.blue == other.blue and self.alpha == other.alpha

def parse_pixel(dataRGBA: int) -> Pixel:
    red: int = (dataRGBA & 0xFF000000) >> 24
    green: int = (dataRGBA & 0x00FF0000) >> 16
    blue: int = (dataRGBA & 0x0000FF00) >> 8
    alpha: int = (dataRGBA & 0x000000FF)
    return Pixel(red, green, blue, alpha)