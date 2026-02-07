#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec3 color;

const vec2 size = vec2(800, 450);   // render size
const float samples = 5.0;          // pixels per axis; higher = bigger glow, worse performance
const float quality = 2.5; 	        // lower = smaller glow, better quality

void main(){
    vec4 texelColor = texture(texture0, fragTexCoord);
    vec4 source = vec4(color ,texelColor.a);

    finalColor = source;
}
