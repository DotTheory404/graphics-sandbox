#version 330 core
out vec4 FragColor;

in vec3 ourColor;
//in vec2 TexCoord;

//uniform float mixValue;

// texture samplers
//uniform sampler2D texture1;
//uniform sampler2D texture2;

uniform float time;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), mixValue);
	float t = sin(time) * 0.5 + 0.5;

    vec3 color = mix(
        ourColor,
        vec3(1.0, 0.2, 0.8),
        t
    );

    FragColor = vec4(color, 1.0);
}