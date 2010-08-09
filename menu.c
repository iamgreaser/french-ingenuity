// Menu crap

#include "common.h"

// function pointer for menu logic
void menu_fptr_logic(void)
{
	if(sys_key_once(KEY_ESC))
		fptr_logic = NULL;
	
	if(sys_key_once(KEY_ENTER))
	{
		fptr_logic = game_fptr_init;
		fptr_video = NULL;
		sys_declock();
	}
}

// function pointer for menu graphics
void menu_fptr_video(void)
{
	sys_gfx_clear();
	
	textout_ex(buf, font, "Menu stuff goes here", 0,0, makecol(0,255,255), -1);
	sys_gfx_flip();
}

// function pointer for menu init
void menu_fptr_init(void)
{
	fptr_logic = menu_fptr_logic;
	fptr_video = menu_fptr_video;
}


