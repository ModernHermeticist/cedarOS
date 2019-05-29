#include "main.h"

/* The frame buffer pointer */
char* fb = (char*) 0x000B8000;

/* The current row of the frame buffer pointer */
int fb_row = 0;

/* The current column of the frame buffer pointer */
int fb_column = 0;

/* The size of a cell... ish... */
short cellSize = 2;

/*  */

/** fb_move_cursor:
 * Moves the cursor of the framebuffer to the given position
 *
 * @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,   ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT,  FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,            pos & 0x00FF);
}

/** fb_write_cell:
 * Writes a character with the given foreground and background to position i
 * in the framebuffer.
 * 
 * @param i The location in the framebuffer
 * @param c The character
 * @param fg The foreground color
 * @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    fb[i] = c;
    fb[i+1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void write_cell(char c, unsigned char fg, unsigned char bg)
{
    *fb = c;
    fb += 1;
    *fb = ((fg & 0x0F) << 4) | (bg & 0x0F);
    fb += 1;
    fb_column += 1;
    if (fb_column >= 80)
    {
        fb_column = 0;
        fb_row += 1;
    }
}
/** fb_new_line:
 * Moves the frame buffer cursor to the next line
 */
void fb_new_line()
{
    while (fb_column < 80)
    {
        fb += 2;
        fb_column += 1;
    }
    fb_column = 0;
    fb_row += 1;
}

/** fb_print:
 * Prints a string to the string at a given offset
 * 
 * @param c      The character string
 * @param offset The offset, if any
 * 
 */
void fb_print(char* c, int offset)
{
    int l = 0;
    while (c[l] != '\n')
    {
        fb_write_cell(l * cellSize + offset, c[l], 0x0, 0xFF);
        l += 1;
    }
}

/** fb_clear:
 * Clears the entire frame buffer
 */
void fb_clear()
{
    for (int i = 0; i < 2000; i++)
    {
        fb_write_cell(i * cellSize, ' ', 0, 0);
    }
}
/** writeln:
 * Writes a character string to the screen. Automatically adjusts the cursor
 * and scrolls the screen if needed. Adjusts for new line and sets cursor at
 * column 0, row += 1
 * 
 * @param buf   The string being written
 */
void writeln(char *buf)
{
    while (*buf != '\n')
    {
        write_cell(*buf, 0x00, 0xFF);
        buf += 1;
    }
    fb_new_line();
}
/** write:
 * Writes a character string to the screen. Automatically adjusts the cursor
 * and scrolls the screen if needed.
 * 
 * @param buf   The string being written
 */
void write(char *buf)
{
    while (*buf != '\n')
    {
        write_cell(*buf, 0x00, 0xFF);
        buf += 1;
    }
}
