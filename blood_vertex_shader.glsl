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
uniform float a;    // Coefficient for x^2

// Outputs to fragment shader
out vec4 color_interp;
out vec2 uv_interp;

void main()
{
    // Calculate the time offset for each particle
    float time_offset = time + t;

    // Calculate the new position along the parabola
    float x = vertex.x + dir.x * time_offset;
    float y = a * x * x;

    // Create the new position vector
    vec4 pos = vec4(x * time_offset, y * time_offset, 0.0, 1.0);

    // Apply transformations
    gl_Position = view_matrix * transformation_matrix * pos;

    // Pass the texture coordinates to the fragment shader
    uv_interp = uv;

    color_interp = vec4(1.0, 2.0, 2.0, 1.0); // Red color
}