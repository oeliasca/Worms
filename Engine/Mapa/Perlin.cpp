#include "Perlin.h"
#include <stdio.h>      
#include <cmath> 
#include <iostream>
#include <algorithm>
#include <random>
Perlin::Perlin(unsigned int seed, int w, int fr)
{
	perlinNoise1D = new float[w];
	//p = new unsigned char[w];
	octave = fr;
	reseed(seed,w);
}

void Perlin::reseed(unsigned int _seed,int w)
{
	seed = _seed;
	int w2 = w/2;
	for (unsigned int i = 0; i < w2; i++) {
		p[i] = i;
	}

	//shuffle
	std::shuffle(std::begin(p), std::begin(p) + w2, std::default_random_engine(seed));

	//duplicate array for overflow
	for (unsigned int i = 0; i < w2; i++) {
		p[w2+i] = p[i];
	}



}

float Perlin::noise1D(float x)
{
	//find smallest point of interval containing target
	
	int xi = (int)(std::floorf(x)) & 255;

	//get decimal value of each component

	x -= std::floorf(x);

	//get smooth value from fade function (becomes weight for each dimension)

	float sx = fade(x);

	//get hash value for all neighboring points
	unsigned char a, b;
	a = p[xi];
	b = p[xi + 1];

	//get weighted average
	float avg = lerp(
		sx,
		grad(a, x, 0, 0),
		grad(a, x - 1, 0, 0)
		);

	//return avg mapped from[-1,1] to [0,1]
	return map(avg, -1, 1, 0, 1);
}

float Perlin::noise2D(float x, float y)
{
	//find smallest point of square containing target

	int xi = (int)(std::floorf(x)) & 255;
	int yi = (int)(std::floorf(y)) & 255;

	//get decimal value of each component

	x -= std::floorf(x);
	y -= std::floorf(y);

	//get smooth value from fade function (becomes weight for each dimension)

	float sx = fade(x);
	float sy = fade(y);

	//get hash value for all neighboring points
	unsigned char aa, ab, ba, bb;
	aa = p[p[xi] + yi];
	ab = p[p[xi] + yi + 1];
	ba = p[p[xi + 1] + yi];
	bb = p[p[xi + 1] + yi + 1];

	//get weighted avg


	/*
	ab              bb


	   P(x,y)


	aa              ba
	*/
	float avg = lerp(
		sy,
		lerp( // "top"
			sx,
			grad(aa, x, y, 0),
			grad(ba, x - 1, y, 0)
		),
		lerp( // "bottom"
			sx,
			grad(ab, x, y - 1, 0),
			grad(bb, x - 1, y - 1, 0)
		)
	);

	return map(avg, -1, 1, 0, 1);
}

float Perlin::noise3D(float x, float y, float z)
{
	//find smallest point of cube containing target
	int xi = (int)(std::floorf(x)) & 255;
	int yi = (int)(std::floorf(y)) & 255;
	int zi = (int)(std::floorf(z)) & 255;

	//get decimal value of each component

	x -= std::floorf(x);
	y -= std::floorf(y);
	z -= std::floorf(z);
	//get smooth value from fade function (becomes weight for each dimension)

	float sx = fade(x);
	float sy = fade(y);
	float sz = fade(z);

	unsigned char aaa, aba, aab, abb, baa, bba, bab, bbb;
	aaa = p[p[p[xi] + yi] + zi];
	aba = p[p[p[xi] + yi + 1] + zi];
	aab = p[p[p[xi] + yi] + zi + 1];
	abb = p[p[p[xi] + yi + 1] + zi + 1];
	baa = p[p[p[xi + 1] + yi] + zi];
	bba = p[p[p[xi + 1] + yi + 1] + zi];
	bab = p[p[p[xi + 1] + yi] + zi + 1];
	bbb = p[p[p[xi + 1] + yi + 1] + zi + 1];

	float avg = lerp(
		sz,
		lerp( // "front"
			sy,
			lerp( // "top"
				sx,
				grad(aaa, x, y, z),
				grad(baa, x - 1, y, z)
			),
			lerp( // "bottom"
				sx,
				grad(aba, x, y - 1, z),
				grad(bba, x - 1, y - 1, z)
			)
		),
		lerp( // "rear"
			sy,
			lerp( // "top"
				sx,
				grad(aab, x, y, z - 1),
				grad(bab, x - 1, y, z)
			),
			lerp( // "bottom"
				sx,
				grad(abb, x, y - 1, z - 1),
				grad(bbb, x - 1, y - 1, z - 1)
			)
		)
	);
	return map(avg, -1, 1, 0, 1);
}

void Perlin::generatePerlinNoise1D(int w)
{
	for (int x = 0; x < w; x++)
	{
		perlinNoise1D[x] = accumulatedNoise1D(x / (w / octave),8,2.0f,0.25);
	}
}

float Perlin::accumulatedNoise1D(float x, int octaves, float lacunarity, float gain)
{
	float result = 0.0f;
	float amplitude = 1.0f;
	float frequency = 1.0f;
	float maxVal = 0.0f; // used to normalize result

	for (; octaves > 0; octaves--) {
		result += noise1D(x * frequency) * amplitude;

		maxVal += amplitude;

		amplitude *= gain;
		frequency *= lacunarity;
	}

	// return normalized result
	return result / maxVal;
}

float Perlin::accumulatedNoise2D(float x, float y, int octaves, float lacunarity, float gain)
{
	float result = 0.0f;
	float amplitude = 1.0f;
	float frequency = 1.0f;
	float maxVal = 0.0f; // used to normalize result

	for (; octaves > 0; octaves--) {
		result += noise2D(x * frequency, y * frequency) * amplitude;

		maxVal += amplitude;

		amplitude *= gain;
		frequency *= lacunarity;
	}

	// return normalized result
	return result / maxVal;
}

float Perlin::accumulatedNoise3D(float x, float y, float z, int octaves, float lacunarity, float gain)
{
	float result = 0.0f;
	float amplitude = 1.0f;
	float frequency = 1.0f;
	float maxVal = 0.0f; // used to normalize result

	for (; octaves > 0; octaves--) {
		result += noise3D(x * frequency, y * frequency, z * frequency) * amplitude;

		maxVal += amplitude;

		amplitude *= gain;
		frequency *= lacunarity;
	}

	// return normalized result
	return result / maxVal;
}
