#include "RandomNumberGenerator.hpp"

#include <chrono>
#include <random>

RandomNumberGenerator::RandomNumberGenerator( float min, float max )
{
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now( ).time_since_epoch( ).count( );
    std::seed_seq ss{ uint32_t( timeSeed & 0xffffffff ), uint32_t( timeSeed >> 32 ) };
    m_rng.seed( ss );

    // initialize a uniform distribution between 0 and 1
    m_distr = std::uniform_real_distribution< float >( min, max );
}

void
RandomNumberGenerator::set_range( float min, float max )
{
    m_distr = std::uniform_real_distribution< float >( min, max );
}

float
RandomNumberGenerator::get_number( )
{
    return m_distr( m_rng );
}
