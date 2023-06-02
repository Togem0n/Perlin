#pragma once

#include <math.h>
// usage?: 

// Perlin::noise(int seed, float x)
// Perlin::noise(int seed, float x, float y)
// Perlin::noise(int seed, float x, float y, float z)

class Perlin
{
    static const int p[];

    float noise(float x, float y) const
    {
        int X = static_cast<int>(floor(x)) & 255;
        int Y = static_cast<int>(floor(y)) & 255;
        float xd0 = x - floor(x);
        float yd0 = y - floor(y);
        float xd1 = xd0 - 1;
        float yd1 = yd0 - 1;

        float u = fade(xd0);
        float v = fade(yd0);
        // then calculate dot prod: dist vector . const vector
        // *** 
        // *** 
        // *** 

        // dist vec
        // (xd0, yd0) (xd1, yd0) (xd0, yd1) (xd1, yd1)

        // const vec
        // (p[X], p[Y]) (p[X + 1], p[Y]) (p[X], p[Y + 1]) (p[X + 1], p[Y + 1])
        int tr = p[p[X + 1] + Y + 1];
        int tl = p[p[X] + Y + 1];
        int br = p[p[X + 1] + Y];
        int bl = p[p[X] + Y];

        // get oconst 

        grad(tr, xd0, yd0);
        grad(br, xd0, yd0);


        // then apply fade function 

        // then lerp

    }

    static float fade(float t)
    {
        //return 6*t*t*t*t*t - 15*t*t*t*t + 10 * t*t*t;
        return t * t * t * (10 + (t * (-15 + 6 * t)));
    }

    static float grad(int hash, float x, float y)
    {
        switch (hash & 0x7)
        {
        	case 0x0: return x + y;
        	case 0x1: return x;
        	case 0x2: return x - y;
        	case 0x3: return -y;
        	case 0x4: return -x - y;
            case 0x5: return -x;
        	case 0x6: return -x + y;
        	case 0x7: return y;
        	default: return 0;
        }
    }

};

const int Perlin::p[] = {151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};
