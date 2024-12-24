#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string_view>
#include <vector>


const int SCREEN_HEIGHT = 400;
const int SCREEN_WIDTH  = 600;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer= nullptr;




bool g_running = true;

void load_from_file(std::string_view path,SDL_Texture** t_texture,int& t_height,
        int& t_width)
{
	std::printf("%s %p\n",__FUNCTION__,(void*)t_texture);
	SDL_Surface* loadedSurface = IMG_Load(path.data());
	if(loadedSurface== nullptr)
	{
		puts("can't load image");
		return;
	}

    //Color key image
	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format,                    0, 0xFF, 0xFF ) );

	*t_texture = SDL_CreateTextureFromSurface(g_renderer,loadedSurface);
    if(*t_texture == nullptr)
    {
	    std::printf("%s %s\n",__FUNCTION__,SDL_GetError());
    }
    else
    {
        t_height = loadedSurface->h;
        t_width  = loadedSurface->w;
    }

	SDL_FreeSurface(loadedSurface);
	
}


class Dot
{
    public:
	 static const int DOT_HEIGHT = 20;
	 static const int DOT_WIDTH  = 20;

	 static const int DOT_VEL    = 1;

	 Dot(int x ,int y);
	 void handleEvent(const SDL_Event& e);
	 void move(std::vector<SDL_Rect>& othersColliders);
	
     void render(SDL_Rect* clip = NULL, double angle = 0.0, 
          SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) ;
	 
     std::vector<SDL_Rect>& getColliders();

	 SDL_Texture* m_texture = nullptr;
     int m_texture_height;
     int m_texture_width;

	 SDL_Texture* getTexture()
	 {
		return m_texture;
	}
   private:
	 int mPosX,mPosY;
	 int mVelX,mVelY;

	 std::vector<SDL_Rect> m_colliders;

	 void shiftColliders();
};

Dot::Dot(int x ,int y)
{
	mPosX = x;
	mPosY = y;

	m_colliders.resize(11);
	mVelX = 0;
	mVelY = 0;

	m_colliders[0].w = 6;
	m_colliders[0].h = 1;

        m_colliders[1].w = 10;
	m_colliders[1].h = 1;

	
	m_colliders[2].w = 14;
	m_colliders[2].h = 1;

	m_colliders[3].w = 16;
	m_colliders[3].h = 2;

	m_colliders[4].w = 18;
	m_colliders[4].h = 2;
	
	m_colliders[5].w = 20;
	m_colliders[5].h = 6;

	m_colliders[6].w = 18;
	m_colliders[6].h = 2;
	
	m_colliders[7].w = 16;
	m_colliders[7].h = 2;

	m_colliders[8].w = 14;
	m_colliders[8].h = 1;

	m_colliders[9].w = 10;
	m_colliders[9].h = 1;

	m_colliders[10].w = 6;
	m_colliders[10].h = 1;

	shiftColliders();
}



Dot dot(0,0);
Dot otherDot(SCREEN_WIDTH/4,SCREEN_HEIGHT/4);




void Dot::handleEvent(const SDL_Event& e) 
{
	//If a key was pressed     
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{         //Adjust the velocity         
		  switch( e.key.keysym.sym )         
		  {             
			  case SDLK_UP: mVelY-= DOT_VEL; 
			   break;             
			  case SDLK_DOWN: mVelY+= DOT_VEL; 
			  break;             
			  case SDLK_LEFT: mVelX-= DOT_VEL; 
			  break;             
			  case SDLK_RIGHT: mVelX+= DOT_VEL; 
			  break;         
		  }     
	}    
	//If a key was released     
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 )     
	{         //Adjust the velocity         
		  switch( e.key.keysym.sym )         
		  {             
		 	 case SDLK_UP:   mVelY+= DOT_VEL; break;             
			 case SDLK_DOWN: mVelY-= DOT_VEL; break;             			     
			 case SDLK_LEFT: mVelX+= DOT_VEL; break;             		            
			case SDLK_RIGHT: mVelX-= DOT_VEL; break;         
		  }     
	} 
}

void Dot::render( SDL_Rect* clip, double angle, 
        SDL_Point* center, SDL_RendererFlip flip )

{
   //Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, DOT_WIDTH,DOT_HEIGHT };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( g_renderer, m_texture, clip, &renderQuad, angle, center, flip );
}

