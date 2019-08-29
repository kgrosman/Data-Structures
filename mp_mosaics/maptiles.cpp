/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"


using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& img,
                       vector<TileImage>& tiles)
{
    /**
     * @todo Implement this function!
     */

    
    //get source image dimensions
    int rows = img.getRows();
    int cols = img.getColumns();


    //make sure arguments are valid
    if (img.getRows() == 0 && img.getColumns() == 0) {
        return NULL;
    }
    if (tiles.empty()) {
        return NULL;
    }

    //holds average colors for every region of the SourceImage in Point<3> form
    vector<Point<3>> regionAverages;

    //holds average colors for every TileImage in tiles in Point<3> form
    vector<Point<3>> tileAverages;

    //lets us get the appropriate image for the average color
    map<Point<3>, TileImage *> colorToTile;

    //holds ptr to TileImages to add in appropriate cells in final mosaic
    //1D index for (col, row) is (row * cols) + col
    vector<TileImage *> layout;

    
    //populate average SourceImage region colors
    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            regionAverages.push_back(convertToXYZ(img.getRegionColor(row, col)));
        }
    }

    //populate average tile colors - need this vector for initializing the KDTree
    for (auto it = tiles.begin(); it != tiles.end(); it++) {
        tileAverages.push_back(convertToXYZ(it->getAverageColor())); 
    }

    //map colors to their respective TileImages
    for (auto it = tiles.begin(); it != tiles.end(); it++) {
        colorToTile.insert({convertToXYZ(it->getAverageColor()), &(*it)}); 
    }

    //construct 3D KDTree and populate it with average colors from the tiles vector
    KDTree<3> tree(tileAverages);

    //add closest TileImage ptr to the layout vector
    for (auto it = regionAverages.begin(); it != regionAverages.end(); it++) {
        layout.push_back(colorToTile.at(tree.findNearestNeighbor(*it)));
    }


    //create new MosaicCanvas with same number of rows and columns as source img
    MosaicCanvas * canvas = new MosaicCanvas(rows, cols);


    //set tiles according to layout vector
    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            canvas->setTile(row, col, layout.at((rows * col) + row));
        }
    }

    //finished - return the canvas
    return canvas;
}
