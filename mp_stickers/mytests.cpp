

#include "cs225/catch/catch.hpp"
#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"


using namespace cs225;

int main() {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 60, 200);
  sheet.changeMaxStickers(1);
  return 0;
}
