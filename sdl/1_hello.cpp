#define SDL_MAIN_HANDLED

#include <SDL2\SDL.h>
#include <stdio.h>
#include <cstdint>
constexpr uint32_t SCREEN_WIDTH = 640;
constexpr uint32_t SCREEN_HEIGHT = 480;


int main(int argc , char* args[])
{

  SDL_Window * window = nullptr;
  SDL_Surface* screen_surface = nullptr;

  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      printf("SDL could not intitialize SDL_Error: %s\n", SDL_GetError());
    }
  else
    {
      window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if(!window)
        {
          printf("SDL can't create Window SDL_Error : %s\n", SDL_GetError());
        }
      else
        {
          screen_surface = SDL_GetWindowSurface(window);

          SDL_FillRect(screen_surface,nullptr,SDL_MapRGB(screen_surface->format,0xFF,0xFF,0xFF ));

          SDL_UpdateWindowSurface( window );

          /* just to winow to stay up */
          SDL_Event e;
          bool quit = false;
          while(quit == false)
            {
              while(SDL_PollEvent(&e))
                if(e.type == SDL_QUIT)
                  {
                    quit = true;
                  }
            }
        }


    }

      SDL_DestroyWindow( window);
      SDL_Quit();

  return 0;
}
