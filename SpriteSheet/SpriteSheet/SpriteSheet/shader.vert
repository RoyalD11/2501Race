// Source code of vertex shader
#version 130

// Vertex buffer
in vec2 vertex;
in vec3 color;
in vec2 uv;

// Uniform (global) buffer
uniform mat4 x;

// Attributes forwarded to the fragment shader
out vec4 color_interp;
out vec2 uv_interp;

uniform int frameindex;
uniform float spriteHeight;
uniform float spriteWidth;
uniform vec2 position;


void main()
{
	vec4 t;
	t = vec4(vertex, 0.0, 1.0);
    gl_Position = x*t;
	
    color_interp = vec4(color, 1.0);

	float tw = 0.5f ; //float(spriteWidth) / texWidth; 
	float th = 0.25f ; //float(spriteHeight) / texHeight;
	int numPerRow = 2; //texWidth / spriteWidth;
	float tx =  float(frameindex % numPerRow) * tw;
	float ty = float(frameindex / numPerRow ) * th;

	// adjust vertex position according to sprite width and height and sprite position
    gl_Position.x = (gl_Position.x * spriteWidth)  / spriteWidth  + position.x;
    gl_Position.y = (gl_Position.y * spriteHeight) / spriteHeight + position.y;

    // (texCoordX  * spriteWidth / textureWidth) + texSourceX
    uv_interp.x = (uv.x *  0.5f) + tx;
    uv_interp.y = (uv.y * 0.25f) + ty ; 
}