#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

const int SCREEN_HIGHT = 600;
const int SCREEN_WIDTH = 900;
const int LINE_WIDTH   = 2;


const int cell_size = 30;


SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;

bool is_running = true;

enum class STATE { PROCESSING, INPUT_CONFIGURATION };
STATE g_state = STATE::INPUT_CONFIGURATION;

const int lig= SCREEN_WIDTH / cell_size;
const int col= SCREEN_HIGHT / cell_size;

int curr_generation[lig][col];
int next_generation[lig][col];

int dx[8] = {1,0,0,-1,1,1,-1,-1};
int dy[8] = {0,1,-1,0,1,-1,1,-1};



void calculate_next_generation() 
{
   
    for(int i = 0 ; i < lig ; ++i)
    {
        
        for(int j = 0 ; j < col; ++j)
        {
            
            int nb_of_living_neighbours=0;
            for(int k = 0 ; k < 8;++k)
            {
                int nx_i = i + dx[k];
                int nx_j = j + dy[k];

                if(curr_generation[nx_i][nx_j])
                    ++nb_of_living_neighbours;
            }

            if(curr_generation[i][j]) // curr cell is alive
            {
                if(nb_of_living_neighbours <2) // less than 2 die
                    next_generation[i][j] = 0;
                else if (nb_of_living_neighbours >3) // more than 3 die
                    next_generation[i][j] = 0;
                else if(nb_of_living_neighbours <=3) // 2 or 3 live
                    next_generation[i][j] = 1;

            }
            else if(nb_of_living_neighbours == 3)
                next_generation[i][j] = 1;
            
        }
    }


    memcpy(curr_generation ,next_generation , sizeof(curr_generation));

  
}

void set_cell(int x , int y)
{
    curr_generation[x][y] = 1;
}

void unset_cell(int x ,int y)
{
    curr_generation[x][y] = 0;
}

void fill_cell(int i , int j)
{
    SDL_Rect rect = {.x = i*cell_size,.y = j*cell_size,.w=cell_size,.h=cell_size};
    SDL_SetRenderDrawColor(g_renderer,0xff,0xff,0xff,0xff);
    SDL_RenderFillRect(g_renderer, &rect);
}

void fill_cells()
{
   for(int i = 0 ; i < lig;++i)
   {
       for(int j = 0 ; j < col; ++j)
       {
            if(curr_generation[i][j])
            {
                fill_cell(i,j);
            }
       }
   }

}


void draw_grid()
{
    //draw column
    for(int x= cell_size ; x <SCREEN_WIDTH; x+=cell_size)
    {
        SDL_Rect rect = {.x=x,.y = 0, .w = LINE_WIDTH,.h=SCREEN_HIGHT};
        SDL_SetRenderDrawColor(g_renderer,0x2f,0x2f,0x2f,0xff);
        SDL_RenderDrawRect(g_renderer,&rect);
    }

    //draw ligne
    for(int y = cell_size ; y < SCREEN_WIDTH; y+=cell_size)
    {
        SDL_Rect rect = {.x=0,.y = y, .w = SCREEN_WIDTH, .h=LINE_WIDTH};
        SDL_SetRenderDrawColor(g_renderer,0x2f,0x2f,0x2f,0xff);
        SDL_RenderDrawRect(g_renderer,&rect);

    }
}

void init()
{
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        is_running = false;
        printf("%s\n",SDL_GetError());
        return;
    }

    g_window = SDL_CreateWindow("game of life",SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HIGHT,SDL_WINDOW_SHOWN);

    if(g_window == NULL)
    {
        is_running = false;
        printf("%s\n",SDL_GetError());
        return;
    }

    g_renderer = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(g_renderer == NULL)
    {
        is_running = false;
        printf("%s\n", SDL_GetError());
        return;
    }

}


void input()
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            is_running = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym == SDLK_ESCAPE)
            {
                //TODO: empty out the matrix
                g_state = STATE::INPUT_CONFIGURATION;
            }
        }
    }
}

void init_input()
{

    printf("inside init_input\n");
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            is_running = false;
        }
        else if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym )
            {
                case SDLK_SPACE :
                            //TODO:: check if the matrix is empty
                            g_state = STATE::PROCESSING;
                            break;

                case SDL_MOUSEBUTTONDOWN:     switch (event.button.button)     {         case SDL_BUTTON_LEFT:             SDL_ShowSimpleMessageBox(0, "Mouse", "Left button was pressed!", g_window);             break;         case SDL_BUTTON_RIGHT:             SDL_ShowSimpleMessageBox(0, "Mouse", "Right button was pressed!", g_window);             break;         default:             SDL_ShowSimpleMessageBox(0, "Mouse", "Some other button was pressed!", g_window);             break;     }
                //case SDL_MOUSEBUTTONDOWN:
                 //   switch (event.button.button)     
                  //  {
                   //      case SDL_BUTTON_LEFT:             
                    //       SDL_ShowSimpleMessageBox(0, "Mouse", "Left button was pressed!", g_window);             
                     //      int xPos,yPos;
                      //     SDL_GetMouseState(&xPos, &yPos);
                          
                       //    printf("mouse position : %d %d\n",xPos, yPos);                      
                        //   set_cell((xPos + cell_size -1)/cell_size, (yPos + cell_size -1)/cell_size);
                        //   break;
                    //TODO: case for double click to unset 
              //  }
            }
        }
    }
}

void update(double dt = 0)
{
   calculate_next_generation(); 
}

void render()
{
    
    SDL_SetRenderDrawColor(g_renderer, 0x00,0x00,0x00,0xff);
    SDL_RenderClear(g_renderer);


    fill_cells();
    draw_grid();  

    SDL_RenderPresent(g_renderer);
    SDL_Delay(500);
}

void close()
{
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

    g_renderer = NULL;
    g_window = NULL;

    SDL_Quit();
}
int main()
{

    init();

    while(is_running)
    {
        if(g_state == STATE::INPUT_CONFIGURATION)
        {
            init_input();
        }
        else if(g_state == STATE::PROCESSING)
        {
            printf("PROCESSING\n");
            input();
            update();
        }
        render();
    }
    close();
    return 0;
}
