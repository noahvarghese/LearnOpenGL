#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "triangle.h"
#include "rectangle.h"

int main(int argc, char **argv)
{
    int i = 0;

    int (*render_loop)(void) = NULL;

    while (argv[i] != NULL)
    {
        if (!strcmp(argv[i], "triangle"))
        {
            render_loop = triangle_lesson;
        }
        else if (!strcmp(argv[i], "rectangle"))
        {
            render_loop = rectangle_lesson;
        }

        if (render_loop != NULL)
        {
            break;
        }

        i++;
    }

    if (render_loop != NULL)
    {
        int res = render_loop();
        return res;
    }

    fprintf(stderr, "[ ERROR ]: No render loop assigned\n");
    fprintf(stderr, "[ HELP ]: Options are:\n\ttriangle\n\trectangle\n");
    return 1;
}