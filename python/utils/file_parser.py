#!/usr/bin/env python3

from typing import (
    List,
    Tuple,
    Union
)

from utils.image import (
    ImageType,
    PackedImage,
    StrideImage,
)
from utils.pixel import (
    Pixel,
    parse_pixel,
)
from utils.resolution import Resolution
from utils.function_tracer import FunctionTracer

def read_by_token(fileobj):
    for line in fileobj:
        for token in line.split():
            yield int(token)
    
def generate_io_data(input_file_name: str, output_file_name: str, image_type: ImageType) -> \
    Tuple[List[Union[PackedImage, StrideImage]], List[Union[PackedImage, StrideImage]]]:
    ft = FunctionTracer("generate_io_data", "seconds //not included into solution timings")

    input_data = generate_data(input_file_name, image_type)
    #output_data = generate_data(output_file_name, image_type) 
    del ft
    
    return input_data, output_data
    

def generate_data(file_name: str, image_type: ImageType) -> List[PackedImage]:
    images: List[PackedImage] = []
    with open(file_name) as f:
        tokens = read_by_token(f)
        images_num: int = next(tokens)
        
        for i in range(images_num):
            ft = FunctionTracer(f"image{i}", "seconds")
            width: int = next(tokens)
            height: int = next(tokens)
            resolution: Resolution = Resolution(width, height)
            
            num_pixels: int = width*height
            pixels: List[Pixel] = []
            for _ in range(num_pixels):
                pixel_data: int = next(tokens)
                pixel: Pixel = parse_pixel(pixel_data)
                pixels.append(pixel)
            
            if image_type == ImageType.PackedImageType:
                packed_image: PackedImage = PackedImage(resolution, pixels)
                images.append(packed_image)
            else:
                stride_image: StrideImage = StrideImage(resolution, pixels)
                images.append(stride_image)
                
            del ft

    return images

def print_images(images: List[Union[PackedImage, StrideImage]]) -> None:
    for index, image in enumerate(images):
        print(f"\n image{index}")
        print(f"{image}")