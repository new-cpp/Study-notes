
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <cstdio>

#define SCREEN_WIDTH 780
#define SCREEN_HIGHT  420
// window to render on
SDL_Window* gWindow = nullptr;
//surface rendered by window , SDL_surface user cpu to render
SDL_Surface* gWindowSurface = nullptr;

//surface containe image
SDL_Surface* gImageSurface = nullptr;
bool init()
  {
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
      {
        printf("can't intialise SDL Vedio subsystem ,%s\n", SDL_GetError());
        success = false;
      }
    else
      {
        gWindow = SDL_CreateWindow("title",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH,SCREEN_HIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == nullptr)
          {
            printf("can't create window , %s\n", SDL_GetError());
            success = false;
          }
        else
          {
            gWindowSurface = SDL_GetWindowSurface(gWindow);
          }
      }
  }

bool loadMedia()
  {
    bool success = true;
    gImageSurface = SDL_LoadBMP("asset/img.bmp");

    if(gImageSurface == nullptr)
      {
        printf("can't load image %s\n", SDL_GetError());
        success = false;
      }
    return success;
  }

void close()
  {
    SDL_FreeSurface(gImageSurface);
    gImageSurface = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_Quit();
  }



int main()
  {
    if(init())
      {
       if( loadMedia())
         {
           SDL_BlitSurface(gImageSurface, nullptr, gWindowSurface,nullptr);
           SDL_UpdateWindowSurface(gWindow);

           SDL_Event e;
           bool quit = false;
           while(!quit)
             {
               while(SDL_PollEvent(&e))
                 {
                   if(e.type == SDL_QUIT)
                     {
                       quit = true;
                     }
                 }
             }
         }
        close();
      }
  }
