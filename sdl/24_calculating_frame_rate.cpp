#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include <string_view>
#include <sstream>
#include <iostream>

constexpr int SCREEN_WIDTH{ 480 };
constexpr int SCREEN_HEIGHT{ 620};
std::string_view title {" key_state" };




struct Timer
{

    Timer()
    {
        m_start_time = SDL_GetPerformanceCounter();

    }
    
    ~Timer()
    {
        auto end = SDL_GetPerformanceCounter();

        auto elapsed_Ms = (end - m_start_time)/(static_cast<float>(SDL_GetPerformanceFrequency())) * 1000.f;

        std::cout<<"elapsed time " << elapsed_Ms<<'\n';
    }


    void start();
    void stop();

    uint64_t elapsed();

    bool isStarted() const ;
    bool isPaused() const ;

    uint64_t m_start_time {0};
    uint64_t m_interval_start{0};
    uint64_t m_elapsed {0};
    enum  class state_t{  STARTED,PAUSED};

    state_t m_timer_state{ state_t::PAUSED};
};

void Timer::start()
{
        if( isPaused())
        {
          std::cout<<"start entered \n";
          m_interval_start = SDL_GetPerformanceCounter() ; 
          m_timer_state = state_t::STARTED;
        }
}

void Timer::stop()
{
    if( isStarted())
    {
      auto interval_end = SDL_GetPerformanceCounter();
      m_elapsed += static_cast <int64_t> ((interval_end - m_interval_start)/(static_cast<float>(SDL_GetPerformanceFrequency())) * 1000.f);
      m_interval_start= 0;
      m_timer_state = state_t::PAUSED;
    }

}


bool Timer::isStarted() const 
{
    return m_timer_state == state_t::STARTED;
}

bool Timer::isPaused() const 
{
   return m_timer_state == state_t::PAUSED;
}

uint64_t Timer::elapsed()
{
    if(isStarted())
    {
      auto interval_end = SDL_GetPerformanceCounter();
      m_elapsed += static_cast <int64_t> ((interval_end - m_interval_start)/(static_cast<float>(SDL_GetPerformanceFrequency())) * 1000.f);
 
    }
    return m_elapsed;
}

struct Sound_manager 
{
    union
    {
        Mix_Chunk* m_chunk;
        Mix_Music* m_music;
    }m_sound;
   
    enum class  sound_type
   {
    NONE,
    CHUNK,
    MUSIC
   };
   

   sound_type m_type{sound_type::NONE};

   bool load_Music(std::string_view filename);
   bool load_Effect(std::string_view filename);

   void free();
};

bool Sound_manager::load_Music(std::string_view filename)
{

  m_sound.m_music = Mix_LoadMUS(filename.data());
  m_type = sound_type::MUSIC;
  return nullptr == m_sound.m_music;
}

bool Sound_manager::load_Effect(std::string_view filename)
{
  m_sound.m_chunk = Mix_LoadWAV(filename.data());
  m_type = sound_type::CHUNK;
  return nullptr == m_sound.m_chunk;
}


void Sound_manager::free()
{

    switch(m_type)
    {
        case sound_type::CHUNK:
            Mix_FreeChunk(m_sound.m_chunk);
        case sound_type::MUSIC:
            Mix_FreeMusic(m_sound.m_music);
            m_sound.m_music = nullptr;
    }
}


struct Texture_manager
{
    Texture_manager() = default;
    ~Texture_manager() = default;


    void free();
    bool load_from_file(std::string_view filename, SDL_Renderer* t_renderer);
    bool load_from_text(std::string_view t_text_to_render, const SDL_Color& t_color, SDL_Renderer* t_renderer,TTF_Font* t_font);



    // render on screen functions
    void render_to_screen(SDL_Renderer* t_renderer);
    
    void render_to_quad(SDL_Renderer* t_renderer, const SDL_Rect* t_src_rect,SDL_Rect* t_dest_rect,
                        const double t_rotation_angle , const SDL_Point* t_rotation_center, const SDL_RendererFlip  t_flip = SDL_FLIP_NONE);

    

    //  transparency manuplitation
    void alter_transparency(uint8_t t_alpha);
    void set_blending_mode (const SDL_BlendMode& t_blend_flag);
    void alter_color(const SDL_Color& t_color);

     
        
