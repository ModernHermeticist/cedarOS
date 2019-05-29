#include "main.h"

int main()
{
    char* msg = "A new message!\n";

    fb_clear(); // clears the frame buffer

    DrawOsSplash();

    writeln(msg);

    msg = "This is a new line!\n";

    writeln(msg);

    fb_new_line();
    fb_new_line();

    msg = "This\n";

    write(msg);

    msg = " is on the same line\n";

    write(msg);

    while(1 < 2)
    {

    }

    return 0;
}

void DrawOsSplash()
{
    for (int i = 0; i < 80; i++)
    {
        write("#\n");
    }
    write("#\n");
    fb_new_line();
    fb -= 2;
    write("#\n");
    write("#\n");
    fb_new_line();
    write("#\n");
    write("#\n");
    fb_new_line();
    write("#\n");
    write("#\n");
    fb_new_line();
    for (int i = 0; i < 81; i++)
    {
        write("#\n");
    }
}