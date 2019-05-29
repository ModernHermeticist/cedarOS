#ifndef GDT_H
#define GDT_H

struct gdt
{
	unsigned int address;
	unsigned short size;
} __attribute__((packed));

#endif
