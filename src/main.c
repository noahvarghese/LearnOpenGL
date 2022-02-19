#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "triangle.h"

int main(int argc, char **argv)
{
    int i = 0;

    int (*render_loop)(void) = NULL;

    while (argv[i] != NULL)
    {
        if (!strcmp(argv[i++], "triangle"))
        {
            render_loop = triangle_lesson;
            break;
        }
    }

    if (render_loop != NULL)
    {
        int res = render_loop();
        return res;
    }

    fprintf(stderr, "[ ERROR ]: No render loop assigned\n");
    return 1;
}