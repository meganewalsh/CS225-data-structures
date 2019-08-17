#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"


int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image BASE;		BASE.readFromFile("base.png");
  Image one;		one.readFromFile("trophy.png");
  Image two;		two.readFromFile("passed.png");
  Image three;		three.readFromFile("seg.png");
  Image four;		four.readFromFile("logo.png");
  Image five;		five.readFromFile("i.png");

  StickerSheet sheet(BASE, 7);

  one.scale(0.5);
  sheet.addSticker(one, 1280, 420);

  two.scale(2);
  sheet.addSticker(two, 1250, 505);

  three.scale(2.3);
  sheet.addSticker(three, 740, 1400);
  sheet.addSticker(three, 810, 1235);
  sheet.addSticker(three, 865, 1110);

  four.scale(0.07);
  sheet.addSticker(four, 860, 510);

  five.scale(0.2);
  sheet.addSticker(five, 725, 820); 

  (sheet.render()).writeToFile("myImage.png");


return 0;
}
