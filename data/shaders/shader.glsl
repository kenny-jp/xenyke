#version 400 core //vertex

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 texCoord;

uniform mat4 mvp; // projection * view

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0);
    ourColor = aColor;
    texCoord = aTexCoord;
}

#version 400 core //fragment

out vec4 FragColor;

in vec4 ourColor;
in vec2 texCoord;

uniform bool hasTexture;
uniform sampler2D ourTexture;

void main()
{
    if (hasTexture) 
    {
        FragColor = texture(ourTexture, texCoord);
    } 
    else 
    {
        FragColor = ourColor;
    }
}
