#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include <string>



constexpr int SCREEN_WIDTH{ 480 };
constexpr int SCEEN_HEIGHT{ 620};
std::stringview title {" key_state" };

struct Texture_manager
{
    Texture_manager() = default;
    ~Texture_manager() = default;


    void free();
    bool load_from_file(std::stringview filename, SDL_Renderer* t_renderer);
    bool load_from_text(std::stringview Text_to_render, SDL_Color& t_color, SDL_Renderer* t_renderer);


    // render on screen functions
    void render_to_screen(SDL_Renderer* t_renderer)
    {
        SDL_RenderCopy(t_renderer, m_current_texture);
    }
    
    void render_to_quad(SDL_Renderer* t_renderer, const SDL_Rect* t_src_rect,const SDL_Rect* t_dest_rect,
                        const double t_rotation_angle , const SDL_Point* t_rotation_center, const SDLRenderFlip t_flip)

    

    //  transparency manuplitation
    void alter_transparency(Uint8 t_alpha);
    void set_blending_mode (const SDL_BlendMode& t_blend_flag);
    void alter_color(const SDL_Color& t_color);

     
        
    int get_width()  const  { return m_width;}
    int get_height() const  { return m_height;};
   


    SDL_Texture* m_current_texture{nullptr};
   

    SDL_Color    m_color{ nullptr};

    int m_height{};
    int m_width {};
};

void Texture_manager::render_to_quad(SDL_Renderer* t_renderer, const SDL_Rect* t_src_rect,const SDL_Rect* t_dest_rect,
                        const double t_rotation_angle , const SDL_Point* t_rotation_center, const SDLRenderFlip t_flip)
  {
      SDL_RenderCopy(t_renderer, m_current_texture, t_src_rect, t_dest_rect, angle,t_rotation_center, t_flip);
  }

void Texture_manager::render_to_screen(SDL_Renderer* t_renderer)
  {
        SDL_RenderCopy(t_renderer, m_current_texture);
  }


void Texture_manager::alter_transparency(Uint8 t_alpha)
{
   m_color.a = t_alpha;
   SDL_SetTextureAlphaMod(m_current_texture,alpha);
}

void Texture_manager::set_blending_mode(const SDL_BlendMode& t_blend_flag)
{
    SDL_setTextureBlendMode(m_current_texture, t_blend_flag);
}
    


bool Texture_manager::load_from_file(std::stringview filename, SDL_Renderer* t_renderer)
{
   SDL_Surface* tmp = IMG_Load(filename.data());

   if(tmp ==nullptr)
   {
       puts("can't load image);
       return false;
   }

   m_current_texture = SDL_CreateTextureFromSurface(t_renderer, tmp);
   SDL_QueryTexture(m_current_texture,nullptr,nullptr, &m_width, &m_height);
   SDL_FreeSurface(tmp);

   return true;
}

 void Texture_manager::load_from_text(std::stringview Text_to_render, SDL_Color& t_color, SDL_Renderer* t_renderer)
{
    SDL_Surface* tmp = TTF_RenderTextSolid(m_font, t_text_to_render.data(), t_color);

    if(tmp == nullptr)
    {
        puts("can't create surface from text);
        puts(TTF_GetError());
        return false;
    }

    m_current_texture = SDL_CreateTextureFromSurface(t_renderer, tmp);
   SDL_QueryTexture(m_current_texture,nullptr,nullptr, &m_width, &m_height);
   SDL_FreeSurface(tmp);

   return true;
 
}

void Texture_manager::free()
{
    SDL_FreeTexture(m_current_texture);
    m_current_texture = nullptr;
}

struct Game
{
    
    Game() = default;
    ~Game() = default;

    void init();
    void input();
    void update();
    void render();
    void close();

   SDL_Renderer* m_renderer{nullptr};
   SDL_Window*  m_window  {nullptr};

   bool m_running {false};
   Uint8 m_next_Texture {0};
   Texture_manager m_texture_array[4];
   TTF_Font*    m_font {nullptr};
};



void Game::init()
{
  if(SDL_Init(SDL_INIT_VEDIO))
  {
      puts("can't init SDL);
      return ;
  }

  m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if(!m_window)
  {
    puts("can't create window);
    return;
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
  if(!m_renderer)
  {
    puts("can't create renderer);
    return ;
  }
  
  if(!Init_IMG(INIT_IMG_PNG) & INIT_IMG_PNG)
  {
      puts(" cant' init image subsystem);
      return;
  }


 if(TTF_Init() == -1)
 {
     puts("can't init font subsystem);
     return ;
 }

 m_font = TTF_OpenFont("asset/font/lazy.ttf", 18);

 if(m_font== nullptr)
 {
     putst("can't open font");
     return ;
 }

 // Create texture from images or text here
 // by functions : load_from_file or load_from_text and assigned it to proper texture in texture_array
}

int main()
{


    //main loop
    Game game;
    game.init();

    while (game.running())
    {

        game.input();
        game.update();
        game.render();
    }
    game.close();
    return 0;
}
