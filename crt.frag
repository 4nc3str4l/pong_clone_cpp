uniform sampler2D texture;
uniform float time;

vec2 crtCurve(vec2 coord) {
    coord = coord * 2.0 - vec2(1.0);
    coord = coord * (1.0 + pow(length(coord), 2) * 0.05);
    return coord;
}

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    vec2 coord = gl_TexCoord[0].xy;
    coord = crtCurve(coord);
    coord = (coord + 1.0) / 2.0;

    if (coord.x > 0.99 || coord.x < 0.01 || coord.y > 0.99 || coord.y < 0.01) {
        if (coord.x < 0.995 && coord.x > 0.005 && coord.y < 0.995 && coord.y > 0.005) {
            gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
            return;
        }
        else {
            gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
            return;
        }
    }

    vec2 pixelCoord = floor(coord * vec2(300, 300));
    coord = (pixelCoord + 0.5) / vec2(300, 300);

    vec4 color = texture2D(texture, coord);
    color.g *= 1.5;
    color.r *= 0.5;
    color.b *= 0.5;

    float line = sin(coord.y * 40.0 + time * 0.5);
    float hLine = sin(coord.x * 80.0 + time * 0.5);
    float totalLine = line * 0.7 + hLine * 0.3;

    float scanningLine = sin((coord.y - time * 0.01) * 20.0 + rand(vec2(time, coord.y)) * 5.0);
    if (abs(scanningLine) < 0.05) {
        color *= 0.8; 
    }

    color.rgb += totalLine * 0.04;

    vec4 rColor = texture2D(texture, coord + vec2(0.002, 0.0));
    vec4 bColor = texture2D(texture, coord - vec2(0.002, 0.0));
    
    gl_FragColor = vec4(rColor.r, color.g, bColor.b, color.a);
}
