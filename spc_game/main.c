#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "spcs_stuff.h"
#include "render.h"

//Pointers
SDL_Window *win;
SDL_Renderer *rend;
SDL_Surface *img;
SDL_Surface *spc;
SDL_Surface *blt;
SDL_Texture *tex;
SDL_Texture *blt_tex;
SDL_Texture *texspc;

uint8_t user_input = 0;

static int events(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
			switch (event.key.keysym.scancode) {
				default: break;
				case SDL_SCANCODE_ESCAPE:
					return 1;
					break;
				case SDL_SCANCODE_A:
					if (event.type == SDL_KEYDOWN)
						user_input |= BUTTON_LEFT;
					else
						user_input &= ~BUTTON_LEFT;
					break;
				case SDL_SCANCODE_D:
					if (event.type == SDL_KEYDOWN)
						user_input |= BUTTON_RIGHT;
					else
						user_input &= ~BUTTON_RIGHT;
					break;
			}
		}

		if (event.type == SDL_MOUSEBUTTONDOWN){
			switch (event.type) {
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					user_input |= LEFT_CLICK;
					break;
			}
		}
	}

	return 0;
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

	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

	rend = SDL_CreateRenderer(win, -1, render_flags);
	if (rend == NULL) {
		printf("Could not create a renderer context");

		return false;
	}

	img = IMG_Load("images/city.png");
	if (img == NULL) {
		printf("Could not create sfc");

		return false;
	}

	blt = IMG_Load("images/shoot.png");
	if (blt == NULL) {
		printf("Could not create sfc2");
	}

	spc = IMG_Load("images/spcs.png");
	if (spc == NULL) {
		printf("Could not create sfc3");

		return false;
	}

	tex = SDL_CreateTextureFromSurface(rend, img);
	if (tex == NULL) {
		printf("Could not create tex");

		return false;
	}

	blt_tex = SDL_CreateTextureFromSurface(rend, blt);
	if (blt_tex == NULL) {
		printf("Could not create tex2");
	}

	texspc = SDL_CreateTextureFromSurface(rend, spc);
	if (texspc == NULL) {
		printf("Could not create tex3");

		return false;
	}

	return true;
}

static void platform_end()
{	
	if (blt != NULL)
		SDL_FreeSurface(blt);
	if (spc != NULL)
		SDL_FreeSurface(spc);
	if (img != NULL)
		SDL_FreeSurface(img);
	if (tex != NULL)
		SDL_DestroyTexture(tex);
	if (blt_tex != NULL)
		SDL_DestroyTexture(blt_tex);
	if (texspc != NULL)
		SDL_DestroyTexture(texspc);
	if (rend != NULL)
		SDL_DestroyRenderer(rend);
	if (win != NULL)
		SDL_DestroyWindow(win);
	int i;

	for (i = 0; i < MAX_BLTS; i++)
		d_projectile(i);

	IMG_Quit();
	SDL_Quit();
}

int main()
{
	atexit(platform_end);
	platform_init();

	SDL_Rect rec_size;
	SDL_Rect spc_s;

	SDL_Rect blt_rec_s;
	SDL_Rect blt_s;

	spcs_param(&rec_size, &spc_s);

	while (events() == 0) {
		update_ship(&spc_s);
		lr_spcs_coll(&spc_s);
		render_stuff(rend, tex, texspc, &rec_size, &spc_s,blt_tex, &blt_rec_s, &blt_s);
		shoot(&spc_s, &blt_s);

	}

	return 0;
}
