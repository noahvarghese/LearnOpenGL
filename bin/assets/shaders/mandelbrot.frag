#version 460 core

out vec4 FragColor;

in vec3 TexCoord;

void main()
{
  int iter = 1000;
  vec3 z, c;

  c.x = (TexCoord.x - 0.5) * 1.5 - -0.5;
  c.y = (TexCoord.y - 0.5) * 1.5 - -0.5;
  c.z = (TexCoord.z - 0.5) * 1.5 - -0.5;

  z = vec3(c.x, c.y, 1.0);

  int i;

  for(i = 0; i < iter; i++) {
    float x = (z.x * z.x - z.y * z.y) + c.x;
    float y = (z.y * z.x + z.x * z.y) + c.y;

    if((x * x + y * y) > 1000000.0) break;
    z.x = x;
    z.y = y;
  }

  if (i == iter) {
    FragColor = vec4(0.0, 0.0, 0.0, 0.0);
  } else {
    FragColor = vec4(z.x, z.y, z.x , 1.0);
  }
}