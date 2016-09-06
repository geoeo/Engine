#include "Bezier.h"
#include "math.h"

// Constructor
Bezier::Bezier (vec3* controlPoints, int numControlPoints, int numSegments, vec3 lineColor) {

    num_segments = numSegments;

    control_points = controlPoints;

    num_control_points = numControlPoints;

    line_color = lineColor;

    nVertices = num_segments;

    // Vertices of the curve
    vertices = new vec3[nVertices];

    // Normals of the curve
    normals = new vec3[nVertices];

    // Colors of the curve
    colors = new vec3[nVertices];

    // UVs of the curve
    UVs = new vec2[nVertices];

    drawMode = GL_LINE_STRIP;
}

// Destructor
Bezier::~Bezier() {

	delete[] vertices;
	delete[] normals;
    delete[] UVs;
    delete[] colors;

    delete[] control_points;
}

void Bezier::load() {

    int i = 0;
    float dt = 1.0/num_segments;

    for (i = 0; i < num_segments; i++) {

        vertices[i] = Bezier::eval3d(control_points, num_control_points, i*dt);
        normals[i] = vec3(1.0,0.0,0.0);
        colors[i] = line_color;
        UVs[i] = vec2(0.0,0.0);
    }
    
    std::cout << "Created Bezier curve with " << nVertices << " vertices" <<endl;
}

// @src: https://gist.github.com/jeetsukumaran/5392166
unsigned long Bezier::binomial(unsigned long n, unsigned long k) {
    
    unsigned long i, b;
    
    if (0 == k || n == k) return 1;
    if (k > n) return 0;

    if (k > (n - k)) {
        k = n - k;
    }
    
    if (1 == k) return n;
    b = 1;
    
    for (i = 1; i <= k; ++i) {
        b *= (n - (k - i));
        if (b < 0) return -1; /* Overflow */
        b /= i;
    }
    return b;
}

float Bezier::length2d(vec2 P[], int nP, int nS) {

    int i = 0;
    float dt = 1.0/nS;
    float len = 0.0;

    vec2 d_0 = Bezier::eval2d(P, nP, 0);

    // Get the total length
    for (i = 0; i < nS; i++) {
        
        // get the difference between point from the curve and previous
        vec2 d = Bezier::eval2d(P, nP, i*dt) - d_0;
        
        // get the lenght from the vector
        len += sqrt(d[0]*d[0] + d[1]*d[1]);

        // set the current position as the last position
        d_0 = d;
    }

    return len;
}

vec2 Bezier::eval_uniform2d(vec2 P[], int nP, float t, int nS) {

    int i = 0;
    float dt = 1.0/nS;
    float len = Bezier::length2d(P,nP,nS);
    float cur_len = 0.0;

    vec2 d_0 = Bezier::eval2d(P, nP, 0);

    // Compare with the total length
    for (i = 0; i < nS; i++) {
        
        vec2 a = Bezier::eval2d(P, nP, i*dt);

        // get the difference between point from the curve and previous
        vec2 d = a - d_0;
        
        // get the lenght from the vector
        cur_len += sqrt(d[0]*d[0] + d[1]*d[1]);

        if (cur_len/len >= t) return a;

        // set the current position as the last position
        d_0 = d;
    }

    return d_0;
}

float Bezier::length3d(vec3 P[], int nP, int nS) {

    int i = 0;
    float dt = 1.0/nS;
    float len = 0.0;

    vec3 d_0 = Bezier::eval3d(P, nP, 0);

    // Get the total length
    for (i = 0; i < nS; i++) {
        
        // get the difference between point from the curve and previous
        vec3 d = Bezier::eval3d(P, nP, i*dt) - d_0;
        
        // get the lenght from the vector
        len += sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2]);

        // set the current position as the last position
        d_0 = d;
    }

    return len;
}

vec3 Bezier::eval_uniform3d(vec3 P[], int nP, float t, int nS) {

    int i = 0;
    float dt = 1.0/nS;
    float len = Bezier::length3d(P,nP,nS);
    float cur_len = 0.0;

    vec3 d_0 = Bezier::eval3d(P, nP, 0);

    // Compare with the total length
    for (i = 0; i < nS; i++) {
        
        vec3 a = Bezier::eval3d(P, nP, i*dt);

        // get the difference between point from the curve and previous
        vec3 d = a - d_0;
        
        // get the lenght from the vector
        cur_len += sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2]);

        if (cur_len/len >= t) return a;

        // set the current position as the last position
        d_0 = d;
    }

    return d_0;
}

vec3 Bezier::eval3d(vec3 P[], int nP, float t) {

    float t_ = 1.0 - t;
    int i = 0; 
    int n = nP - 1;
    vec3 e = vec3(0.0,0.0,0.0);

    for (i = 0; i <= n; i ++) {

        e += (float) Bezier::binomial(n,i) * pow(t_,n-i) * pow(t,i) * P[i];
    }

    return e;
}

vec2 Bezier::eval2d(vec2 P[], int nP, float t) {

    float t_ = 1.0 - t;
    int i = 0; 
    int n = nP - 1;
    vec2 e = vec2(0.0,0.0);

    for (i = 0; i <= n; i ++) {

        e += (float) Bezier::binomial(n,i) * pow(t_,n-i) * pow(t,i) * P[i];
    }

    return e;
}

float Bezier::easeIn(float t){

    vec2 P[] = {
        vec2(0.0,0.0),
        vec2(0.4,0.0),
        vec2(1.0,1.0),
        vec2(1.0,1.0)
    }; 

    vec2 e = Bezier::eval2d(P,4,t);

    return e[1];    
}

float Bezier::easeOut(float t){

    vec2 P[] = {
        vec2(0.0,0.0),
        vec2(0.0,0.0),
        vec2(0.6,1.0),
        vec2(1.0,1.0)
    }; 

    vec2 e = Bezier::eval2d(P,4,t);

    return e[1];    
}

float Bezier::easeInOut(float t){

    vec2 P[] = {
        vec2(0.0,0.0),
        vec2(0.4,0.0),
        vec2(0.6,1.0),
        vec2(1.0,1.0)
    }; 

    vec2 e = Bezier::eval2d(P,4,t);

    return e[1];    
}