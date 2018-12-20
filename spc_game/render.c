#include <stdio.h>
#include <SDL2/SDL.h>
#include "spcs_stuff.h"
#include "render.h"

extern Projectile *shot[MAX_BLTS];

void render_stuff(SDL_Renderer *rend,
					SDL_Texture *tex,
					SDL_Texture *texspc,
					SDL_Rect *rec_size,
					SDL_Rect *spc_s,
					SDL_Texture *blt_tex,
					SDL_Rect *blt_rec_s,
					SDL_Rect *blt_s)
{
	SDL_RenderClear(rend);
	SDL_RenderCopy(rend, tex, NULL, NULL);

	for(int i = 0; i < MAX_BLTS; i++) if (shot[i]) {
		printf("count %d\n", i);
		blt_rec_s->x = 0;
		blt_rec_s->y = 0;
		blt_rec_s->w = BLT_SW;
		blt_rec_s->h = BLT_SH;

		blt_s->x = shot[i]->x + (SPC_SW - BLT_SW)/2;
		blt_s->y = spc_s->y - BLT_SH;
		blt_s->w = BLT_SW;
		blt_s->h = BLT_SH;

		SDL_RenderCopy(rend, blt_tex, NULL, blt_s);
	}

	SDL_RenderCopy(rend, texspc, rec_size, spc_s);
	SDL_RenderPresent(rend);
}