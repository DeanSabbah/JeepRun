#version 130

// Attributes passed from the vertex shader
in vec4 color_interp;
in vec2 uv_interp;

// Texture sampler
uniform sampler2D onetex;
uniform bool grayscale;
uniform bool invincible;

void main()
{
    // Sample texture
    vec4 color = texture2D(onetex, uv_interp);

    // Convert color to grayscale if grayscale mode is enabled
    if (grayscale) {
        float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
        color = vec4(vec3(gray), color.a);
    }
    else if(invincible){
        color.rgb = mix(color.rgb, vec3(0.937, 0.78, 0.02), 0.5); 
    }

    // Assign color to fragment
    gl_FragColor = color;

    // Check for transparency
    if (color.a < 1.0)
    {
         discard;
    }
}