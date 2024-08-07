#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include <string_view>


constexpr int SCREEN_WIDTH{ 480 };
constexpr int SCREEN_HEIGHT{ 620};
std::string_view title {" key_state" };


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
            m_sound.m_chunk = nullptr;
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
   Uint8 m_next_sound{0};
   Texture_manager m_texture;
   Sound_manager m_sounds[5];
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

m_sounds[0].load_Effect("asset/sound/scratch.wav");
m_sounds[1].load_Effect("asset/sound/high.wav");
m_sounds[2].load_Effect("asset/sound/low.wav");
m_sounds[3].load_Effect("asset/sound/medium.wav");
m_sounds[4].load_Music("asset/sound/beat.wave");

m_texture.load_from_text("choose number from 0 to 4",{0,0xff,0,0xff},m_renderer,m_font);

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

    if(currentKeyStates[SDL_SCANCODE_0])
    {
        // play first sound effect
        Mix_PlayChannel(-1,m_sounds[0].m_sound.m_chunk,0);
        puts(" 0 was pressed");

    }
    else if(currentKeyStates[SDL_SCANCODE_1])
    {
        // play second sound effect
        puts("1 was pressed");
        Mix_PlayChannel(-1,m_sounds[1].m_sound.m_chunk,0);

    }
    else if(currentKeyStates[SDL_SCANCODE_2])
    {
        // play second sound effect
        puts("2 was pressed");
        Mix_PlayChannel(-1,m_sounds[2].m_sound.m_chunk,0);
    }
    else if(currentKeyStates[SDL_SCANCODE_3])
    {
        // play third sound effect
        puts("3 was pressed");
        Mix_PlayChannel(-1,m_sounds[3].m_sound.m_chunk,0);
    }
    else if (currentKeyStates[SDL_SCANCODE_4])
    {
        // play music 
        puts("4 was pressed");
        if( Mix_PlayingMusic() == 0 )
        {
            Mix_PlayMusic( m_sounds[4].m_sound.m_music, -1 );
        }
  
    }
    else if (currentKeyStates[SDL_SCANCODE_5])
    {
        //resume music
        if(Mix_PlayingMusic())
        {
            if( Mix_PausedMusic() == 1)
                Mix_ResumeMusic();
        }
    }
    else if (currentKeyStates[SDL_SCANCODE_6])
    {
        //pause musiv
        if(Mix_PlayingMusic())
        {
            if(Mix_PausedMusic() != 1)
                Mix_PauseMusic();
        }
    }
    //halt music
    else if(currentKeyStates[SDL_SCANCODE_7])
         Mix_HaltMusic();
    
}

void Game::render()
{


    //clear screen
    SDL_SetRenderDrawColor(m_renderer, 0xFF,0xFF,0xFF,0xff);
    SDL_RenderClear(m_renderer);

    //render current texture
    //m_texture_array[m_next_Texture].render_to_screen( m_renderer);

    SDL_Rect quad{ 10,10,0,0};
    m_texture.render_to_quad(m_renderer,nullptr,&quad,0,nullptr);


    
    //update screen
    SDL_RenderPresent(m_renderer);
}


void Game::close()   
{     
	SDL_DestroyRenderer(m_renderer);     
	SDL_DestroyWindow(m_window);     
	m_renderer=nullptr;     
	m_window = nullptr;      
	
    m_texture.free();
    for(int i = 0 ; i < 5;++i)
        m_sounds[i].free();

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
