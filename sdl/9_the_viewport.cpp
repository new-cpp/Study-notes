#define SDL_MAIN_HANDLER
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

struct App
{
  void init();
  void input();
  void update(){}
  void render();
  void close();

  bool m_running{true};
  SDL_Window* m_window{nullptr};
  SDL_Renderer* m_render{nullptr};
  SDL_Texture* m_texture{nullptr};
  int m_width{640},m_height{480};
};

void App::init()
  {
    if(SDL_Init(SDL_INIT_VIDEO)<0)
      {
        puts("can't init video substem");
        m_running = false;
        return;
      }

    m_window = SDL_CreateWindow("title",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,m_width,m_height,SDL_WINDOW_SHOWN);
    if(m_window == nullptr)
      {
        puts("can't create window");
        m_running = false;
        return ;
      }

    m_render = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
    if(m_render == nullptr)
      {
        puts("can't can't create render");
        m_running = false;
        return ;
      }
    SDL_SetRenderDrawColor(m_render,0xff,0xff,0xff,0xff);
    SDL_RenderClear(m_render);

    if(!IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG)
      {
        puts("can't init image subsystem");
        m_running =false;
        return ;
      }

    SDL_Surface* tmp_surface = IMG_Load("asset/img.png");
    m_texture = SDL_CreateTextureFromSurface(m_render,tmp_surface);
    SDL_FreeSurface(tmp_surface);

  }


void App::input()
  {
    SDL_Event e;
    while(SDL_PollEvent(&e))
      {
        if(e.type == SDL_QUIT)
          {
            m_running = false;
          }
      }
  }

void App::render()
  {
    SDL_Rect topLeftViewport{0,0,m_width/2,m_height/2};
    SDL_Rect bottomViewport{0,m_height/2,m_width,m_height/2};
    SDL_Rect topRightViewport{m_width/2,0,m_width/2,m_height/2};
    SDL_RenderSetViewport(m_render,&topLeftViewport);
    SDL_RenderCopy(m_render,m_texture,nullptr,nullptr);

    SDL_RenderSetViewport(m_render,&bottomViewport);
    SDL_RenderCopy(m_render,m_texture,nullptr,nullptr);

    SDL_RenderSetViewport(m_render,&topRightViewport);
    SDL_RenderCopy(m_render,m_texture,nullptr,nullptr);

    SDL_RenderPresent(m_render);
  }
void App::close()
  {
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);
    m_texture = nullptr;
    m_render = nullptr;
    m_window = nullptr;
    SDL_Quit();

    IMG_Quit();
  }
int main(int argc, char* argv[])
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
