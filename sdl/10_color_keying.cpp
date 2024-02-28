#define SDL_MAIN_HANDLER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

using i32=int;
using i64=long long;

struct TextureManager
{
  TextureManager()= default;
  ~TextureManager() = default;
  void loadFromFile(SDL_Renderer*& t_render,const std::string& path);

  void free();
  void render(SDL_Renderer*& t_render,i32 x, i32 y);

  i32 getWidth()const { return m_width;}
  i32 getHeight()const { return m_height;}

  SDL_Texture* m_texture{nullptr};
  i32 m_width,m_height;

};

void TextureManager::loadFromFile(SDL_Renderer*& t_render, const std::string& path)
  {
    // delete preexisting texture
    free();

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr)
      {
        puts("can't load surface");
      }
    else
      {
        // make green transparnt
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,0,0xff,0xff));
        m_texture = SDL_CreateTextureFromSurface(t_render,loadedSurface);

        if(m_texture==nullptr)
          {
            puts("can't create texuture from surface");
          }
        else
          {
            int access;
            unsigned int format;
            SDL_QueryTexture(m_texture,&format,&access,&m_width,&m_height);
          }
      }
   }

void TextureManager::free()
  {
    if(m_texture!=nullptr)
      {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        m_width = 0;
        m_height = 0;
      }
  }

void TextureManager::render(SDL_Renderer*& t_render,i32 x,i32 y)
  {
    SDL_Rect renderQuad { x,y,m_width,m_height};
    SDL_RenderCopy(t_render,m_texture,nullptr,&renderQuad);
  }
struct Game
{


  void init();
  void input();
  void update();
  void render();
  void close();

  void loadMedia();

  SDL_Window* m_window{nullptr};
  SDL_Renderer* m_render{nullptr};

  const int m_height{480};
  const int m_width{620};

  bool m_running{true};
  TextureManager m_backgroundTexture;
  TextureManager m_playerTexture;
};

void Game::init()
  {
    if(SDL_Init(SDL_INIT_VIDEO)<0)
      {
        puts("SDL can't init subsystem");
        m_running = false;
      }
    m_window = SDL_CreateWindow("title",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,m_width,m_height,SDL_WINDOW_SHOWN);
    if(m_window == nullptr)
      {
        puts("can't create window");
        m_running = false;
      }

    m_render = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
    if(m_render== nullptr)
      {
        puts("can't create render");
        m_running = false;
      }
    if(!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG ))
      {
        puts("can't init image sybstem");
        m_running = false;
      }

     loadMedia();
  }

void Game::input()
  {
    SDL_Event e;
    while(SDL_PollEvent(&e))
      {
        if(e.type==SDL_QUIT)
          m_running = false;
        if(e.type == SDL_KEYDOWN)
          {
            if(e.key.keysym.sym == SDLK_UP)
              {
                puts("up pressed!!!");
              }
          }
      }
  }

void Game::update()
  {
  }


void Game::render()
  {
    SDL_SetRenderDrawColor( m_render, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(m_render);



    m_backgroundTexture.render(m_render,0,0);
    m_playerTexture.render(m_render,240,190);

    SDL_RenderPresent(m_render);
  }

void Game::loadMedia()
  {

    m_backgroundTexture.loadFromFile(m_render,"asset/background.png");
    m_playerTexture.loadFromFile(m_render,"asset/foo.png");

  }

void Game::close()
  {
    m_backgroundTexture.free();
    m_playerTexture.free();

    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);

    m_window = nullptr;
    m_render = nullptr;

    IMG_Quit();
    SDL_Quit();
  }

int main(int argc, char* argv[])
  {

    Game game;
    game.init();

    while(game.m_running)
      {
        game.input();
        game.update();
        game.render();
      }
    game.close();
    return 0;
  }
