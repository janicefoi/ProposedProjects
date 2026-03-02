# Image-processor

This project is a part of learning to code with C++. This is a console app to edit pictures in 24-bit BMP format.

## Format of command line arguments

Here is the description of command line arguments:
{program name} {path to input file} {path to output file}
[-{filter name 1} [filter parameter 1] [filter parameter 2] ...]
[-{filter name 1} [filter parameter 1] [filter parameter 2] ...] ...`


### Example

ImageProcessor parrots.bmp parrotsgs.bmp -gs will convert the input color (24-bit BMP format) parrots.bmp into a B&W (grayscale) image parrotsgs.bmp 

image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs

In this example:
1. The image is downloaded from the file `input.bmp`
2. The image is cropped to a rectangle 800х600 pixels in the upper left corner
3. The image is converted to grayscale
4. The resulting image is saved to the file /tmp/output.bmp

## Filters
In the formulas, we further assume that each color component is represented by a real number from 0 to 1. Pixel colors are represented by triples (R, G, B). Thus, (0, 0, 0) – black, (1, 1, 1) – white.


If the filter is set by a matrix, it means that the value of each of the colors is determined by the weighted sum of the values of this color in neighboring pixels in accordance with the matrix. In this case, the target pixel corresponds to the central element of the matrix.

For example, for a filter given by a matrix

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D1%20&%202%20&%203%20%5C%5C4%20&%205%20&%206%20%5C%5C7%20&%208%20&%209%20%5C%5C%5Cend%7Bbmatrix%7D)

The value of each of the colors of the target pixel `C[x][y]` will be determined by the formula

```
C[x][y] =
  min(1, max(0,
   1*C[x-1][y-1] + 2*C[x][y-1] + 3*C[x+1][y-1] +
   4*C[x-1][y]   + 5*C[x][y]   + 6*C[x+1][y]   +
   7*C[x-1][y+1] + 8*C[x][y+1] + 9*C[x+1][y+1]
))
```

When processing pixels close to the edge of the image, part of the matrix may extend beyond the image boundary. In this case, we will use the value of the image pixel closest to it as the value of the pixel that goes beyond the border.

### The list of the filters:

The picture: 

![image](https://user-images.githubusercontent.com/129896942/230489934-6b4ff9a9-bac1-42ad-8d97-4f0ff67a2754.png)


#### Crop (-crop width height)
Crops the image to the specified width and height. The upper left part of the image is used.

If the requested width or height exceeds the dimensions of the original image, the available part of the image is given.

Example: -crop 500 500


![image](https://user-images.githubusercontent.com/129896942/230487448-fc73d782-a989-4534-be54-cada3d87f148.png)



#### Grayscale (-gs)
Converts the image to grayscale using the formula

![encoding](https://latex.codecogs.com/svg.image?R'%20=%20G'%20=%20B'%20=0.299%20R%20&plus;%200%20.587%20G%20&plus;%200%20.%20114%20B)

Example: -gs


![image](https://user-images.githubusercontent.com/129896942/230487268-33e51fe8-7772-40cb-8903-2dca5db792cf.png)



#### Negative (-neg)
Converts an image to a negative using the formula

Example: -neg


![image](https://user-images.githubusercontent.com/129896942/230487624-02258dc0-c9e7-427a-a7ef-aaedf8f19de6.png)



#### Sharpening (-sharp)
Sharpening. It is applied by using a matrix

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%205%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

Example: -sharp

![image](https://user-images.githubusercontent.com/129896942/230488644-a6466a98-38d7-4f14-a65d-795da9c97f94.png)



#### Edge Detection (-edge threshold)
Border selection. The image is converted to grayscale and a matrix is applied

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%204%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

Pixels with a value exceeding the threshold are colored white, the rest are black.

Example: -edge 0.1

![image](https://user-images.githubusercontent.com/129896942/230488967-d9c5f09a-6700-48da-83ce-fd726875ed66.png)



### Pinky (-mine)

Makes the picture glamourous.

Example: -mine

![image](https://user-images.githubusercontent.com/129896942/230489475-488db054-047f-48ff-9af9-777196426cf8.png)




