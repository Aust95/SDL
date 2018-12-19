#include <stdio.h>
#include <SDL2/SDL.h>

void render_stuff(SDL_Renderer *rend,
					SDL_Texture *tex,
					SDL_Texture *texspc,
					SDL_Rect *rec_size,
					SDL_Rect *spc_s)
{
	SDL_RenderClear(rend);//Limpa a tela
	SDL_RenderCopy(rend, tex, NULL, NULL);//Copia a textura para o contexto de renderizacao
	//SDL_RenderCopy(rend, blt_tex, &blt_rec_s, &blt_s);
	SDL_RenderCopy(rend, texspc, rec_size, spc_s);
	SDL_RenderPresent(rend);
}