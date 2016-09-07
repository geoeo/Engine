#pragma once
#include "Geometry.h"
#include "common.h"

class Bezier : public Geometry {

private:
	vec3* control_points;
	int num_segments;
	int num_control_points;
	vec3 line_color;

public:

    // Constructor
    Bezier(vec3*, int, int, vec3);

    // Destructor
    ~Bezier();

    // Evaluate the line segments
    void load(void);


    //***** Static methods

    // Compute binomial coefficients
    static unsigned long binomial(unsigned long, unsigned long);

    // Evaluate the bezier curve
    static vec3 eval3d(vec3[], int, float);
    static vec2 eval2d(vec2[], int, float);

    // Evaluate the bezier curve with uniform length
    static float length2d(vec2[], int, int);
    static vec2 eval_uniform2d(vec2[], int, float, int);
    static float length3d(vec3[], int, int);
    static vec3 eval_uniform3d(vec3[], int, float, int);

    // Easeing effects
    static float easeIn(float);
    static float easeOut(float);
    static float easeInOut(float);
};