    int get_width()  const  { return m_width;}
    int get_height() const  { return m_height;};
   


    SDL_Texture* m_current_texture{nullptr};
   

    SDL_Color    m_color{ };

    int m_height{};
    int m_width {};
};

void Texture_manager::render_to_quad(SDL_Renderer* t_renderer, const SDL_Rect* t_src_rect,SDL_Rect* t_dest_rect,
                        const double t_rotation_angle , const SDL_Point* t_rotation_center, const SDL_RendererFlip  t_flip)

  {
      if(t_dest_rect)
      {
            t_dest_rect->w = m_width;
            t_dest_rect->h = m_height;
      }
      SDL_RenderCopyEx(t_renderer, m_current_texture, t_src_rect, t_dest_rect, t_rotation_angle ,t_rotation_center, t_flip);
  }

void Texture_manager::render_to_screen(SDL_Renderer* t_renderer)
  {
        SDL_RenderCopy(t_renderer, m_current_texture,nullptr,nullptr);
  }


void Texture_manager::alter_transparency(uint8_t t_alpha)
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

 bool Texture_manager::load_from_text(std::string_view t_text_to_render,const SDL_Color& t_color, SDL_Renderer* t_renderer,TTF_Font* t_font)
{
    SDL_Surface* tmp = TTF_RenderText_Solid(t_font, t_text_to_render.data(), t_color);

    if(tmp == nullptr)
    {
        puts("can't create surface from text");
        puts(TTF_GetError());
        return false;
    }

   m_width = tmp->w;
   m_height = tmp->h;
   m_current_texture = SDL_CreateTextureFromSurface(t_renderer, tmp);

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
   Texture_manager m_prompt_texture;
   Texture_manager m_time_passed_texture;

   Timer m_time{};
   int32_t m_counted_frames{};

   TTF_Font*    m_font {nullptr};
};



void Game::init()
{ 
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
  {
      printf("can't init SDL %s\n", SDL_GetError());
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

 m_font = TTF_OpenFont("asset/font/lazy.ttf", 24);

 if(m_font== nullptr)
 {
     puts("can't open font");
     return ;
 }

 if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT, 2 , 2048) < 0)
 {
     printf("SDL_Mixer cound not initialza! %s\n" , Mix_GetError());
     return;
 }

 m_running = true;
 // Create texture from images or text here
 // by functions : load_from_file or load_from_text and assigned it to proper texture in texture_array


 m_prompt_texture.load_from_text(" average Frame per second,",{0,0xff,0,0xff},m_renderer,m_font);

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

    if(  currentKeyStates[SDL_SCANCODE_S])
    {
        m_time.start();
    }
    else if(m_time.isStarted() && currentKeyStates[SDL_SCANCODE_P])
    {
        m_time.stop();
    }
    else if(m_time.isPaused() && currentKeyStates[SDL_SCANCODE_U])
    {
        m_time.start();
    }
}

void Game::render()
{


    //clear screen
    SDL_SetRenderDrawColor(m_renderer, 0xFF,0xFF,0xFF,0xff);
    SDL_RenderClear(m_renderer);

    //render current texture
    //m_texture_array[m_next_Texture].render_to_screen( m_renderer);

    SDL_Rect quad{0 ,0, 480,620};
    m_prompt_texture.render_to_quad(m_renderer,nullptr,&quad,0,nullptr);


    float average_fps = m_counted_frames/(SDL_GetTicks()/1000.f);

    std::string s="";
    s+= std::to_string(average_fps);
    s+='\0';

    m_time_passed_texture.load_from_text(s.c_str(),{0,0xff,0,0xff},m_renderer,m_font);
    quad.y += 20;
    m_time_passed_texture.render_to_quad(m_renderer, nullptr, &quad, 0,nullptr);

    
    //update screen
    SDL_RenderPresent(m_renderer);

    ++m_counted_frames;
}


void Game::close()   
{     
	SDL_DestroyRenderer(m_renderer);     
	SDL_DestroyWindow(m_window);     
	m_renderer=nullptr;     
	m_window = nullptr;      
	

    Mix_Quit();
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
