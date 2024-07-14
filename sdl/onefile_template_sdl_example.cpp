#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include <string>
#include <string_view>


constexpr int SCREEN_WIDTH{ 480 };
constexpr int SCREEN_HEIGHT{ 620};
std::string_view title {" key_state" };

struct Texture_manager
{
    Texture_manager() = default;
    ~Texture_manager() = default;


    void free();
    bool load_from_file(std::string_view filename, SDL_Renderer* t_renderer);
    bool load_from_text(std::string_view t_text_to_render, SDL_Color& t_color, SDL_Renderer* t_renderer,TTF_Font* t_font);



    // render on screen functions
    void render_to_screen(SDL_Renderer* t_renderer);
    
    void render_to_quad(SDL_Renderer* t_renderer, const SDL_Rect* t_src_rect,const SDL_Rect* t_dest_rect,
                        const double t_rotation_angle , const SDL_Point* t_rotation_center, const SDL_RendererFlip  t_flip);

    

    //  transparency manuplitation
    void alter_transparency(Uint8 t_alpha);
    void set_blending_mode (const SDL_BlendMode& t_blend_flag);
    void alter_color(const SDL_Color& t_color);

     
        
    int get_width()  const  { return m_width;}
    int get_height() const  { return m_height;};
   


    SDL_Texture* m_current_texture{nullptr};
   

    SDL_Color    m_color{ };

    int m_height{};
    int m_width {};
};

void Texture_manager::render_to_quad(SDL_Renderer* t_renderer, const SDL_Rect* t_src_rect,const SDL_Rect* t_dest_rect,
                        const double t_rotation_angle , const SDL_Point* t_rotation_center, const  SDL_RendererFlip t_flip)
  {
      SDL_RenderCopyEx(t_renderer, m_current_texture, t_src_rect, t_dest_rect, t_rotation_angle ,t_rotation_center, t_flip);
  }

void Texture_manager::render_to_screen(SDL_Renderer* t_renderer)
  {
        SDL_RenderCopy(t_renderer, m_current_texture,nullptr,nullptr);
  }


void Texture_manager::alter_transparency(Uint8 t_alpha)
{
   m_color.a = t_alpha;
   SDL_SetTextureAlphaMod(m_current_texture,t_alpha);
}

void Texture_manager::set_blending_mode(const SDL_BlendMode& t_blend_flag)
{
    SDL_SetTextureBlendMode(m_current_texture, t_blend_flag);
}
    
bool Texture_manager::load_from_file(std::string_view filename, SDL_Renderer* t_renderer) 
{
    SDL_Surface* tmp = IMG_Load(filename.data());

   if(tmp ==nullptr)
   {
       puts("can't load image");
       return false;
   }

   m_current_texture = SDL_CreateTextureFromSurface(t_renderer, tmp);
   SDL_QueryTexture(m_current_texture,nullptr,nullptr, &m_width, &m_height);
   SDL_FreeSurface(tmp);

   return true;
}

 bool Texture_manager::load_from_text(std::string_view t_text_to_render, SDL_Color& t_color, SDL_Renderer* t_renderer,TTF_Font* t_font)
{
    SDL_Surface* tmp = TTF_RenderText_Solid(t_font, t_text_to_render.data(), t_color);

    if(tmp == nullptr)
    {
        puts("can't create surface from text");
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
    SDL_DestroyTexture(m_current_texture);
    m_current_texture = nullptr;
}

struct Game
{
    
    Game() = default;
    ~Game() = default;

    void init();
    void input() ; 
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
  if(SDL_Init(SDL_INIT_VIDEO))
  {
      puts("can't init SDL");
      return ;
  }

  m_window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if(!m_window)
  {
    puts("can't create window");
    return;
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
  if(!m_renderer)
  {
    puts("can't create renderer");
    return ;
  }
  
  if(!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
  {
      puts(" cant' init image subsystem");
      return; 
  }

  if(TTF_Init() == -1)
 {
     puts("can't init font subsystem");
     return ;
 }

 m_font = TTF_OpenFont("asset/font/lazy.ttf", 18);

 if(m_font== nullptr)
 {
     puts("can't open font");
     return ;
 }

 m_running = true;
 // Create texture from images or text here
 // by functions : load_from_file or load_from_text and assigned it to proper texture in texture_array
}



void Game::input()
{

    SDL_Event e;
    while(SDL_PollEvent(&e) !=0)
    {
        if(e.type == SDL_QUIT)
        {
            m_running = false;
        }
    }
}

void Game::update()
{

    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

    if(currentKeyStates[SDL_SCANCODE_UP])
    {
      m_next_Texture = 0;    
    }
    else if(currentKeyStates[SDL_SCANCODE_DOWN])
    {
        m_next_Texture = 1;
    }
    else
    {
      m_next_Texture = 2;
    }
}

void Game::render()
{


    //clear screen
    SDL_SetRenderDrawColor(m_renderer, 0xFF,0xFF,0xFF,0xff);
    SDL_RenderClear(m_renderer);

    //render current texture
    //m_texture_array[m_next_Texture].render_to_screen( m_renderer);

    
    //update screen
    SDL_RenderPresent(m_renderer);
}


void Game::close()   
{     
	SDL_DestroyRenderer(m_renderer);     
	SDL_DestroyWindow(m_window);     
	m_renderer=nullptr;     
	m_window = nullptr;      
	//m_textureManager.free();      
	IMG_Quit();     
	SDL_Quit();    
}
int main()
{


    //main loop
    Game game;
    game.init();

    while (game.m_running)
    {

        game.input();
        game.update();
        game.render();
    }
    game.close();
    return 0;
}
