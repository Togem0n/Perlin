#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <cstdint>

#include "Perlin.h"
#include "SimplexNoise.h"

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;

bool init();

void close();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	return success;
}

void close()
{
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	SDL_Quit();
}

int main( int argc, char* args[] )
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		bool quit = false;

		SDL_Event e;
		
		// 1d
		//float xoff = 0;
		//for (int y = 0; y < SCREEN_HEIGHT; y++)
		//{
		//	for (int x = 0; x < SCREEN_WIDTH; x++)
		//	{
		//		float noise = (SimplexNoise::noise(xoff) + 1) / 2 * 255;
		//		SDL_Rect fillRect =  {x, y, 1, 1 };
		//		SDL_SetRenderDrawColor( gRenderer, noise, noise, noise, 255);		
		//		SDL_RenderFillRect( gRenderer, &fillRect );
		//		xoff += 0.001;
		//	}
		//}

		// 2d
		//float xoff = 0;
		//float yoff = 0;
		//for (int x = 0; x < SCREEN_WIDTH; x++)
		//{
		//	xoff = 0;
		//	for (int y = 0; y < SCREEN_HEIGHT; y++)
		//	{
		//		float noise = (SimplexNoise::noise(xoff, yoff) + 1) / 2 * 255;
		//		SDL_Rect fillRect =  {x, y, 1, 1 };
		//		SDL_SetRenderDrawColor( gRenderer, noise, noise, noise, 255);		
		//		SDL_RenderFillRect( gRenderer, &fillRect );
		//		xoff += 0.001;
		//	}
		//	yoff += 0.001;
		//}

		SDL_RenderPresent( gRenderer );
		float t = 0;
		while( !quit )
		{
			while( SDL_PollEvent( &e ) != 0 )
			{
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
			}

			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );

			float noise = (SimplexNoise::noise(t) + 1)/2 * SCREEN_HEIGHT;
			printf("%f\n", noise);
			SDL_Rect fillRect = {t * 30, noise, 1, 1 };
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );		
			SDL_RenderFillRect( gRenderer, &fillRect );

			t += 0.01f;

			SDL_RenderPresent( gRenderer );
		}
	}

	close();

	return 0;
}