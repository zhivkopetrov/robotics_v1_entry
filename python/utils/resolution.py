#!/usr/bin/env python3

class Resolution:
    def __init__(self, width: int, height: int):
        self.width: int = width
        self.height: int = height
    
    def __str__ (self):
        return '(' + str(self.width) + ', ' + str(self.height) + ')'

    def __eq__(self, other):
        return self.width == other.width and self.height == other.height