#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "triangle.h"
#include "rectangle.h"
#include "two_triangles_1.h"

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
        else if (!strcmp(argv[i], "two_triangles_1"))
        {
            render_loop = two_triangles_1_lesson;
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
    fprintf(stderr, "[ HELP ]: Options are:\n\ttriangle\n\trectangle\n\ttwo_triangles_1\n");
    return 1;
}