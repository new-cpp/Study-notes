/*
 * flood algorithm : identifies the connected components 
 *  		     a cell belong to in a multidemntinal array
 *
 */

const int MAXN = 1000;
int grid[MAXN][MAXN];
bool visited[MAXN][MAXN]; 

int curr_size;  // current connected components size
int h ,w;	

bool out_bound(int i ,int j)
{
	return ( i <0 || i>=h || j < 0 || j >=w);
}

void flood(int i , int j, int color)
{
	if(out_bound(i,j)          ||
	   grid[i][j] != color     ||           //or not the same color
	   visited[i][j] == true)               // or visited
		return ;

	++curr_size;
	visited[i][j] = true;
	// all neighboors
	flood(i+1, j,color);
	flood(i  , j+1,color);
	flood(i -1,j,color);
	flood(i   ,j-1,color);
}

int main()
{
	for(int i = 0 ; i< h ; ++i)
		for(int j = 0 ; j < w ; ++j)
		{
			if(visited[i][j] == false)
			{
				curr_size = 0;
				flood(i,j, grid[i][j]);
			}
		}
	return 0;
}
