// Actual game stuff

#include "common.h"

// function pointer for game logic
void game_fptr_logic(void)
{
	if(sys_key_once(KEY_ESC))
	{
		fptr_logic = menu_fptr_init;
		fptr_video = NULL;
		sys_declock();
	}
}

// function pointer for game graphics
void game_fptr_video(void)
{
	sys_gfx_clear();
	textout_ex(buf, font, "Game stuff goes here", 0,0, makecol(255,255,0), -1);
	sys_gfx_flip();
}

// function pointer for game init
void game_fptr_init(void)
{
	fptr_logic = game_fptr_logic;
	fptr_video = game_fptr_video;
}
