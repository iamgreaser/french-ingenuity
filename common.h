// Common include file everything should use

// TODO: ifndef unistd.h out wrt the Digital Mars C compiler
// unlike MinGW32, dmc spews an error if you have unistd
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include <allegro.h>

#ifdef WIN32
#else
#endif /* WIN32 */

// defines / enums
enum {
	CREEP_NONE,
	CREEP_G1, CREEP_W1, CREEP_B1, CREEP_R1,
	CREEP_G2, CREEP_W2, CREEP_B2, CREEP_R2,
	CREEP_G3, CREEP_W3, CREEP_B3, CREEP_R3,
	CREEP_G4, CREEP_W4, CREEP_B4, CREEP_R4,
};

// structs
struct fi_creep
{
	uint32_t id;
	uint8_t type;
	int16_t x,y; // signed so it can move into a corner
	uint8_t board;
} __attribute__((__packed__));

// main.c
extern void (*fptr_logic)(void);
extern void (*fptr_video)(void);

// network.c
int network_init(void);
void network_exit(void);

// sys_allegro.c
#define GFX_WIDTH 800
#define GFX_HEIGHT 600

extern BITMAP *buf;

int sys_init(void);
void sys_exit(void);
void sys_msleep(int);
void sys_main(void);
void sys_declock(void);
void sys_gfx_flip(void);
void sys_gfx_clear(void);
int sys_key_once(int);

// menu.c
void menu_fptr_init(void);

// game.c
void game_fptr_init(void);
