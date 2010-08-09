// Allegro system driver
// This will be the only driver we will use
// It's too tricky to build an API

#include "common.h"

BITMAP *buf = NULL;
int sys_mbcount = 0;
int curcol = 0;
int tick_current = 0;
int tick_logic = 0;

char key_fired[KEY_MAX];

// this is just a timer thread
// it is not part of the API
void sys_allegro_timer_proc()
{
	tick_current++;
}

/* err = int sys_init():
 * Initialise the main system library.
 */
int sys_init(void)
{
	allegro_init();
	
	printf("initialising system...");
	
	// do this early as it appears in the taskbar
	set_window_title("french ingenuity - a #botb production - dear germany, fix your software");
	
	// this should do
	if(install_timer())
	{
		printf("FAIL: timer init\n");
		return 1;
	}
	if(install_keyboard())
	{
		printf("FAIL: keyboard init\n");
		return 1;
	}
	int tmp = install_mouse();
	
	if(tmp == -1)
	{
		printf("FAIL: mouse init\n");
		return 1;
	}
	
	if(tmp > 0)
		sys_mbcount = tmp;
	
	// gfx mode, yay
	// use 32-bit where available
	set_color_depth(32);
	if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, GFX_WIDTH,GFX_HEIGHT, 0,0))
	{
		printf("FAIL: gfx mode\n");
		return 1;
	}
	
	buf = create_bitmap(GFX_WIDTH, GFX_HEIGHT);
	if(buf == NULL)
	{
		printf("FAIL: back buffer\n");
		return 1;
	}
	
	printf("OK!\n");
	/*printf("- system: Allegro\n");
	printf("- mouse buttons: %i\n", sys_mbcount);*/
	
	return 0;
}

/* sys_exit():
 * Shut down the main system library.
 */
void sys_exit(void)
{
	// allegro will deal with itself
}

/* sys_msleep(int msec):
 * Sleep for msec milliseconds.
 */
void sys_msleep(int msec)
{
	rest(msec);
}

/* sys_main():
 * Run logic / video threads (keep it all going smoothly).
 */
void sys_main(void)
{
	sys_msleep(200); // FreeBSD likes it when threads sleep a bit
	install_int_ex(sys_allegro_timer_proc, BPS_TO_TIMER(50));
	
	while(fptr_logic != NULL)
	{
		if(keyboard_needs_poll())
			poll_keyboard();
		if(mouse_needs_poll())
			poll_mouse();
		
		if(tick_current > tick_logic)
		{
			// So we don't overshoot.
			
			if(tick_current - 10 > tick_logic)
				tick_logic = tick_current - 10;
			
			fptr_logic();
			tick_logic++;
			
		} else {
			if(fptr_video != NULL)
				fptr_video();
			
			sys_msleep(5); // Like I said wrt FreeBSD
		}
		
		
	}
}

/* sys_declock():
 * Resets the timer used for fptr_logic.
 */
void sys_declock(void)
{
	tick_logic = tick_current;
}

/* sys_gfx_flip():
 * Flip / blit / whatever for the buffers.
 */
void sys_gfx_flip(void)
{
	blit(buf, screen, 0,0, 0,0, GFX_WIDTH,GFX_HEIGHT);
}

/* sys_gfx_clear():
 * Clear the drawing buffer.
 */
void sys_gfx_clear(void)
{
	clear_bitmap(buf);
}

/* waspressed = int sys_key_once(int key)
 * Check if a key was pressed.
 */
int sys_key_once(int k)
{
	int p = key_fired[k];
	int q = key[k];
	key_fired[k] = q;
	
	return (!p) && q;
}
