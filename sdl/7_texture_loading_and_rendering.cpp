#define SDL_MAIN_HANDLER
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <utility>

struct App
{
  void init();
  void input();
  void update(){}
  void render();
  void close();


  void load_texture(const std::string& t_path);

  bool m_running{true};
  SDL_Window* m_window{nullptr};
  SDL_Renderer* m_renderer{nullptr};
  SDL_Texture* m_texture{nullptr};

  int m_width{480},m_height{720};
};

void App::init()
  {
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
      {
        puts("can't init sdl subsystem");
        m_running = false;
      }

    m_window = SDL_CreateWindow("title",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                m_width, m_height, SDL_WINDOW_SHOWN);
    if(m_window == nullptr)
      {
        puts("can't create window");
        m_running = false;
      }
    m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
    if(m_renderer == nullptr)
      {
        puts("can't create renderer");
        m_running = false;
      }
    SDL_SetRenderDrawColor(m_renderer, 0xFF,0xFF,0xFF,0xFF);

    //init IMG lib for png image
    if(!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
      {
        puts("can't init image lib");
        m_running = false;
      }

    load_texture("asset/img.png");
  }

void App::load_texture(const std::string& t_path)
  {
    SDL_Surface* loaded_surface = IMG_Load(t_path.c_str());
    if(loaded_surface == nullptr)
      {
        puts("can't load image to surface");
        m_running = false;
      }

    m_texture = SDL_CreateTextureFromSurface(m_renderer,loaded_surface);
    if(m_texture == nullptr)
      {
        puts("can't create texure from surface ");
        m_running = false;
      }

    SDL_FreeSurface(loaded_surface);
  }


void App::close()
  {
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    m_texture = nullptr;
    m_renderer = nullptr;
    m_window = nullptr;

    SDL_Quit();
    IMG_Quit();
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
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer,m_texture,nullptr,nullptr);
    SDL_RenderPresent(m_renderer);
  }
int main(int argc, char* argv[])
  {

    App app;
    app.init();
    while(app.m_running)
      {
        app.input();
        app.update();// entities if any
        app.render();
      }
    app.close();
    return 0;
  }
