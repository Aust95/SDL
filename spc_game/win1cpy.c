#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define WIN_WIDTH (700)
#define WIN_HEIGHT (500)
#define SPC_SW 32
#define SPC_SH 64

//Pointers
SDL_Window *win;
SDL_Renderer *rend;
SDL_Surface *img;
SDL_Surface *spc;
SDL_Texture *tex;
SDL_Texture *texspc;

static int events(SDL_Rect *spc_mx)
{
	SDL_Event event;
	int done = 0;

	while (SDL_PollEvent(&event)) {//Event loop
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					done = 1;
				case SDLK_d:
					spc_mx->x += 10;
				break;
				case SDLK_a:
					spc_mx->x -= 10;
			}
		}
	}
	return done;
}

static bool platform_init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0) {
		printf("Error initializing SDL");

		return false;
	}

	//Creates a window
	Uint32 win_flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP;

	win = SDL_CreateWindow("My Window",
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							WIN_WIDTH, WIN_HEIGHT, win_flags);
	if (win == NULL) {
		printf("Could not create window");

		return false;
	}

	//Creates a renderer context	
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

	rend = SDL_CreateRenderer(win, -1, render_flags);
	if (rend == NULL) {
		printf("Could not create a renderer context");

		return false;
	}

	img = IMG_Load("city.png");
	if (img == NULL) {
		printf("Could not create surface");

		return false;
	}

	spc = IMG_Load("spcs.png");
	if (spc == NULL) {
		printf("Could not create surface 2");

		return false;
	}

	tex = SDL_CreateTextureFromSurface(rend, img);
	if (tex == NULL) {
		printf("Could not create texture");

		return false;
	}

	texspc = SDL_CreateTextureFromSurface(rend, spc);
	if (texspc == NULL) {
		printf("Could not create texture 2");

		return false;
	}
}



static void platform_end()
{
	if (spc != NULL)
	SDL_FreeSurface(spc);
	if (img != NULL)
		SDL_FreeSurface(img);
	if (tex != NULL)
		SDL_DestroyTexture(tex);
	if (rend != NULL)
		SDL_DestroyRenderer(rend);
	if (win != NULL)
		SDL_DestroyWindow(win);

	IMG_Quit();
	SDL_Quit();
}

int main()
{
	atexit(platform_end);
	platform_init();

	int done = 0;
	SDL_Rect rec_size;
	SDL_Rect spc_s;

	rec_size.x = 0;
	rec_size.y = 0;
	rec_size.w = SPC_SW;
	rec_size.h = SPC_SH;

	spc_s.x = WIN_WIDTH/2 - SPC_SW/2;
	spc_s.y = WIN_HEIGHT - SPC_SH;
	spc_s.w = SPC_SW;
	spc_s.h = SPC_SH;

	while (done == 0) {

		done = events(&spc_s);

		SDL_RenderClear(rend);//Limpa a tela
		SDL_RenderCopy(rend, tex, NULL, NULL);//Copia a textura para o contexto de renderizacao
		SDL_RenderCopy(rend, texspc, &rec_size, &spc_s);
		SDL_RenderPresent(rend);
	}

	return 0;
}
