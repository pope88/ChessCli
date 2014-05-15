#ifndef _RANDOM_H_
#define _RANDOM_H_


#include "Platform.h"

namespace System
{

class Random
{
public:
	Random();
	/// Creates and initializes the Randomizer.

	Random(UInt64 seed);
	/// Creates and initializes the Randomizer.
	/// Specify the seed

	~Random();
	/// Destroys the Randomizer.

	UInt32 next();
	/// Returns the next 32-bit pseudo random number.

	UInt32 next(UInt32 n);
	/// Returns the next 32-bit pseudo random number modulo n.

	UInt64 next64();
	/// Returns the next 64-bit pseudo random number.

	UInt64 next64(UInt64 n);
	/// Returns the next 64-bit pseudo random number modulo n.

	char nextChar();
	/// Returns the next pseudo random character.

	bool nextBool();
	/// Returns the next boolean pseudo random value.

	float nextFloat();
	/// Returns the next float pseudo random number between 0.0 and 1.0.

	double nextDouble();
	/// Returns the next double pseudo random number between 0.0 and 1.0.

private:
	void initState(UInt64 seed);
	UInt64 getRandSeed();

private:
	void * randState;
};


//
// inlines
//
inline UInt32 Random::next()
{
	return UInt32(next64());
}


inline UInt32 Random::next(UInt32 n)
{
	return UInt32(next64() % n);
}


inline UInt64 Random::next64(UInt64 n)
{
	return next64() % n;
}


inline char Random::nextChar()
{
	return char((next64() >> 3) & 0xFF);
}


inline bool Random::nextBool()
{
	return (next64() & 0x1000ULL) != 0;
}


inline float Random::nextFloat()
{
	return float(nextDouble());
}

}

#endif // _RANDOM_H_
