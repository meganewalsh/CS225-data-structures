#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"

using namespace cs225;
using namespace std;
StickerSheet::StickerSheet (const Image &picture, unsigned max){

   arrayPtr = new Sticker[max];

//All elements without a picture will point to NULL
   for (unsigned i=0; i < max; i++)
	arrayPtr[i].stickerImage = NULL;

   basePic = picture;
   _Max = max;
}



StickerSheet::~StickerSheet(){

   delete[] arrayPtr;
}



StickerSheet::StickerSheet (const StickerSheet& other){

   _Max = other._Max;
   basePic = other.basePic;

   arrayPtr = new Sticker[_Max];
   for (unsigned i = 0; i < other._Max; i++){
      arrayPtr[i].stickerImage = other.arrayPtr[i].stickerImage;
      arrayPtr[i].x = other.arrayPtr[i].x;
      arrayPtr[i].y = other.arrayPtr[i].y;
   }
}



const StickerSheet& StickerSheet::operator= (const StickerSheet &other){
  if (this != &other) {
     this->basePic = other.basePic;
     this->_Max = other._Max;

     for (unsigned i = 0 ; i < _Max ; i++)
	this->arrayPtr[i] = other.arrayPtr[i];
  }
  return *this;
}



void StickerSheet::changeMaxStickers (unsigned max){
// Note: cannot change size of array once created. tempSheet is correct length

//INCREASING size. Smaller = _Max, bigger = max.
  if (max >= _Max){
  Sticker* tempStickerPtr = new Sticker[max];

      // Copy exisitng image*s to tempSheet
      for (unsigned i = 0; i < _Max; i++)
	tempStickerPtr[i] = arrayPtr[i];

      // Fill additional, null spaces
      for (unsigned i = _Max; i < max; i++)
	tempStickerPtr[i].stickerImage = NULL;

  // sheetPtr point to new array
  Sticker* temporary = arrayPtr;
  arrayPtr = tempStickerPtr;
  delete[] temporary;
  }

// DECREASING size - cuts off extra.  Smaller = max, bigger = _Max.
  else {

      // Deletes all of the cut-off pictures -- memory
      for (unsigned i = max; i < _Max; i++){
         if (arrayPtr[i].stickerImage != NULL)
	    removeSticker(i); //from arrayPtr
      }
  }  

  _Max = max;
}



int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
int flag = -1;
  for (unsigned i = 0; i < _Max; i++){
     // Find the first empty cell in the array, point to sticker
     if (arrayPtr[i].stickerImage == NULL){
        Sticker* newSticker = new Sticker();
        newSticker->x = x;
        newSticker->y = y;
	
       newSticker->stickerImage = &sticker;
        arrayPtr[i] = *newSticker;
	delete newSticker;
	flag = i;
	break;
     }
  }
  // If no change in flag, there was no room in the sheet for another sticker
  return flag;	
}



bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){

  if (index > (_Max - 1) || arrayPtr[index].stickerImage == NULL)
	return false;

  arrayPtr[index].x = x;
  arrayPtr[index].y = y;
  return true;
}



void StickerSheet::removeSticker (unsigned index){
  arrayPtr[index].stickerImage = NULL;

}



Image* StickerSheet::getSticker (unsigned index) const{
  if (index > (_Max -1))
     return NULL;

  else 
     return arrayPtr[index].stickerImage;

}



Image StickerSheet::render() const{

Image newPic;
newPic = basePic;
for (unsigned i = 0; i < _Max ; i++) {
  if (arrayPtr[i].stickerImage != NULL){
    // Resizes if sticker placement is out of bounds
    if ((arrayPtr[i].x + (*(arrayPtr[i].stickerImage)).width()) > newPic.width()){
		newPic.resize( arrayPtr[i].x+(*(arrayPtr[i].stickerImage)).width() , newPic.width());}
    if ((arrayPtr[i].y + (*(arrayPtr[i].stickerImage)).height()) > newPic.height()){
		newPic.resize( newPic.width(), arrayPtr[i].y+(*(arrayPtr[i].stickerImage)).height());}
    // Overwrite base pixels with sticker pixels 
    for (unsigned stickerX = 0; stickerX < (*(arrayPtr[i].stickerImage)).width(); stickerX++){
      for (unsigned stickerY = 0; stickerY < (*(arrayPtr[i].stickerImage)).height(); stickerY++){
	  HSLAPixel & stickerPixel = (*(arrayPtr[i].stickerImage)).getPixel(stickerX, stickerY);
	  if (stickerPixel.a != 0){
	     HSLAPixel & newPixel = newPic.getPixel(arrayPtr[i].x+stickerX, arrayPtr[i].y+stickerY);
	     newPixel = stickerPixel;}
      }
    }
  }
}
return newPic;
}
