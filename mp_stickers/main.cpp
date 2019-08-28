#include "Image.h"
#include "StickerSheet.h"

int main() {
    Image background(1049,700);
    date.readFromFile("background.png");
    date.scale(900, 600);


    StickerSheet sheet(background, 10);
    

    Image sticker1(62, 76);
    adam.readFromFile("p1.png");
    adam.scale(75, 500);


    Image sticker2(80,83);
    matt.readFromFile("p2.png");
    matt.scale(95, 500);

    Image sticker3(270, 292);
    baby.readFromFile("p3.png");
    baby.scale(160, 400);

    Image sticker4(40,51);
    lab.readFromFile("p4.png");
    lab.scale(50, 500);
    
    sheet.addSticker(sticker1, 410, 215);
    sheet.addSticker(sticker2, 452, 238);

    sheet.addSticker(sticker3,500, 90);
    sheet.addSticker(sticker4, 294, 104);
    
    
    
    Image finalPic = sheet.render();

   
    
    finalPic.writeToFile("myImage.png");

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
