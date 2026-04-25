#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec3 color;
uniform float time;

const float renderWidth = 800;
const float renderHeight = 800;

const vec2 size = vec2(renderWidth, renderHeight);   // render size
const float samples = 20.0;          // pixels per axis; higher = bigger glow, worse performance
const float quality = 20; 	        // lower = smaller glow, better quality
float offset = 0.0;

void main(){

    vec4 sum = vec4(0);
    vec2 sizeFactor = vec2(1)/size*quality;

    float frequency = renderHeight/3.0;

    const int range = 2;            // should be = (samples - 1)/2;

    for (int x = -range; x <= range; x++)
    {
        for (int y = -range; y <= range; y++)
        {
            sum += texture2D(texture0, fragTexCoord + vec2(x, y)*sizeFactor);
        }
    }

    float globalPos = (fragTexCoord.y + offset)*frequency;
    float wavePos = cos((fract(globalPos) - 0.5)*3.14);

    vec4 texelColor = texture(texture0, fragTexCoord);
    vec4 source = vec4(color ,texelColor.a);

    finalColor = mix(vec4(0.0, 0.3, 0.0, 0.0), ((sum/(samples*samples)) + source)*colDiffuse, wavePos);
}
