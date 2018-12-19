#include <SDL2/SDL.h>

#define SPC_SW 32
#define SPC_SH 64
#define BLT_SW 8
#define BLT_SH 16

#define BUTTON_LEFT  (0x01)
#define BUTTON_RIGHT (0x02)
#define LEFT_CLICK (0x04)

extern void update_ship(SDL_Rect* const rect, SDL_Rect *blt_s);
extern void spcs_param(SDL_Rect *const rec_size, SDL_Rect *const spc_s);
extern void proj1_param(SDL_Rect *const blt_rec_s, SDL_Rect *const blt_s, SDL_Rect *const spc_s);
extern void lr_spcs_coll(SDL_Rect *const spc_mx);
extern void proj1_track(SDL_Rect *blt_s);
