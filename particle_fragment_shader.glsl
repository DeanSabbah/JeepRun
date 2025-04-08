// Source code of fragment shader
#version 130

// Attributes passed from the vertex shader
in vec4 color_interp;
in vec2 uv_interp;

// Texture sampler
uniform sampler2D onetex;

void main()
{
    // Sample texture
    vec4 texColor = texture2D(onetex, uv_interp);

    // Modulate texture color with interpolated color
    vec3 finalColor = texColor.rgb * color_interp.rgb;

    // Assign color to fragment with interpolated alpha
    gl_FragColor = vec4(finalColor, texColor.a * color_interp.a);

    // Check for transparency and discard fragment if fully transparent
    if (gl_FragColor.a < 1.0)
    {
        discard;
    }
}
