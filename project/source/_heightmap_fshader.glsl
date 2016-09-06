#version 430 core

out vec4 color;

uniform vec2 terrainOffset;
uniform float effect;

in vec2 fragUV;

// Simple pseudo random generator, that seeds with the coordinate values
// @src: http://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

// Implementation of Perlin Noise and fBm
// @src: http://www.kamend.com/2012/06/perlin-noise-and-glsl/
vec4 mod289(vec4 x)
{
    return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x)
{
    return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r)
{
    return 1.79284291400159 - 0.85373472095314 * r;
}

vec2 fade(vec2 t) {
    return t*t*t*(t*(t*6.0-15.0)+10.0);
}

// Classic Perlin noise
float cnoise(vec2 P)
{
    vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
    vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
    Pi = mod289(Pi); // To avoid truncation effects in permutation
    vec4 ix = Pi.xzxz;
    vec4 iy = Pi.yyww;
    vec4 fx = Pf.xzxz;
    vec4 fy = Pf.yyww;

    vec4 i = permute(permute(ix) + iy);

    vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;
    vec4 gy = abs(gx) - 0.5 ;
    vec4 tx = floor(gx + 0.5);
    gx = gx - tx;

    vec2 g00 = vec2(gx.x,gy.x);
    vec2 g10 = vec2(gx.y,gy.y);
    vec2 g01 = vec2(gx.z,gy.z);
    vec2 g11 = vec2(gx.w,gy.w);

    vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
    g00 *= norm.x;
    g01 *= norm.y;
    g10 *= norm.z;
    g11 *= norm.w;

    float n00 = dot(g00, vec2(fx.x, fy.x));
    float n10 = dot(g10, vec2(fx.y, fy.y));
    float n01 = dot(g01, vec2(fx.z, fy.z));
    float n11 = dot(g11, vec2(fx.w, fy.w));

    vec2 fade_xy = fade(Pf.xy);
    vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
    float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
    return 2.3 * n_xy;
}

// Classic Perlin noise, periodic variant
float pnoise(vec2 P, vec2 rep)
{
    vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
    vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
    Pi = mod(Pi, rep.xyxy); // To create noise with explicit period
    Pi = mod289(Pi);        // To avoid truncation effects in permutation
    vec4 ix = Pi.xzxz;
    vec4 iy = Pi.yyww;
    vec4 fx = Pf.xzxz;
    vec4 fy = Pf.yyww;

    vec4 i = permute(permute(ix) + iy);

    vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;
    vec4 gy = abs(gx) - 0.5 ;
    vec4 tx = floor(gx + 0.5);
    gx = gx - tx;

    vec2 g00 = vec2(gx.x,gy.x);
    vec2 g10 = vec2(gx.y,gy.y);
    vec2 g01 = vec2(gx.z,gy.z);
    vec2 g11 = vec2(gx.w,gy.w);

    vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
    g00 *= norm.x;
    g01 *= norm.y;
    g10 *= norm.z;
    g11 *= norm.w;

    float n00 = dot(g00, vec2(fx.x, fy.x));
    float n10 = dot(g10, vec2(fx.y, fy.y));
    float n01 = dot(g01, vec2(fx.z, fy.z));
    float n11 = dot(g11, vec2(fx.w, fy.w));

    vec2 fade_xy = fade(Pf.xy);
    vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
    float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
    return 2.3 * n_xy;
}

float fbm(vec2 P, int octaves, float lacunarity, float gain)
{
    float sum = 0.0;
    float amp = 1.0;
    vec2 pp = P;

    int i;

    for(i = 0; i < octaves; i+=1)
    {
        amp *= gain;
        sum += amp * cnoise(pp);
        pp *= lacunarity;
    }
    return sum;

}

float generateTerrainPerlin(vec2 position) {

    float frequency = 0.0;
    float amplitude = 0.0;

    int i = 0;
    int iterations = 20;

    float noise = 0.0;

    vec2 seed = position.xy;

    frequency = 0.1;
    amplitude = 1.2;

    // Make some cool Background
    for (i=0; i<3; i++) {
        noise += abs(amplitude/pow(2.0,float(i))*cnoise(seed*frequency*pow(2.0,float(i))));
    }

    frequency = 1.9;
    amplitude = 0.4;

    // Make some mountains
    for (i=0; i<iterations; i++) {
        noise += abs(amplitude/pow(2.0,float(i))*cnoise(seed*frequency*pow(2.0,float(i))));
    }

    // Limit the top of the mountains
    float limitedMax = min(1-(pow(20,-1*noise)),noise);

    // Height from (-1,1) to (0,1)
    // limitedMax = limitedMax*0.5 + 0.5;

    return limitedMax;
}

float generateTerrainFbm(vec2 position) {

    vec2 seed = position.xy;

    float noise = 0.0;

    noise += fbm(seed*4, 8, 2.6, 0.4)*2.0 + 0.2;
    noise += fbm(seed*25, 2, 9, 0.3)*0.4;

    return noise;
}

// Ridged MultiFractal Terrain Model
// @src: Texturing & Modeling: A Procedural Approach
float RidgedMultiFractal(vec3 point, float H, float lacunarity, float octaves, float offset, float gain)
{
    float result, frequency, signal, weight;
    int i;
    bool first = true;
    float exponentArray[15];

    frequency = 1.0;
    if (first)
    {
        for (int i = 0; i<octaves; ++i)
        {
            exponentArray[i] = pow(frequency, -H);
            frequency *= lacunarity;
        }

        first = false;
    }

    /* get first octave */
    signal = cnoise( point.xy );
    /* get absolute value of signal (this creates the ridges) */
    if ( signal < 0.0 ) signal = -signal;
    /* invert and translate (note that "offset" should be ~= 1.0) */
    signal = offset - signal;
    /* square the signal, to increase "sharpness" of ridges */
    signal *= signal;
    /* assign initial values */
    result = signal;
    weight = 1.0;

    for( i=1; i<octaves; i++ )
    {
        /* increase the frequency */
        point.x *= lacunarity;
        point.y *= lacunarity;
        point.z *= lacunarity;

        /* weight successive contributions by previous signal */
        weight = signal * gain;
        if ( weight > 1.0 ) weight = 1.0;
        if ( weight < 0.0 ) weight = 0.0;
        signal = cnoise( point.xy );
        if ( signal < 0.0 ) signal = -signal;
        signal = offset - signal;
        signal *= signal;
        /* weight the contribution */
        signal *= weight;
        result += signal * exponentArray[i];
    }

    return result;
}

void main(){

    float noise = 0.0;

    // Composite with Perlin
    // noise = generateTerrainPerlin(fragUV+terrainOffset);

    // Composite with fBm
    // noise = generateTerrainFbm(fragUV+terrainOffset);

    // Random noise
    // noise = rand(fragUV.xy+terrainOffset);

    // Perlin noise
    // noise = cnoise(fragUV.xy*5+terrainOffset);

    // fBm noise
    // noise = fbm(fragUV.xy, 10, 2.2, 0.9);

    float frequency = 1.0;
    float amplitude = 1.1;

    float H = 0.9;
    float lacunarity = 3.3;
    int ocatves = 9;
    float offset = 1.0;
    float gain = 3.2;

    if (effect > 1e-2) {
        amplitude = effect;
        H = effect;
    }

    // Ridged MultiFractal noise
    noise = RidgedMultiFractal(vec3(fragUV.xy*frequency, 1.0) * 3.0, H, lacunarity, ocatves, offset, gain) * amplitude;

    color = vec4(vec3(noise), 1.0);
}
