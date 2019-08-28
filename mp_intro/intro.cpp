#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <cmath>



void rotate(std::string inputFile, std::string outputFile) {
 cs225::PNG input;
 input.readFromFile(inputFile);
 
 cs225::PNG result(input.width(), input.height());


 for (unsigned int x = 0; x < input.width(); x++) {
     for (unsigned int y = 0; y < input.height(); y++) {
        cs225::HSLAPixel& respixel = result.getPixel(x, y);
        cs225::HSLAPixel& inpixel = input.getPixel(input.width() - x - 1, input.height() - y - 1);

        respixel.h = inpixel.h;
        respixel.s = inpixel.s;
        respixel.l = inpixel.l;
        respixel.a = inpixel.a;
     }
 }

 result.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
    for (unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < height; y++) {
            cs225::HSLAPixel& pixel = png.getPixel(x, y);
            
            
            
            
            pixel.l = 0.7;
            pixel.s = 0.7;
            pixel.a = ((double) x*x + y*y)  / (((double) width*width) + ((double) height*height));
            pixel.h =  ((double) (x + y) * 360.0) / ((double) width + height);
        }
    }


  return png;
}


