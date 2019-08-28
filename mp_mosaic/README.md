# mp_mosaics
This MP entails my creating a mosaic that resembles an image by building a k-d tree containing data from a large number of stock images (called "tiles") and finding the tile with the closest appearance to each small section of the original image via a nearest-neighbor search on the k-d tree. The optimal tiles then replace their corresponding section(s) of the image, generating the mosaic.