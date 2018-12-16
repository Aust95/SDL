#include <SDL2/SDL.h>

#define SPC_SW 32
#define SPC_SH 64
#define BLT_SW 8
#define BLT_SH 16

extern void update_ship(SDL_Rect* const rect);
extern void spcs_param(SDL_Rect *const rec_size, SDL_Rect *const spc_s);
extern void proj1_param(SDL_Rect *const blt_rec_s, SDL_Rect *const blt_s, SDL_Rect *const spc_s);
extern void lr_spcs_coll(SDL_Rect *const spc_mx);
