#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float time;
uniform sampler2D texture1;

void main()
{
    vec4 texColor = texture(texture1, TexCoord);

    // Рух кольорової хвилі
    float wave = sin(TexCoord.x * 6.0 + time * 2.0);

    // Перетворюємо -1..1 у 0..1
    wave = wave * 0.5 + 0.5;

    vec3 blue = vec3(0.1, 0.2, 1.0);
    vec3 pink = vec3(1.0, 0.1, 0.5);

    vec3 overlayColor = mix(blue, pink, wave);

    // прозорість overlay
    float opacity = 0.35;

    vec3 finalColor = mix(
        texColor.rgb,
        overlayColor,
        opacity
    );

    FragColor = vec4(finalColor, texColor.a);
}