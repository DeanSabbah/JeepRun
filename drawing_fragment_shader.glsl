#version 130

// Attributes passed from the vertex shader
in vec4 color_interp;
in vec2 uv_interp;

// Texture sampler
uniform sampler2D onetex;

uniform float health;
uniform float maxHealth;

void main()
{

    // Calculate the proportion of health remaining
    float healthRatio = float(health) / float(maxHealth);

    // Set the default color
    vec4 color = vec4(1.0, 0.0, 0.0, 1.0);

    // If the fragment is not on the shape, make it transparent
    vec2 coord = uv_interp;
    vec2 boxSize = vec2(0.5, 0.1);
    if (abs(coord.x) > boxSize.x || abs(coord.y) > boxSize.y) {
        color.a = 0.0;
    }

    // Calculate the cutoff position based on health
    float cutoff = boxSize.x - (2.0 * boxSize.x * healthRatio);

    // Discard fragments to the left of the cutoff
    if (coord.x < cutoff) {
        color.rgb = vec3(1.0, 1.0, 1.0);
    }

    // Check for transparency
    if (color.a < 1.0) {
        discard;
    }

    gl_FragColor = color;
}
