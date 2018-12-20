#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIN_WIDTH  (700)
#define WIN_HEIGHT (500)

#define MAX_SHOOTS (1)

enum {
	BUTTON_LEFT  = 0x01,
	BUTTON_RIGHT = 0x02,
	BUTTON_SHOOT = 0x04
};

static SDL_Window *win;
static SDL_Renderer *rend;
static SDL_Texture *bg_tex;
static SDL_Texture *ship_tex;
static SDL_Texture *shoot_tex;
static uint8_t input = 0;


static SDL_Rect ship = {
	.x = (WIN_WIDTH / 2) - 16,
	.y = WIN_HEIGHT - 63,
	.w = 32,
	.h = 63
};

static SDL_Rect shoots[MAX_SHOOTS];
static int shoots_cnt = 0;


static bool events(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
			switch (event.key.keysym.scancode) {
				
				default: break;
				
				case SDL_SCANCODE_ESCAPE: return true;

				case SDL_SCANCODE_A:
					if (event.type == SDL_KEYDOWN)
						input |= BUTTON_LEFT;
					else
						input &= ~BUTTON_LEFT;
					break;
				case SDL_SCANCODE_D:
					if (event.type == SDL_KEYDOWN)
						input |= BUTTON_RIGHT;
					else
						input &= ~BUTTON_RIGHT;
					break;
			}
		}

		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			input |= BUTTON_SHOOT;
		} else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
			input &= ~BUTTON_SHOOT;
		}
	}

	return false;
}

static bool platform_init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL");
		return false;
	}

	//Creates a window
	Uint32 win_flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP;

	win = SDL_CreateWindow("My Window",
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							WIN_WIDTH, WIN_HEIGHT, win_flags);
	if (win == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window");
		return false;
	}

	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

	rend = SDL_CreateRenderer(win, -1, render_flags);
	if (rend == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create a renderer context");

		return false;
	}

	bg_tex = IMG_LoadTexture(rend, "images/city.png");
	if (bg_tex == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create bg_tex");
		return false;
	}

	ship_tex = IMG_LoadTexture(rend, "images/spcs.png");
	if (ship_tex == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create ship_tex");
		return false;
	}

	shoot_tex = IMG_LoadTexture(rend, "images/shoot.png");
	if (shoot_tex == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create shoot_tex");
	}

	SDL_SetTextureBlendMode(ship_tex, SDL_BLENDMODE_BLEND);

	return true;
}

static void platform_end()
{	
	if (shoot_tex != NULL)
		SDL_DestroyTexture(shoot_tex);
	if (ship_tex != NULL)
		SDL_DestroyTexture(ship_tex);
	if (bg_tex != NULL)
		SDL_DestroyTexture(bg_tex); 
	if (rend != NULL)
		SDL_DestroyRenderer(rend);
	if (win != NULL)
		SDL_DestroyWindow(win);

	IMG_Quit();
	SDL_Quit();
}



static void update_ship(void)
{

	if (input&BUTTON_SHOOT && shoots_cnt < MAX_SHOOTS) {
		shoots[shoots_cnt] = (SDL_Rect) {
			.x = ship.x + 16,
			.y = ship.y + 16,
			.w = 8,
			.h = 16
		};
		++shoots_cnt;
	}

	if (input&BUTTON_LEFT) {
		ship.x -= 1;
	} else if (input&BUTTON_RIGHT) {
		ship.x += 1;
	}
}


static void update_shoots(void)
{
	int i;
	for (i = 0; i < shoots_cnt; ++i) {
		shoots[i].y -= 5;
		if (shoots[i].y <= -16)
			shoots_cnt -= 1;
	}
}


int main()
{
	int i;

	atexit(platform_end);
	platform_init();


	while (events() == 0) {
		update_ship();
		update_shoots();

		SDL_RenderCopy(rend, bg_tex, NULL, NULL);
		SDL_RenderCopy(rend, ship_tex, NULL, &ship);
		for (i = 0; i < shoots_cnt; ++i)
			SDL_RenderCopy(rend, shoot_tex, NULL, &shoots[i]);

		SDL_RenderPresent(rend);
	}

	return 0;
}
