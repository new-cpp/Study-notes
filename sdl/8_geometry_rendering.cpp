#define SDL_MAIN_HANDLER
#include <SDL2/SDL.h>
#include <string>


struct entity
{
 explicit entity(SDL_Renderer*& r,int w, int h):m_render(r),m_width(w),m_height(h){}

    void draw();
    int m_width,m_height;
    SDL_Rect m_fillRect{m_width/4,m_height/4,m_width/2,m_height/2};;
    SDL_Rect m_rect{m_width/6,m_height/6, m_width*2/3,m_height*2/3};

    SDL_Renderer* m_render;
};
static int  count = 0;
void entity::draw()
  {
     if(count<1)
    printf("%d %d\n",m_fillRect.x,m_fillRect.w);

   // printf("inside draw %p\n", m_render);
    SDL_SetRenderDrawColor(m_render,0xff,0,0,0xff);

    if(count<1)
    printf("%d %d\n",m_fillRect.x,m_fillRect.w);
    SDL_RenderFillRect(m_render,&m_fillRect);

    if(count<1)
    printf("%d %d\n",m_fillRect.x,m_fillRect.w);
    SDL_SetRenderDrawColor(m_render,0,0xff,0,0xff);
    SDL_RenderDrawRect(m_render,&m_rect);

    SDL_SetRenderDrawColor(m_render,0,0,0xff,0xff);
    SDL_RenderDrawLine(m_render,0,m_height/2,m_width,m_height/2);

    SDL_SetRenderDrawColor(m_render,0xff,0xff,0,0xff);
    for(int i = 0;i <m_height; ++i)
      {
        SDL_RenderDrawPoint(m_render,m_width/2,i);
      }
  }


struct App
{
  App()=default;
  void init();
  void input();
  void update(){}
  void render();
  void close();


  bool m_running{true};
  SDL_Window* m_window{ nullptr };
  SDL_Renderer* m_render { nullptr};
  int m_width{640},m_height{480};
  entity e{m_render,m_width,m_height};

  };


void App::init()
  {
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
      {
        puts("can't init");
        return;
      }

    m_window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
                                ,m_width, m_height,SDL_WINDOW_SHOWN);

    if(m_window == nullptr)
      {
        puts("can't create window");
        return;
      }

    m_render = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);

    if(m_render == nullptr)
      {
        puts("can't create render");
        return ;
      }

    e.m_render = m_render;
    e.m_width = m_width;
    e.m_height = m_height;
    SDL_SetRenderDrawColor(m_render, 0xFF,0xFF,0Xff,0xff);
    SDL_RenderClear(m_render);

  }


void App::input()
  {
    SDL_Event e{};
    while(SDL_PollEvent(&e))
      {
        if(e.type == SDL_QUIT)
          m_running = false;
      }

  }


void App::render()
  {
     //wipe the screen

    if(count<1)
      printf("%d %d\n", e.m_rect.x,e.m_rect.h);
    e.draw();
    ++count;
    SDL_RenderPresent(m_render);
  }



void App::close()
  {
    SDL_DestroyRenderer(m_render);
    m_render = nullptr;
    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    SDL_Quit();
  }


int main(int argc, char* argv[])
  {

    App app{};
    printf("main: %d %d \n",app.e.m_rect.x,app.e.m_rect.h);
    app.init();
    while(app.m_running)
      {
        app.input();
        app.update();
        app.render();
      }
    app.close();
  }
