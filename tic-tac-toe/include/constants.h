typedef enum sdstate{
    EMPTY, EX, OH
} sdstate; // The seed state

typedef enum gstate {
    PLAYING, DRAW, XWON, OWON
} gstate; // The game state

int  winningPatterns[] = {
    0x1c0,   // 0b111 000 000 (row 2)
    0x038,   // 0b000 111 000 (row 1)
    0x007,   // 0b000 000 111 (row 0)
    0x124,   // 0b100 100 100 (col 2)
    0x092,   // 0b010 010 010 (col 1)
    0x049,   // 0b001 001 001 (col 0)
    0x111,   // 0b100 010 001 (diagonal)
    0x054    // 0b001 010 100 (opposite diagonal)
};// msb is (2, 2); lsb is (0, 0)

#define ROWS 3
#define COLS 3
