/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    std::map <Point<3>, int> myMap;
    //Create vector of points from theTiles vector  ---  (h, s, l)
    vector<Point<3>> points;
    for (int i = 0; i < (int)theTiles.size(); i++){
        HSLAPixel pixTile = theTiles[i].getAverageColor();
        double newH = (double)pixTile.h/360;
 	Point<3> myPoint(newH, pixTile.s, pixTile.l);
	myMap[myPoint] = i;
        points.push_back(myPoint);
    }    

    const KDTree<3>* myTree = new const KDTree<3>(points);

    //Creates dynamically allocated canvas with same number of rows and columns as source; to be returned.
    MosaicCanvas* myCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    
    //For every region in the source, take the tileImage with average color closest to the average color of
    //that region and place that tileImage into myCanvas in the same tile position as the source's region
    for (int x = 0; x < (int)theSource.getRows(); x++){
        for (int y = 0; y < (int)theSource.getColumns(); y++){
	    //myCanvas->setTile(x,y, get_match_at_idx(*myTree, myMap, theTiles, theSource, x, y));

            HSLAPixel pixel = theSource.getRegionColor(x,y);
	    double newHue = (double)pixel.h/360;
            Point<3> point = Point<3>(newHue, pixel.s, pixel.l);
            Point<3> neighbor = myTree->findNearestNeighbor(point); 
            myCanvas->setTile(x, y, &theTiles[myMap[neighbor]]);
        }
    }

    delete myTree;
    return myCanvas;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
