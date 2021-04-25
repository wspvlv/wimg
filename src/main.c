/* Wimg main function */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <wc/io.h>
#include <wc/types/char.h>
#include <wc/types/array.h>

#define WIN_WIDTH	640
#define WIN_HEIGHT	480

#define FILE_BMP	1
#define FILE_PNG	2
#define FILE_JPG	3

static SDL_Window*		window		= NULL;	/* Window pointer */
static SDL_Renderer*	renderer	= NULL;	/* Renderer pointer */
static SDL_Texture* 	image		= NULL;	/* Image pointer */
static SDL_Rect			rect; 

static void			init	();
static void			update	();
static void			quit	();
static const char*	fileExt	(const char *filename);

static const char* fileExt(const char *filename) {
    const char *dot = filename + cs(filename, '.', CS_REVERSE);
    if (!dot || dot == filename) return "";
    return dot + 1;
}

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

	/* Create Renderer */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	/* Initialize SDL_image */
	const char* ext[3] = { "bmp", "png", "jpg" };
	switch (hs(fileExt(file), ext, 2)) {
		case FILE_BMP:	break;
		case FILE_PNG:	IMG_Init(IMG_INIT_PNG);		break;
		case FILE_JPG:	IMG_Init(IMG_INIT_JPG);		break;
		default:		
			outl("Unknown image type");
		break;
	}
	
	/* Load Image */
	if ((image = IMG_LoadTexture(renderer, file)));
	else outl(SDL_GetError());

	/* Get width and height */
	int w, h, dfilled;
	float ratio;
	SDL_QueryTexture(image, NULL, NULL, &w, &h);
	if (w > h) {
		ratio = (float)w/(float)h;
		dfilled = WIN_WIDTH / ratio;
		rect.x = 0;
		rect.y = (WIN_HEIGHT-dfilled) / 2;
		rect.w = WIN_WIDTH;
		rect.h = dfilled;
	}
	else {
		ratio = (float)h/(float)w;
		dfilled = WIN_HEIGHT / ratio;
		rect.x = (WIN_WIDTH-dfilled) / 2;
		rect.y = 0; 
		rect.w = dfilled;
		rect.h = WIN_HEIGHT;
	}

	outl("Image rendered!");
}

static void update() {
	/* Event handler */
    SDL_Event e;
	
	while (SDL_PollEvent(&e) != 0) {
		if (
			(e.type == SDL_QUIT) || 
			( (e.type == SDL_KEYUP) && (e.key.keysym.sym == SDLK_ESCAPE) )
		)	quit();
	}

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, image, NULL, &rect);
	SDL_RenderPresent(renderer);
}

static void quit() {
	/* Destroy image */
	SDL_DestroyTexture(image);
	/* Destroy window */
    SDL_DestroyWindow(window);
	/* Destroy Renderer */
    SDL_DestroyRenderer(renderer);
	/* Quit SDL_image */
    IMG_Quit();
    /* Quit SDL */
    SDL_Quit();
	/* Exit */
	_Exit(0);
}