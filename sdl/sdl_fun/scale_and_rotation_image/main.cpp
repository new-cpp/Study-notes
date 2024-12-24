#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <string>

constexpr int m_height{480};
constexpr int m_width{640};
const std::string title("title");



struct Game
{
    void init();
    void update();
    void input();
    void render();
    void close();


    bool is_running()
    {
        return m_running;
    }

    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
    bool m_running{true};
    
};

void Game::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        printf("%s\n",SDL_GetError());
        m_running = false;
    }

    m_window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,m_height,m_width,SDL_WINDOW_SHOWN);


    if(!m_window)
    {
        printf("%s\n",SDL_GetError());
        m_running = false;

    }
    
    m_renderer = SDL_CreateRenderer(m_window, -1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!m_renderer)
    {
         printf("%s\n",SDL_GetError());
        m_running = false;

    }


}

void Game::input()
{
    SDL_Event e;
    while(SDL_PollEvent(&e)!=0)
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
void Game::close()
{

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    m_renderer = nullptr;
    m_window = nullptr;
    SDL_Quit();
}


void Game::render()
{

    SDL_SetRenderDrawColor(m_renderer, 0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(m_renderer);
    
    SDL_Rect rect{40,80,100,100};
    SDL_SetRenderDrawColor(m_renderer, 0x0A,0x0A,0x0A,0xFF);
    SDL_RenderDrawRect(m_renderer, &rect );

    Sint16 vx[] = { 100, 300, 200 };
	Sint16 vy[] = { 100, 100, 300 };
    filledPolygonColor(m_renderer, vx, vy, 3, 0xFFFF0000);

    thickLineColor(m_renderer, 0, 0, m_width, m_height, 20, 0xFF00FFFF) ;
    thickLineColor(m_renderer, 0, m_height, m_width, 0, 20, 0xFF00FFFF) ;
    SDL_RenderPresent(m_renderer);
    SDL_Delay(10);
}

struct App
{

    App()=default;
    ~App() = default;
    void run();
};

void App::run()
{

    Game game;
    game.init();

    while(game.is_running())
    {
        game.input();
        game.update();
        game.render();
    }
    game.close();
}

int main( int argc, char* argv[])
{
    
    
    App app;

    app.run();


    return 0;

}
