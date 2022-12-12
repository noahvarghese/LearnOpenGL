#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "1.getting_started/2.1.hello_triangle/hello_triangle.h"
#include "1.getting_started/2.2.hello_triangle_indexed/hello_triangle_indexed.h"
#include "1.getting_started/2.3.hello_triangle_exercise1/hello_triangle_exercise1.h"
#include "1.getting_started/2.4.hello_triangle_exercise2/hello_triangle_exercise2.h"
#include "1.getting_started/2.5.hello_triangle_exercise3/hello_triangle_exercise3.h"
#include "1.getting_started/3.1.shaders_uniform/shaders_uniform.h"
#include "1.getting_started/3.2.shaders_interpolation/shaders_interpolation.h"
#include "1.getting_started/3.4.shaders_exercise1/shaders_exercise1.h"
#include "1.getting_started/3.5.shaders_exercise2/shaders_exercise2.h"
#include "1.getting_started/3.6.shaders_exercise3/shaders_exercise3.h"
#include "1.getting_started/4.6.textures_exercise4/textures_exercise4.h"
#include "1.getting_started/5.2.transformations_exercise2/transformations_exercise2.h"
#include "1.getting_started/6.1.coordinate_systems/coordinate_systems.h"
#include "1.getting_started/6.2.coordinate_systems_depth/coordinate_systems_depth.h"


int main(int argc, char **argv)
{
    int i = 0;

    int (*render_loop)(void) = NULL;

    while (argv[i] != NULL)
    {
        if (!strcmp(argv[i], "--example"))
        {
            if (argv[++i] == NULL)
            {
                break;
            }

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
            else if (!strcmp(argv[i], "two_triangles_2"))
            {
                render_loop = two_triangles_2_lesson;
            }
            else if (!strcmp(argv[i], "two_triangles_3"))
            {
                render_loop = two_triangles_3_lesson;
            }
            else if (!strcmp(argv[i], "uniform"))
            {
                render_loop = uniforms_lesson;
            }
            else if (!strcmp(argv[i], "attributes"))
            {
                render_loop = more_attributes_lesson;
            }
            else if (!strcmp(argv[i], "invert"))
            {
                render_loop = invert_triangle_lesson;
            }
            else if (!strcmp(argv[i], "horizontal"))
            {
                render_loop = horizontal_offset_lesson;
            }
            else if (!strcmp(argv[i], "vertex_as_color"))
            {
                render_loop = vert_color_lesson;
            }
            else if (!strcmp(argv[i], "smiling_box"))
            {
                render_loop = smiling_box_lesson;
            }
            else if (!strcmp(argv[i], "transformation"))
            {
                render_loop = transformation_lesson;
            }
            else if (!strcmp(argv[i], "2d_coordinates"))
            {
                render_loop = coordinate_lesson_2d;
            }
            else if (!strcmp(argv[i], "3d_coordinates"))
            {
                render_loop = coordinate_lesson_3d;
            }

            if (render_loop != NULL)
            {
                break;
            }
        }

        i++;
    }

    if (render_loop != NULL)
    {
        int res = render_loop();
        return res;
    }

    const char *help = "\n[ HELP ]\n"
                       "--example\tone of the following:\n"
                       "\t\ttriangle\n"
                       "\t\trectangle\n"
                       "\t\ttwo_triangles_1\n"
                       "\t\ttwo_triangles_2\n"
                       "\t\ttwo_triangles_3\n"
                       "\t\tuniform\n"
                       "\t\tattributes\n"
                       "\t\tinvert\n"
                       "\t\thorizontal\n"
                       "\t\tvertex_as_color\n"
                       "\t\tsmiling_box\n"
                       "\t\ttransformation\n"
                       "\t\t2d_coordinates\n"
                       "\t\t3d_coordinates\n";

    fprintf(stderr, "%s", "[ ERROR ]: No render loop assigned\n");
    fprintf(stderr, "%s", help);
    return 1;
}
