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

// might need this for whatever reason -GM
#ifdef WIN32
#else
#endif /* WIN32 */

#define PACKED_PRE
#define PACKED_SUF __attribute__((__packed__))

// defines / enums

// creep types
enum
{
	CREEP_NONE,
	CREEP_G1, CREEP_W1, CREEP_B1, CREEP_R1,
	CREEP_G2, CREEP_W2, CREEP_B2, CREEP_R2,
	CREEP_G3, CREEP_W3, CREEP_B3, CREEP_R3,
	CREEP_G4, CREEP_W4, CREEP_B4, CREEP_R4,
};

// tower types
enum // also used for bullets
{
	TOWER_NONE,
	TOWER_NORMAL,
	TOWER_SLOW,
	TOWER_SPLASH,
	TOWER_ROCKET,
	TOWER_SPEED,
	TOWER_ULTIMATE,
};

// network messages
enum
{
	NM_NOP,
	
	// server -> client
	NM_CNEW,
	NM_CIGN,
	NM_CSET,
	NM_CDEL,
	NM_TNEW,
	NM_TIGN,
	NM_TSET,
	NM_TALT,
	NM_TDEL,
	NM_BNEW,
	NM_BSET,
	NM_BHIT, // implies delete
	NM_BDEL,
	NM_PSET,
	NM_CLIST,
	NM_TLIST,
	NM_BLIST,
	
	// client -> server
	NM_SCHECK,
	NM_CREQ,
	NM_TREQ,
	NM_CREAD,
	NM_TREAD,
};

// tower states
enum
{
	TS_IDLE,
	TS_UPGR,
	TS_SELL,
	TS_STRAT_LOCK,
	TS_STRAT_UNLOCK,
	TS_STRAT_HARD,
	TS_STRAT_WEAK,
	TS_STRAT_CLOSE,
	TS_STRAT_FURTHEST,
	TS_STRAT_FASTEST,
};

// structs

// x,y are signed for rotation purposes in these structs
// bottom-left corner plays these coordinates straight

// fi_node: node on a map
PACKED_PRE struct fi_node_intern
{
	uint32_t id;
	int16_t x,y;
	uint16_t len;
} PACKED_SUF;

struct fi_node
{
	struct fi_node_intern d;
	struct fi_node *p, *n;
};

// fi_creep: general creep information
PACKED_PRE struct fi_creep_intern
{
	uint32_t id;
	uint32_t health;
	uint32_t max_health;
	int16_t x,y;
	uint16_t node_pos;
	uint8_t node_start;
	uint8_t node_end;
	uint8_t type;
	uint8_t board;
} PACKED_SUF;

struct fi_creep
{
	struct fi_creep_intern d;
	struct fi_creep *p,*n;
};

// fi_tower: general tower information
PACKED_PRE struct fi_tower_intern
{
	uint32_t id;
	uint32_t state_timedone;
	int8_t x,y;
	uint8_t type;
	uint8_t level;
	uint8_t mode;
	uint8_t state;
	uint8_t board;
} PACKED_SUF;

struct fi_tower
{
	struct fi_tower_intern d;
};

// fi_bullet: general bullet information
PACKED_PRE struct fi_bullet_intern
{
	uint32_t id;
	uint32_t state_timedone;
	int8_t x,y;
	uint8_t type;
	uint8_t level;
	uint8_t mode;
	uint8_t state;
} PACKED_SUF;

struct fi_bullet
{
	struct fi_bullet_intern d;
};

// fi_player: general player information
PACKED_PRE struct fi_player_intern
{
	uint32_t credit;
	uint32_t income;
	uint8_t lives;
	uint8_t id;
} PACKED_SUF;

struct fi_player
{
	struct fi_player_intern d;
	char *name;
};

// fi_state: state for resync
PACKED_PRE struct fi_state_intern
{
	uint32_t statetime;
	uint32_t checksum; // calculated when requested
} PACKED_SUF;

struct fi_state
{
	struct fi_state_intern d;
};

// network messages: server -> client
PACKED_PRE struct fi_nm_header
{
	uint8_t sync; // 0xF1
	uint8_t type;
	uint16_t len;
	uint32_t time;
} PACKED_SUF;

PACKED_PRE struct fi_nm_cnew
{
	uint32_t cid;
	uint32_t id;
	uint32_t max_health; // always set health to full
	uint8_t type;
	uint8_t board;
} PACKED_SUF;

PACKED_PRE struct fi_nm_cign
{
	uint32_t cid;
} PACKED_SUF;

PACKED_PRE struct fi_nm_cset
{
	struct fi_creep_intern d;
} PACKED_SUF;

PACKED_PRE struct fi_nm_cdel
{
	uint32_t id;
} PACKED_SUF;

PACKED_PRE struct fi_nm_tnew
{
	uint32_t cid;
	uint32_t id;
	int8_t x,y;
	uint8_t type;
	uint8_t board;
} PACKED_SUF;

PACKED_PRE struct fi_nm_tign
{
	uint32_t cid;
} PACKED_SUF;

PACKED_PRE struct fi_nm_tset
{
	struct fi_tower_intern d;
} PACKED_SUF;

PACKED_PRE struct fi_nm_talt
{
	uint32_t id;
	uint32_t state_timedone;
	uint8_t state;
} PACKED_SUF;

PACKED_PRE struct fi_nm_tdel
{
	uint32_t id;
} PACKED_SUF;

PACKED_PRE struct fi_nm_bnew
{
	uint32_t id;
	uint32_t src; // tower
	uint32_t dest; // creep
} PACKED_SUF;

PACKED_PRE struct fi_nm_bset
{
	struct fi_bullet_intern d;
} PACKED_SUF;

PACKED_PRE struct fi_nm_bhit // implies delete
{
	uint32_t id;
} PACKED_SUF;

PACKED_PRE struct fi_nm_bdel
{
	uint32_t id;
} PACKED_SUF;

PACKED_PRE struct fi_nm_pset
{
	struct fi_player_intern d;
} PACKED_SUF;

PACKED_PRE struct fi_nm_clist
{
	uint32_t len;
	uint32_t ids[];
} PACKED_SUF;

PACKED_PRE struct fi_nm_tlist
{
	uint32_t len;
	uint32_t ids[];
} PACKED_SUF;

PACKED_PRE struct fi_nm_blist
{
	uint32_t len;
	uint32_t ids[];
} PACKED_SUF;

// network messages: client -> server

PACKED_PRE struct fi_nm_scheck
{
	struct fi_state_intern d;
} PACKED_SUF;

PACKED_PRE struct fi_nm_creq
{
	uint32_t cid;
	uint8_t type;
} PACKED_SUF;

PACKED_PRE struct fi_nm_treq
{
	uint32_t cid;
	int8_t x,y;
	uint8_t type;
} PACKED_SUF;

PACKED_PRE struct fi_nm_cread
{
	uint32_t id;
} PACKED_SUF;

PACKED_PRE struct fi_nm_tread
{
	uint32_t id;
} PACKED_SUF;

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
