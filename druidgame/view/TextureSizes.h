#ifndef TEXTURESIZES
#define TEXTURESIZES

#include <unordered_map>
#include <string>

using namespace std;

struct Rect
{
  int width, height;
  Rect(int w, int h)
  {
    width = w;
    height = h;
  }
};

const unordered_map<string, Rect> TEXTURE_SIZES =
    {
        {"player_human", Rect(20, 40)},
        {"player_cat", Rect(50, 25)},
        {"enemy_human1", Rect(20, 40)},
        {"map1_bg2", Rect(200, 150)},
        {"block_grass1", Rect(10, 10)},
        {"block_stonewall1", Rect(10, 10)}};

#endif /* TEXTURESIZES */
