#define SDL_MAIN_HANDLE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <cstddef>
#include <string>
#include <utility>
struct App
{

  void init();
  void render();
  void update();
  void input();
  void close();

  void load_asset();

  bool m_running{true};
  int m_height{480}, m_width{720};

  SDL_Window* m_windows;
  SDL_Surface* m_screen;
  SDL_Surface* m_canvas;
};

void App::init()
  {
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
      {
        puts("can't init sdl subsystem");
        std::exit(-1);
      }

     m_windows = SDL_CreateWindow("title",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED
                                  ,m_height, m_width,SDL_WINDOW_SHOWN);
     if(m_windows==nullptr)
       {
         puts("can't create window");
         return;
       }
     else
       {
         m_screen = SDL_GetWindowSurface(m_windows);

         if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
           {
             puts("can't init image subsystem");
             return ;
           }
         else
           {
             load_asset();
           }
       }
  }

void App::load_asset()
  {
    std::string path("asset/img.png");
    m_canvas = IMG_Load(path.c_str());
    if(m_screen == nullptr)
      {
        puts("can't load png image");
        return;
      }
    else
      {
        //convert sruface into screen forma;
        auto optimized_surface = SDL_ConvertSurface(m_canvas, m_screen->format, 0);
        m_canvas = std::move(optimized_surface);
      }
  }


void App::update(){}

void App::render()
  {
    SDL_BlitSurface(m_canvas,nullptr,m_screen,nullptr);
    SDL_UpdateWindowSurface(m_windows);
  }

void App::input()
  {
    SDL_Event e;
    while(SDL_PollEvent(&e))
      {
        if(e.type == SDL_QUIT)
          m_running = false;
        else if(e.type == SDL_KEYDOWN)
          {
            if(e.key.keysym.sym == SDLK_d)
              puts("d is pressed");
          }
      }
  }

void App::close()
  {
    SDL_FreeSurface(m_canvas);
    SDL_DestroyWindow(m_windows);
    m_windows = nullptr;
    SDL_Quit();
  }
int main(int argc, char* arg[])
  {

    App app;
    app.init();

    while(app.m_running)
      {
        app.input();
        app.update();
        app.render();
      }

    app.close();
    return 0;
  }
