#include "shader.h"
#include "shader.h"

char *read_file(const char *fileName)
{
    error("Not implemented");
}

unsigned int compile_shader(const char *shaderSource, GLenum shaderType)
{
    int success;
    char infoLog[512];
    unsigned int shader;

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    // check for errors
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        const char *message = str_concat("Shader compilation failed\n", infoLog);
        error(message);
    }

    return shader;
}

/*****************************************************************/
/*                         OOP  - BEWARE                         */
/*****************************************************************/

void use(shader *self)
{
    glUseProgram(self->ID);
}

void setUniformBool(shader *self, const bool val)
{
    error("Not implemented");
}

void setUniformInt(shader *self, const bool val)
{
    error("Not implemented");
}

void setUniformFloat(shader *self, const bool val)
{
    error("Not implemented");
}

shader *init_shader(const char *vertexShaderFilePath, const char *fragmentShaderFilePath)
{

    // 1. get data from file paths provided
    const char *vertexShaderData = read_file(vertexShaderFilePath);
    const char *fragmentShaderData = read_file(fragmentShaderFilePath);

    // 2. Compile the shaders
    int vertexShaderID = compile_shader(vertexShaderData, GL_VERTEX_SHADER);
    int fragmentShaderID = compile_shader(fragmentShaderData, GL_FRAGMENT_SHADER);

    // 3. Create the shader program
    unsigned int shaderProgram = glCreateProgram();

    // 4. Attach shaders to program
    glAttachShader(shaderProgram, vertexShaderID);
    glAttachShader(shaderProgram, fragmentShaderID);

    // 5. Link shaders within program
    glLinkProgram(shaderProgram);

    // 6. Check whether process was successful
    int success;
    char infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        const char *message = str_concat("Shader compilation failed\n", infoLog);
        error(message);
    }

    // 7. create struct
    shader *s = (shader *)malloc(sizeof(shader));

    if (s == NULL)
    {
        error("Failed to instantiate shader.");
    }

    // 8. assign function pointers
    s->ID = s;
    s->use = use;
    s->setUniformBool = setUniformBool;
    s->setUniformFloat = setUniformFloat;
    s->setUniformInt = setUniformInt;

    return s;
}