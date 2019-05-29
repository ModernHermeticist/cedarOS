#ifndef IO_H
#define IO_H

/* The I/O port */
#define FB_COMMAND_PORT                 0x3D4
#define FB_DATA_PORT                    0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND            14
#define FB_LOW_BYTE_COMMAND             15

/* The frame buffer pointer */
char* fb;

/* frame buffer width is 80 characters */
#define FB_WIDTH                        80
/* frame buffer height is 25 characters */
#define FB_HEIGHT                       25

/* The size of a cell... ish... */
short cellSize;

/* Color definitions */
#define FB_GREEN     2
#define FB_DARK_GREY 8


/** outb:
 *  Sends the given data to the given I/O port. Defined in io.s
 *
 *  @param port The I/O port to send the data to
 *  @param data The data to send to the I/O port
 */
extern void outb(unsigned short port, unsigned char data);

void fb_move_cursor(unsigned short pos);
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void write_cell(char c, unsigned char fg, unsigned char bg);
void fb_new_line();
void fb_print(char c[], int offset);
void fb_clear();
void writeln();
void write();

#endif /* IO_H */
