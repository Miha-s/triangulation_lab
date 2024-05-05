#ifndef RANDOMNUMBERGENERATOR_HPP
#define RANDOMNUMBERGENERATOR_HPP

#include <random>

class RandomNumberGenerator
{
    std::mt19937_64 m_rng;
    std::uniform_real_distribution< float > m_distr;

public:
    RandomNumberGenerator( float min = 0, float max = 1 );

    // default [0, 1)
    void set_range( float min, float max );

    float get_number( );
};

#endif  // RANDOMNUMBERGENERATOR_HPP
