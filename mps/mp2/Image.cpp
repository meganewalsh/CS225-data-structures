#include "Image.h"
using namespace cs225;

void Image::lighten(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x, y);
      if (pixel.l <= 0.9)
	pixel.l += 0.1;
      else
	pixel.l = 1.0;
    }
  }
}


void Image::lighten(double amount){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x, y);
      if (pixel.l <= (1.0 - amount))
	pixel.l += amount;
      else
	pixel.l = 1.0;
    }
  }
}



void Image::darken(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x, y);
      if (pixel.l >= 0.1)
	pixel.l -= 0.1;
      else
	pixel.l = 0.0;
    }
  }
}


void Image::darken(double amount){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x, y);
      if (pixel.l >= amount)
	pixel.l -= amount;
      else
	pixel.l = 0.0;
    }
  }
}


void Image::saturate(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x, y);
      if (pixel.s <= 0.9)
	pixel.s += 0.1;
      else
	pixel.s = 1.0;
    }
  }
}


void Image::saturate(double amount){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x, y);
      if (pixel.s <= (1.0 - amount))
	pixel.s += amount;
      else
	pixel.s = 1.0;
    }
  }
}


void Image::desaturate(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x, y);
      if (pixel.s >= 0.1)
	pixel.s -= 0.1;
      else
	pixel.s = 0.0;
    }
  }
}


void Image::desaturate(double amount){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x, y);
      if (pixel.s >= amount)
	pixel.s -= amount;
      else
	pixel.s = 0.0;
    }
  }
}


void Image::grayscale(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x, y);
	pixel.s = 0;
    }
  }
}


void Image::rotateColor(double degrees){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x, y);
      if ((pixel.h + degrees) > 360)
	pixel.h = (pixel.h + degrees - 360);
      else if ((pixel.h + degrees) < 0)
	pixel.h = (pixel.h + degrees + 360);
      else
	pixel.h += degrees;
    }
  }
}


void Image::illinify(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
	HSLAPixel & pixel = getPixel(x, y);
      if(pixel.h < 113 || pixel.h >= 294)
	pixel.h = 11;   //orange hue
      else
	pixel.h = 216;  //blue hue      
    }
  }
}


void Image::scale(double factor){

//Determine new dimensions based on factor, save
int saveW = width();
int saveH = height();
int oldOriginX, oldOriginY, newOriginX, newOriginY;
int newDeltaX, newDeltaY; //distance of new pixel from new origin
int oldDeltaX, oldDeltaY; //distance of old pixel from old origin

//Expanding - saveW saveH SMALL, w h LARGE
if (factor >= 1){
 //Resize original image
   unsigned int w = width() * factor;
   unsigned int h = height() * factor;
   resize(w, h);		//calling width() height() now returns new

 //Initializes indexes 
 
   oldOriginX = (saveW-1); oldOriginY = (saveH-1); newOriginX = (w-1); newOriginY = (h-1);

   for(int newX = (w-1); newX >= 0 ; newX--){
      for(int newY = (h-1); newY >= 0; newY--){
	  newDeltaX = newOriginX - newX;
	  newDeltaY = newOriginY - newY;
	  oldDeltaX = newDeltaX / factor;
	  oldDeltaY = newDeltaY / factor;

	  HSLAPixel & newPixel = this->getPixel(newX, newY);
	  HSLAPixel & oldPixel = this->getPixel((oldOriginX - oldDeltaX), (oldOriginY - oldDeltaY));
	  newPixel = oldPixel;
      }
   }
}

//Shrinking - saveW saveH LARGE, w h SMALL
else{
 //Initializes indexes 
   int w = width() * factor;
   int h = height() * factor;

   for(int newX = 0; newX < w; newX++){
      for(int newY = 0; newY < h; newY++){
	  newDeltaX = newX;
	  newDeltaY = newY;
	  oldDeltaX = newDeltaX / factor;
	  oldDeltaY = newDeltaY / factor;
	  
	  HSLAPixel & newPixel = this->getPixel(newX, newY);
	  HSLAPixel & oldPixel = this->getPixel(oldDeltaX, oldDeltaY);
	  newPixel = oldPixel;
      }
   }

resize(w, h);
}


}



void Image::scale(unsigned int w, unsigned int h){
//Check both ratios to see which one rounds less (floor).
  double Ratio;

Ratio =((double) h) / ((double) height());
scale(Ratio);	
 
}
