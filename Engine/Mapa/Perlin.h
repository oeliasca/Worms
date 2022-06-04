#pragma once
class Perlin
{

private:
	//permutation table
	unsigned char p[2280];

	//current seed
	unsigned int seed;

	float* perlinNoise1D;
	float octave;

public:
	//fade function
	inline float fade(float t) {
		return t * t * t * (t * (t * 6 - 15) + 10);
	};

	//linear interpolation
	inline float lerp(float t, float a, float b) {
		return a + t * (b - a);
	};

	//map function
	inline float map(float val, float ogMin, float ogMax, float newMin, float newMax) {
		//get proportion in original range
		float prop = (val - ogMin) / (ogMax - ogMin);
		return lerp(prop, newMin, newMax);
	};

	//gradient function
	//calculate the dot product between gradient vector and distance vector

	inline float grad(int hash, float x, float y, float z) {
		//convert the last 4 bits of the hash into one of the 12 possible gradients
		int h = hash & 0b1111;//= hash & 15 = hash % 16 = get last 4 bits

		//if the first bit 1, set to x, otherwise set to y
		float u = h < 0b1000 ? x : y;

		//if the fisrts/second bits 0,set to y
		//if the first/second bits 1, set to x
		//else set to z

		float v = h < 0b0100 ? y : h == 0b1100 || h == 0b1110 ? x : z;

		//make u,v negative based on the last 2 bits, then add results
		//adding results is like dot product because gradient components are 1,
		//so the results of dot product is adding components

		return ((h & 0b0001) == 0 ? u : -u) + ((h & 0b0010) == 0 ? v : -v);

	};

	Perlin(unsigned int seed,int w,int fr);
	void reseed(unsigned int _seed,int w);

	float noise1D(float x);
	float noise2D(float x,float y);
	float noise3D(float x,float y, float z);

	void generatePerlinNoise1D(int w);
	float* getPerlinNoise1D() { return perlinNoise1D; };

	float accumulatedNoise1D(float x, int octaves = 8, float lacunarity = 2.0f, float gain = 0.5f);
	float accumulatedNoise2D(float x, float y, int octaves = 8, float lacunarity = 2.0f, float gain = 0.5f);
	float accumulatedNoise3D(float x, float y, float z, int octaves = 8, float lacunarity = 2.0f, float gain = 0.5f);

};