bool is_running()
{
	return g_running;
}
void init()
{
if(SDL_Init(SDL_INIT_VIDEO))
   {
     g_running = false;
     std::printf("can't init SDL %s",SDL_GetError());
     return;
   }

  g_window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if(g_window == nullptr)
  {
     g_running = false;
     std::printf("can't create window %s",SDL_GetError());
     return;
  }

  g_renderer = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);

  if(g_renderer == nullptr)
  { 
     g_running = false;
     std::printf(" can't create renderer %s",SDL_GetError());
     return;
  }

  if(!IMG_Init(IMG_INIT_PNG)& IMG_INIT_PNG)
  {
	puts("can't init image subsystem");
	return;
  }


  load_from_file(std::string_view("asset/dot_2.bmp"),&dot.m_texture,dot.m_texture_height,dot.m_texture_width);
  load_from_file(std::string_view("asset/dot_2.bmp"),&otherDot.m_texture,dot.m_texture_height,dot.m_texture_width);

}

void input()
{
 SDL_Event e;
 while(SDL_PollEvent(&e))
 {
   if(e.type == SDL_QUIT)
   {
     g_running = false;
   }
   dot.handleEvent(e);
 }
}


void update(double dt = 0)
{
 dot.move(otherDot.getColliders()); 
}

void render()
{
  SDL_SetRenderDrawColor(g_renderer,0xff,0xff,0xff,0xff);
  SDL_RenderClear(g_renderer);


  SDL_Rect m_wall{40,40,40,40};
 SDL_SetRenderDrawColor(g_renderer, 0x00,0x16,0x00,0xff);     
 SDL_RenderDrawRect(g_renderer,&m_wall);  
 
 dot.render();
  otherDot.render();
  SDL_RenderPresent(g_renderer);
}
void close() { 
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow( g_window);

   g_renderer=nullptr;
   g_renderer=nullptr;

   IMG_Quit();
   SDL_Quit();

}


bool checkCollision(std::vector<SDL_Rect>& a , std::vector<SDL_Rect>& b)
{
//  for(const auto& boxA : a)
//  {
//	for(const auto& boxB : b)
//	{
//		if(SDL_IntersectRect(&boxA,&boxB,nullptr))
//		 return true;
//	}
// }
//  return false;
//The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Go through the A boxes
    for( int Abox = 0; Abox < a.size(); Abox++ )
    {
        //Calculate the sides of rect A
        leftA = a[ Abox ].x;
        rightA = a[ Abox ].x + a[ Abox ].w;
        topA = a[ Abox ].y;
        bottomA = a[ Abox ].y + a[ Abox ].h;

        //Go through the B boxes
        for( int Bbox = 0; Bbox < b.size(); Bbox++ )
        {
            //Calculate the sides of rect B
            leftB = b[ Bbox ].x;
            rightB = b[ Bbox ].x + b[ Bbox ].w;
            topB = b[ Bbox ].y;
            bottomB = b[ Bbox ].y + b[ Bbox ].h;

            //If no sides from A are outside of B
            if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
            {
                //A collision is detected
                return true;
            }
        }
    }

    //If neither set of collision boxes touched
    return false;
}


void Dot::move(std::vector<SDL_Rect>& othersColliders)
{

	mPosX += mVelX;

	shiftColliders();

 	if((mPosX <0)	|| (mPosX + DOT_WIDTH > SCREEN_WIDTH) || checkCollision(m_colliders , othersColliders))
	{
	    mPosX -=mVelX;
	    shiftColliders();
	}


	mPosY += mVelY;
	shiftColliders();

 	if((mPosY <0)	|| (mPosY + DOT_HEIGHT> SCREEN_HEIGHT) || checkCollision(m_colliders , othersColliders)) { 
	    mPosY -=mVelY;
	    shiftColliders();
	}

}
void Dot::shiftColliders()
{
    int r = 0;

    for(int set = 0 ;set < m_colliders.size();++set)
    {
	m_colliders[set].x = mPosX + (DOT_WIDTH + m_colliders[set].w)/2;
	m_colliders[set].y = mPosY + r;

	r+=m_colliders[set].h;
   }
}


std::vector<SDL_Rect>& Dot::getColliders()
{
	return m_colliders;
}

int main()
{

	uint32_t delta = 0;
	uint32_t last_tick_time = 0;
	init();
	
	while(is_running())
	{
	    uint32_t tick_time = SDL_GetTicks();

	    delta = tick_time - last_tick_time;
	    last_tick_time = tick_time;

	    input();
	    update(delta);
	    render();
	}
	close();

	return EXIT_SUCCESS;
}
