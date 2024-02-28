#include <SDL2/SDL.h>

#include <cstdio>
#include <cstdint>
#include <array>
#include <string>
#include <cstddef>
enum class KeyPressed
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct Media
{
  void load_image();
  void free();

  std::array< SDL_Surface*,4 >m_images;
  size_t m_curr_image{0};
};

void Media::load_image()
{
  std::string ressource{"asset/img0.bmp"};

  for(auto& ele : m_images)
    {
      printf("%s\n",ressource.c_str());
      ele = SDL_LoadBMP(ressource.c_str());
      if(ele == nullptr)
        {
          puts("can't load image\n");
          return ;
        }
      ++ressource.at(9);
    }
}

void Media::free()
  {
    for(auto& ele : m_images)
      {
        SDL_FreeSurface(ele);
      }
  }


struct App
{

  void init();
  void input();
  void update();
  void render();
  void close();

  bool m_running{true};
  SDL_Window* m_window{nullptr};
  SDL_Surface* m_window_surface{nullptr};
  uint32_t m_width{480},m_hight{720};
  Media m_media{};
};

void App::init()
{
  if(SDL_Init(SDL_INIT_EVERYTHING)< 0)
    {
      puts("can't initialize SDL\n");
      return ;
    }
  m_window = SDL_CreateWindow("lesson 4",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_hight, SDL_WINDOW_SHOWN);

  if(m_window == nullptr)
    {
      puts("can't create window\n");
      return ;
    }

   m_window_surface = SDL_GetWindowSurface(m_window);

   m_media.load_image();
}


void App::input()
  {
    SDL_Event e;
    while(SDL_PollEvent(&e))
      {
         if(e.type == SDL_QUIT) m_running = false;
         else if( e.type == SDL_KEYDOWN)
           {
             switch(e.key.keysym.sym)
               {
                 case SDLK_UP:
                   m_media.m_curr_image = static_cast<int>(KeyPressed::UP);
                   break;
                 case SDLK_DOWN:
                   m_media.m_curr_image = static_cast<int>(KeyPressed::DOWN);
                   break;
                 case SDLK_LEFT:
                   m_media.m_curr_image = static_cast<int>(KeyPressed::LEFT);
                   break;
                 case SDLK_RIGHT:
                   m_media.m_curr_image = static_cast<int>(KeyPressed::RIGHT);
               }
           }
      }
  }


void App::update()
  {
  }

void App::render()
  {
   // printf("curr_image : %d\n",m_media.m_curr_image);
    SDL_BlitSurface(m_media.m_images[m_media.m_curr_image], nullptr, m_window_surface, nullptr);
    SDL_UpdateWindowSurface(m_window);
  }

void App::close()
{
    m_media.free();

    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

int main(int argc , char* argv[])
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
