#include <iostream>
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "Image.h"

#include <iostream>
using cs225::HSLAPixel;
    StickerSheet::StickerSheet(const Image& picture, unsigned max) {
        basePicture = picture;
        allStickers = new Image*[max];
        for (unsigned i = 0; i < max; i++) {
            allStickers[i] = NULL;
        }
        size = max;
        numStickers = 0;
    }
        
    
    StickerSheet::StickerSheet(const StickerSheet& other) {
        StickerSheet::copy_(other);
    }
    StickerSheet::~StickerSheet() {
        StickerSheet::delete_();
        
    }

    const StickerSheet& StickerSheet::operator=(const StickerSheet& other) {
        StickerSheet::delete_();
        StickerSheet::copy_(other);
        return *this;
    }

    void StickerSheet::changeMaxStickers(unsigned max) {
        
        Image** newAllStickers = new Image*[max];
        unsigned newNumStickers = 0;
        for (unsigned i = 0; i < numStickers; i++) {
            if (i < max) {
                newAllStickers[i] = allStickers[i];
                newNumStickers++;

            } else if (allStickers[i]) {
                delete allStickers[i];
                allStickers[i] = NULL;
            }
        }
        delete[] allStickers;
        numStickers = newNumStickers;
        allStickers = newAllStickers;
        size = max;

    }

    int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y) {
        if (numStickers < size) {
            Image* newImage = new Image(sticker, x, y);
            
            allStickers[numStickers] = newImage;
            numStickers++;
            return (numStickers - 1);
        } else {
            return -1;
        }
    }

    bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
        if (index >= numStickers) {
            return false;
        }
        Image& toTrans = *allStickers[index];
        toTrans.cornerX = x;
        toTrans.cornerY = y;
        return true;
    }
        
    void StickerSheet::removeSticker(unsigned index) {
        if (index <= numStickers - 1) {
            
            

            Image** newAllStickers = new Image*[size];



            for (unsigned i = 0; i < size - 1; i++) {
                if (i >= index) {
                    newAllStickers[i] = allStickers[i + 1];
                } else {
                    newAllStickers[i] = allStickers[i];
                }
            }
            delete allStickers[index];
            delete[] allStickers;
            
            numStickers--;
            allStickers = newAllStickers;

        }
                
        
    }
            
            
    Image* StickerSheet::getSticker(unsigned index){
        if (index <= numStickers - 1) {
            return allStickers[index];
        }
        return NULL;


    }
    Image StickerSheet::render() const{
         unsigned imageWidth = basePicture.width();
        unsigned imageHeight = basePicture.height();
        
        
        for (unsigned i = 0; i < numStickers && i < size;  i++) {
            if (allStickers[i] != NULL) {
                unsigned cx =  allStickers[i] -> cornerX;
                unsigned w = allStickers[i] -> width();
                

                if ((allStickers[i] -> cornerX) + (allStickers[i] -> width()) > imageWidth) {

                imageWidth = allStickers[i] -> cornerX + allStickers[i] -> width();
            }
                if (allStickers[i] -> cornerY + allStickers[i] -> height() > imageHeight) {
                imageHeight = allStickers[i] -> cornerY + allStickers[i] -> height();
            } 
            
        }
        }
        
        
        Image result(imageWidth, imageHeight);

        for (unsigned i = 0; i < imageWidth; i++) {
            for (unsigned j = 0; j < imageHeight; j++) {
                if (i < basePicture.width() && j < basePicture.height()) {
                    HSLAPixel& pixel = result.getPixel(i, j);
                    pixel = basePicture.getPixel(i, j);

                }

            }
        }
        for (unsigned i = 0 ; i < numStickers; i++) {
            if (allStickers[i] != NULL) {
            if (allStickers[i]) {
            Image& thisSticker = *allStickers[i];
            unsigned startX = thisSticker.cornerX;
            unsigned startY = thisSticker.cornerY;

            for (unsigned i = 0; i < thisSticker.width(); i++) {
                for (unsigned j = 0; j < thisSticker.height(); j++) {
                    HSLAPixel& pixel = result.getPixel(i + startX, j + startY);                 
                    HSLAPixel& stickerPixel = thisSticker.getPixel(i, j);
                    if (stickerPixel.a != 0) {
                        pixel = stickerPixel;
                    }
                }
            }
            }
            }
        }


        return result;
    }

    void StickerSheet::delete_() {
        for (unsigned i = 0; i < numStickers; i++) {
            delete allStickers[i];
        }
        delete[] allStickers; 
    }

    void StickerSheet::copy_(const StickerSheet& other) {
        size = other.size;
        numStickers = other.numStickers;
        basePicture = other.basePicture;
        allStickers = new Image*[other.size];
        for (unsigned i = 0; i < other.size; i++) {
            allStickers[i] = NULL;
        }
        for (unsigned i = 0; i < other.numStickers; i++) {
            allStickers[i] = new Image;
            *allStickers[i] = *other.allStickers[i];
        }
               
    }

