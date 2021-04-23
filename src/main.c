/* Wimg main function */
#include <SDL2/SDL.h>
/*#include <SDL_image.h>*/
#include <wc/io.h>

#define WIN_WIDTH	640
#define WIN_HEIGHT	480

static SDL_Window*	window;		/* Window pointer */
static SDL_Surface*	surface;	/* Surface pointer */
static SDL_Surface* image;		/* Image pointer */

static void init();
static void update();
static void quit();

int main(int argc, char* args[]) {
	init(args[1]);
	while(1) update();
	quit();
	return 0;
}

static void init(char* file) {
	/* Initialize SDL*/
	if(SDL_Init(SDL_INIT_VIDEO) < 0) outl(SDL_GetError());
	/* Create window */
	window = SDL_CreateWindow(
		"Wimg", 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIN_WIDTH,
		WIN_HEIGHT,
		0
	);
	/* Get surface */
	surface = SDL_GetWindowSurface(window);

	//Load image
	if (image = SDL_LoadBMP(file));
	else outl(SDL_GetError());
}

static void update() {
	/* Fill the surface black */
    /* SDL_FillRect(surface, NULL, 0); */
	SDL_BlitSurface(image, NULL, surface, NULL);
    /* Update the surface */
    SDL_UpdateWindowSurface(window);
	/* Event handler */
    SDL_Event e;
	
	while (SDL_PollEvent(&e) != 0) {
		if (
			(e.type == SDL_QUIT) || 
			( (e.type == SDL_KEYUP) && (e.key.keysym.sym == SDLK_ESCAPE) )
		)	quit();
	}
}

static void quit() {
	/* Destroy window */
    SDL_DestroyWindow(window);
    /* Quit SDL */
    SDL_Quit();
	/* Exit */
	_Exit(0);
}