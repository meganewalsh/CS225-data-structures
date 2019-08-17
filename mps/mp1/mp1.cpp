#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <math.h>
using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
PNG orig;
orig.readFromFile(inputFile);

PNG rotated = orig;

 for (unsigned x = 0; x < orig.width(); x++) { 
    for (unsigned y = 0; y < orig.height(); y++) {
	HSLAPixel * o_pixel = orig.getPixel(x, y);
	HSLAPixel * r_pixel = rotated.getPixel((orig.width()-x-1), (orig.height()-y-1));
		
	r_pixel->h = o_pixel->h;
	r_pixel->s = o_pixel->s;
	r_pixel->l = o_pixel->l;
	r_pixel->a = o_pixel->a;

    }
 }
rotated.writeToFile(outputFile);
}




PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3
double index = 0;
 for (unsigned x = 0; x < png.width(); x++) { 
    for (unsigned y = 0; y < png.height(); y++) {
	index++;
	HSLAPixel * pixel = png.getPixel(x, y);
	pixel->l = 0.7;
	pixel->a = 1;
	pixel->s = 0.7;
	
	if(x==2*y || x==3*y || x==4*y || x==5*y || y==2*x || y==3*x || y==4*x ||
	   y==5*x || x==6*y || y==6*x || x==y || x==1.5*y || y==1.5*x)
		pixel->l = 1;
	else{
		pixel->h = 0.6*sqrt(x*x+y*y);
		if ((pixel->h < 300 && pixel->h > 250) || (pixel->h < 400 && pixel->h > 350) || (pixel->h < 600 && pixel->h > 550) || (pixel->h >420 && pixel->h <430))
		   pixel->h = 20;
	}
   }
 }

  return png;
}
