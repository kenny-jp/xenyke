#version 400 core

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
