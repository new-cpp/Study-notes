#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <cassert>

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

  void setSpriteClip();
  SDL_Rect* getSpriteClip(int i)
    {
      assert(i<4);
      return &m_sprite_clip[i];
    }

  int m_width,m_height;
  SDL_Texture* m_sprite_sheets{nullptr};
  SDL_Rect m_sprite_clip[4];
  };

bool TextureManager::loadFromFile(const std::string& path,SDL_Renderer* t_render)
  {
    SDL_Surface* tmp = IMG_Load(path.c_str());
    if(tmp==nullptr)
      {
        puts("can't load image");
        return false;
      }
    m_sprite_sheets = SDL_CreateTextureFromSurface(t_render,tmp);
    SDL_FreeSurface(tmp);


    return true;
  }

void TextureManager::free()
  {
    SDL_DestroyTexture(m_sprite_sheets);
    m_sprite_sheets=nullptr;
  }

void TextureManager::render(SDL_Renderer* render,int x , int y ,SDL_Rect* clip)
  {
    SDL_Rect renderQuad = {x,y,m_width,m_height};
    if(clip!=nullptr)
      {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
      }
    SDL_RenderCopy(render,m_sprite_sheets,clip,&renderQuad);
  }

void TextureManager::draw(SDL_Renderer*t_render)
  {
    render(t_render,0,0,nullptr);
  }

void TextureManager::setSpriteClip()
  {
    m_sprite_clip[0].x = 0;
    m_sprite_clip[0].y = 0;
    m_sprite_clip[0].w = 100;
    m_sprite_clip[0].h = 100;

     m_sprite_clip[1].x = 1;
    m_sprite_clip[1].y = 0;
    m_sprite_clip[1].w = 100;
    m_sprite_clip[1].h = 100;

     m_sprite_clip[2].x = 0;
    m_sprite_clip[2].y = 100;
    m_sprite_clip[2].w = 100;
    m_sprite_clip[2].h = 100;

     m_sprite_clip[3].x = 100;
    m_sprite_clip[3].y = 100;
    m_sprite_clip[3].w = 100;
    m_sprite_clip[3].h = 100;
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

  TextureManager m_texture{};
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
    if(!m_texture.loadFromFile("asset/sprites.png",m_render))
      {
        LOG_STOP("can't load image");
      }

    m_texture.setSpriteClip();
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
      }
  }

void Game::update()
  {

  }

void Game::render()
  {
    SDL_SetRenderDrawColor(m_render,0xff,0xff,0xff,0xff);
    SDL_RenderClear(m_render);

    //entities drawing
      //Render top left sprite
      m_texture.render(m_render, 0, 0, m_texture.getSpriteClip(0) );

      //Render top right sprite
      m_texture.render(m_render, width -  m_texture.getSpriteClip(1)->w, 0,   m_texture.getSpriteClip(1) );

      //Render bottom left sprite
      m_texture.render(m_render, 0, height -   m_texture.getSpriteClip(1)->h,   m_texture.getSpriteClip(2) );

      //Render bottom right sprite
      m_texture.render(m_render, width -   m_texture.getSpriteClip(3)->w, height -   m_texture.getSpriteClip(3)->h,   m_texture.getSpriteClip(3) );


    SDL_RenderPresent(m_render);
  }

void Game::close()
  {
    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);
    m_render=nullptr;
    m_window = nullptr;

    m_texture.free();
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
