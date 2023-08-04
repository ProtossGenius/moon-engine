#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main(){
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord;
}

#shader fregment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;
uniform float c_Transparency;

in vec2 v_TexCoord;

void main(){
    vec4 texColor = texture(u_Texture, v_TexCoord);
    if (texColor.a > c_Transparency)
        texColor.a = c_Transparency;
    color = texColor;
}