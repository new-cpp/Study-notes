/**
 *alpha blending: allows you to control the transparency of a texture.
 */

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>

//log and end loop
#define LOG_STOP(str) puts(str);\
                      m_running = false;\

//window configs
constexpr int width{480};
constexpr int height{620};
std::string title ("title");
constexpr int window_pos{SDL_WINDOWPOS_UNDEFINED};


struct TextureManager
{
  TextureManager()=default;
  ~TextureManager()=default;

  void free();
  bool loadFromFile(const std::string& path,SDL_Renderer* t_render);
  void render(SDL_Renderer* render,int x ,int y ,SDL_Rect* clip=nullptr);
  void draw(SDL_Renderer*);

  int getWidth()const { return m_width;}
  int getHeight()const { return m_height;}


  void alterAlpha(Uint8 delta_a)
    {

      m_color.a = (static_cast<short>(m_color.a) + delta_a)%256;
      std::cout<<(int)m_color.a<<'\n';
      SDL_SetTextureAlphaMod(m_texture,m_color.a);
    }

  void setBlendingMode(const SDL_BlendMode& blendflag)
    {
      SDL_SetTextureBlendMode(m_texture,blendflag);
    }

  int m_width,m_height;
  SDL_Texture* m_texture{nullptr};

    struct
  {
    Uint8 r{0},g{0},b{0},a{0};
  }m_color{};

  };


bool TextureManager::loadFromFile(const std::string& path,SDL_Renderer* t_render)
  {
    SDL_Surface* tmp = IMG_Load(path.c_str());
    if(tmp==nullptr)
      {
        puts("can't load image");
        return false;
      }
    m_texture = SDL_CreateTextureFromSurface(t_render,tmp);
    SDL_FreeSurface(tmp);

    return true;
  }

void TextureManager::free()
  {
    SDL_DestroyTexture(m_texture);
        m_texture=nullptr;
  }

void TextureManager::render(SDL_Renderer* render,int x , int y ,SDL_Rect* clip)
  {
    SDL_Rect renderQuad = {x,y,m_width,m_height};
    if(clip!=nullptr)
      {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
      }
    SDL_RenderCopy(render,m_texture,clip,&renderQuad);
  }

void TextureManager::draw(SDL_Renderer*t_render)
  {
    //SDL_SetTextureColorMod(m_texture,m_color.r,m_color.g,m_color.b);
    SDL_RenderCopy(t_render,m_texture,nullptr,nullptr);
  }


struct Game
{

  void init();
  void input();
  void update();
  void render();
  void close();

  SDL_Window* m_window{nullptr};
  SDL_Renderer* m_render{nullptr};
  bool m_running{true};

  TextureManager m_front_texture{};
  TextureManager m_back_texture{};
};

void Game::init()
  {
    if(SDL_Init(SDL_INIT_VIDEO))
      {
        LOG_STOP("can't init SDL");
      }
    m_window = SDL_CreateWindow(title.c_str(), window_pos, window_pos,width,height,SDL_WINDOW_SHOWN);

    if(m_window == nullptr)
      {
        LOG_STOP("can't create window");
      }
    m_render = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
    if(m_render == nullptr)
      {
        LOG_STOP("can't create renderer");
      }

    if(!IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG )
      {
        LOG_STOP("can't init image");
      }

    // load textures
    if(!m_front_texture.loadFromFile("asset/alpha_blending_front.png",m_render))
      {
        LOG_STOP("can't load image");
      }

    if(!m_back_texture.loadFromFile("asset/alpha_blending_back.png",m_render))
      {
        LOG_STOP("can't load image");
      }

      m_front_texture.setBlendingMode(SDL_BLENDMODE_BLEND);
   }

void Game::input()
  {
    SDL_Event e;
    while(SDL_PollEvent(&e))
      {
        if(e.type == SDL_QUIT)
          {
            m_running = false;
          }
        else if(e.type == SDL_KEYDOWN && e.key.repeat == 0)/*SDL_generate fake repeated keypresse if it's hold
                                   long enough */
          {

             if(e.key.keysym.sym == SDLK_w)
              {
                m_front_texture.alterAlpha(32);
              }
             else if(e.key.keysym.sym == SDLK_s)
              {
                m_front_texture.alterAlpha(-32);
              }

          }


      }
  }

void Game::update()
  {

  }

void Game::render()
  {
    SDL_SetRenderDrawColor(m_render,0xff,0xff,0xff,0xff);
    SDL_RenderClear(m_render);

    // drawing
    m_back_texture.draw(m_render);
    m_front_texture.draw(m_render);

    SDL_RenderPresent(m_render);
  }

void Game::close()
  {
    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);
    m_render=nullptr;
    m_window = nullptr;

    m_front_texture.free();
    m_back_texture.free();
    IMG_Quit();
    SDL_Quit();

  }
int main()
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
  }
