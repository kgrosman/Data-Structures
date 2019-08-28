#include "Image.h"

void Image::darken() {
    Image::darken(0.1);

}
void Image::darken(double amount) {
    int height = this -> height();
    int width = this -> width();
    
for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
        cs225::HSLAPixel& pixel = this -> getPixel(i,j);
        pixel.l = ((0.0 < pixel.l - amount) ? pixel.l - amount: 0.0);
    }
}
}


void Image::lighten() {
Image::lighten(0.1);
}
void Image::lighten(double amount){
int height = this -> height();
    int width = this -> width();
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            cs225::HSLAPixel& pixel = this -> getPixel(i,j);
            pixel.l = ((1.0 > pixel.l + amount) ? pixel.l + amount : 1.0);
        }
    }

    
}

void Image::saturate(){
    Image::saturate(0.1);
}

void Image::saturate(double amount){ 
    int height = this -> height();
    int width = this -> width();
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            cs225::HSLAPixel& pixel = this -> getPixel(i,j);
            pixel.s = ((1.0 > pixel.s + amount) ? pixel.s + amount : 1.0);
        }
    }

}
void Image::desaturate(){
    Image::desaturate(0.1);
}
void Image::desaturate(double amount){
    int height = this -> height();
    int width = this -> width();
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            cs225::HSLAPixel& pixel = this -> getPixel(i,j);
            pixel.s = ((0.0 > pixel.s - amount) ? pixel.s - amount: 1.0);
        }
    }
}
void Image::grayscale(){
    int height = this -> height();
    int width = this -> width();
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            cs225::HSLAPixel& pixel = this -> getPixel(i,j);
            pixel.s = 0;
            
        }
    }

}
void Image::illinify() {
    int height = this -> height();
    int width = this -> width();
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            cs225::HSLAPixel& pixel = this -> getPixel(i,j);
            pixel.h = (pixel.h >= 113.5 && pixel.h <= 293.5) ? 216 : 11;
            
        }
    }

}
void Image::rotateColor(double degrees) {
    int height = this -> height();
    int width = this -> width();
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            cs225::HSLAPixel& pixel = this -> getPixel(i,j);
            pixel.h += degrees;
            if (pixel.h > 360.0) {
                while (pixel.h > 360.0) {
                    pixel.h -= 360.0;
                }

            }

            if (pixel.h < 0.0) {
                while (pixel.h < 0.0) {
                    pixel.h += 360.0;
                }
            }
            
        }
    }

}
void Image::scale (double factor) {

    double height = (double) this -> height();
    double width = (double) this -> width();
   
    unsigned newHeight = (unsigned) (height * factor);
    unsigned newWidth = (unsigned) (width * factor);
    Image::scale (newWidth, newHeight);

}
void Image::scale (unsigned w, unsigned h) {
    double height = this -> height();
    double width = this -> width();
    unsigned newHeight;
    unsigned newWidth;
    double dW = (double) w;
    double dH = (double) h;
    
    if (dW / dH > width / height) {
        newHeight = (unsigned) dH;
        newWidth = (unsigned) (dH * width) / height;
    } else {
    newHeight = (unsigned) (dW * height) / width;
    newWidth = (unsigned) dW;
    }
    
    Image scaled(newWidth, newHeight);
      

    for (unsigned i = 0; i < newWidth; i++) {
        for (unsigned j = 0; j < newHeight; j++) {
            cs225::HSLAPixel& newPixel = scaled.getPixel(i, j);
            double dI = (double) i;
            double dJ = (double) j;
            unsigned scaledI = (unsigned) (dI * width)/ newWidth;
            unsigned scaledJ = (unsigned) (dJ * height) / newHeight;

            cs225::HSLAPixel& OrigPixel = this -> getPixel(scaledI, scaledJ);
            newPixel.h = OrigPixel.h;
            newPixel.s = OrigPixel.s;
            newPixel.l = OrigPixel.l;
            newPixel.a = OrigPixel.a;
        }
    }
    
    *this = scaled;



}

Image::Image() : cs225::PNG::PNG(1000, 1000) {
    cornerX = 0;
    cornerY = 0;


 }

Image::Image(unsigned x, unsigned y) : cs225::PNG::PNG(x , y) {
    cornerX = 0;
    cornerY = 0;

}

Image::Image(Image& picture, unsigned x, unsigned y) : cs225::PNG::PNG((cs225::PNG) picture) {
    cornerX = x;
    cornerY = y;


}

