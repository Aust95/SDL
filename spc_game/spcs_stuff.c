#include <SDL2/SDL.h>
#include "spcs_stuff.h"
#include "render.h"

extern uint8_t user_input;

extern SDL_Rect rec_size;
extern SDL_Rect spc_s;
extern SDL_Rect blt_rec_s;
extern SDL_Rect blt_s;

void update_ship(SDL_Rect* const rect)
{
	if (user_input&BUTTON_LEFT){
		rect->x -= 5;
	}
	else if (user_input&BUTTON_RIGHT){
		rect->x += 5;		
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

Projectile *shot[MAX_BLTS] = {NULL};

void c_projectile(int x, int y, int dy)
{
	int ctr = -1;

	for (int i = 0; i < MAX_BLTS; i++) {
		if (shot[i] == NULL) {
			ctr = i;
			break;
		}
	}

	if (ctr >= 0) {
		int i = ctr;

		shot[i] = malloc(sizeof(Projectile));
		shot[i]->x = x;
		shot[i]->y = y;
		shot[i]->dy = dy;
	}
}

void d_projectile(int i)
{
	if(shot[i]) {
		free(shot[i]);
		shot[i] = NULL;
	}
}

void shoot(SDL_Rect *spc_s, SDL_Rect *blt_s)
{
	if (user_input&LEFT_CLICK) {
		c_projectile(spc_s->x, blt_s->y, 1);
	}

	for (int i = 0; i < MAX_BLTS; i++) {
		if (shot[i]){
			printf("count %d\n", i);
			shot[i]->y -= shot[i]->dy;

			if (shot[i]->dy < 0){
				printf("deleting...%d\n", i);
				d_projectile(i);
			}
		}
	}
}
