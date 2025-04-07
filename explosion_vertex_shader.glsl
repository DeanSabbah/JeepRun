// Source code of vertex shader for particle system
#version 130

// Vertex buffer
in vec2 vertex; // Usually (0,0)
in vec2 dir;    // Normalized direction
in float t;     // Phase offset
in vec2 uv;     // Texture coordinates

// Uniforms
uniform mat4 transformation_matrix;
uniform mat4 view_matrix;
uniform float time; // Global timer

// Outputs to fragment shader
out vec4 color_interp;
out vec2 uv_interp;

void main()
{
    vec4 pos;
    float lifetime = 1.0;       // Seconds
    float maxRadius = 3.0;      // Max spread
    float acttime = time;

    // Clamp to [0, lifetime]
    float clampedTime = min(acttime, lifetime);

    // Normalize to [0,1] for easing
    float tNorm = clampedTime / lifetime;

    // Easing function
    float easeOut = 1 - (pow(1.0 - tNorm, 5.0) * pow(2, -10 * tNorm)); // Qunitic and exponential ease-out
    // Calculate final distance
    float dist = 3.0 * easeOut * maxRadius;

    // Compute final position
    pos = vec4(vertex.x + clampedTime * dist * dir.x, vertex.y + clampedTime * dist * dir.y, 0.0, 1.0);

    // Apply transformations
    gl_Position = view_matrix * transformation_matrix * pos;

      // Interpolate color for explosion effect
    vec3 startColor = vec3(1.0, 1.0, 0.0); // Bright yellow
    vec3 midColor1 = vec3(1.0, 0.5, 0.0);  // Orange
    vec3 midColor2 = vec3(1.0, 0.2, 0.0);  // Red
    vec3 endColor = vec3(0.1, 0.1, 0.1);   // Dark gray

    vec3 interpolatedColor;
    if (tNorm < 0.33) {
        interpolatedColor = mix(startColor, midColor1, tNorm / 0.33);
    } else if (tNorm < 0.66) {
        interpolatedColor = mix(midColor1, midColor2, (tNorm - 0.33) / 0.33);
    } else {
        interpolatedColor = mix(midColor2, endColor, (tNorm - 0.66) / 0.34);
    }

    // Set color and alpha based on lifetime
    float alpha = (acttime <= lifetime) ? 1.0 : 0.0;
    color_interp = vec4(interpolatedColor, alpha);

    // Pass UVs
    uv_interp = uv;
}