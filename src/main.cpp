#include <psp2/kernel/processmgr.h>
#include <SDL2/SDL.h>
#include <vector>

//Screen dimension constants
enum {
  SCREEN_WIDTH  = 960,
  SCREEN_HEIGHT = 544
};

SDL_Window    * gWindow   = NULL;
SDL_Renderer  * gRenderer = NULL;

const int H_WIDTH = SCREEN_WIDTH / 2;
const int Q_WIDTH = SCREEN_WIDTH / 4;
const int H_HEIGHT = SCREEN_HEIGHT / 2;
const int Q_HEIGHT = SCREEN_HEIGHT / 4;

const std::vector<SDL_Vertex> verts = {
  { SDL_FPoint{ H_WIDTH-Q_WIDTH, H_HEIGHT+Q_HEIGHT }, SDL_Color{ 255,   0,   0, 255}, SDL_FPoint{0}, },
  { SDL_FPoint{ H_WIDTH+Q_WIDTH, H_HEIGHT+Q_HEIGHT }, SDL_Color{   0, 255,   0, 255}, SDL_FPoint{0}, },
  { SDL_FPoint{         H_WIDTH, H_HEIGHT-Q_HEIGHT }, SDL_Color{   0,   0, 255, 255}, SDL_FPoint{0}, },
};


int main(int argc, char *argv[]) {
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
      return -1;

  if ((gWindow = SDL_CreateWindow("RedRectangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
    return -1;

  if ((gRenderer = SDL_CreateRenderer(gWindow, -1, 0)) == NULL)
      return -1;

  bool running = true;
  while( running ) {
    SDL_Event ev;
    while(SDL_PollEvent( &ev )) {
      if(SDL_QUIT == ev.type) {
        running = false;
        break;
      }
    }

    SDL_SetRenderDrawColor(gRenderer, 51, 77, 77, SDL_ALPHA_OPAQUE); // clear color {0.2, 0.3, 0.3}
    SDL_RenderClear(gRenderer);
    SDL_RenderGeometry(gRenderer, nullptr, verts.data(), verts.size(), nullptr, 0);
    SDL_RenderPresent(gRenderer);
  }

  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  SDL_Quit();
  return 0;
}
