#include <SDL2/SDL.h>
#include "spcs_stuff.h"

#define WIN_WIDTH (700)
#define WIN_HEIGHT (500)

extern uint8_t user_input;

extern SDL_Rect rec_size;
extern SDL_Rect spc_s;
extern SDL_Rect blt_rec_s;
extern SDL_Rect blt_s;
extern SDL_Renderer *rend;
extern SDL_Texture *blt_tex;

void update_ship(SDL_Rect* const rect, SDL_Rect *blt_s)
{
	if (user_input&BUTTON_LEFT){
		rect->x -= 5;
		if (blt_s->y > (WIN_HEIGHT - SPC_SH - BLT_SH) - 1)
			blt_s->x -= 5;
	}
	else if (user_input&BUTTON_RIGHT){
		rect->x += 5;
		
		if (blt_s->y > (WIN_HEIGHT - SPC_SH - BLT_SH) - 1)
			blt_s->x += 5;
	}
}

void lr_spcs_coll(SDL_Rect *spc_mx)
{
	if (spc_mx->x < 0)
		spc_mx->x = 0;
	else if (spc_mx->x + SPC_SW > WIN_WIDTH)
		spc_mx->x = WIN_WIDTH - SPC_SW;
}


void spcs_param(SDL_Rect *rec_size, SDL_Rect *spc_s)
{
	rec_size->x = 0;
	rec_size->y = 0;
	rec_size->w = SPC_SW;
	rec_size->h = SPC_SH;

	spc_s->x = WIN_WIDTH/2 - SPC_SW/2;
	spc_s->y = WIN_HEIGHT - SPC_SH;
	spc_s->w = SPC_SW;
	spc_s->h = SPC_SH;
}

void proj1_param(SDL_Rect *blt_rec_s, SDL_Rect *blt_s, SDL_Rect *spc_s)
{
	blt_rec_s->x = 0;
	blt_rec_s->y = 0;
	blt_rec_s->w = BLT_SW;
	blt_rec_s->h = BLT_SH;

	blt_s->x = WIN_WIDTH/2 - BLT_SW/2;
	blt_s->y = spc_s->y - BLT_SH;
	blt_s->w = BLT_SW;
	blt_s->h = BLT_SH;
}

void proj1_track(SDL_Rect *blt_s)
{
	if (user_input&LEFT_CLICK) {

		blt_s->y -= 10;
	}
}
