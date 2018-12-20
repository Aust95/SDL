#include <SDL2/SDL.h>

#define WIN_WIDTH (700)
#define WIN_HEIGHT (500)

extern void render_stuff(SDL_Renderer *rend,
							SDL_Texture *tex,
							SDL_Texture *texspc,
							SDL_Rect *rec_size,
							SDL_Rect *spc_s,
							SDL_Texture *blt_tex,
							SDL_Rect *blt_rec_s,
							SDL_Rect *blt_s);
