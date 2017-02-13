#include "img.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace img {

void Img::Load(SDL_Renderer* renderer, const char* file) {
  SDL_Surface* image = IMG_Load(file);

  if (image == NULL) {
    printf("error loading image %s", file);
  }

  texture = SDL_CreateTextureFromSurface(renderer, image);

  if (texture == NULL) {
    printf("error loading texture %s", file);
  }

  if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) < 0) {
    printf("error querying texture %s", file);
  }

  SDL_FreeSurface(image);
}
}
