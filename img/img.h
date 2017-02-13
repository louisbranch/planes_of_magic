#ifndef IMG_H_
#define IMG_H_

#include <SDL2/SDL.h>

namespace img {

class Img {
 public:
  int w;
  int h;
  SDL_Texture* texture;

  void Load(SDL_Renderer*, const char* file);
};
}

#endif  // IMG_H_
