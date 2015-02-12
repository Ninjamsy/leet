#include "ParkMiller.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const long a = 16807;
const long m = 2147483647;
const long q = 127773;
const long r = 2836;

Myway::Myway(long Seed_ ) : Seed(Seed_)
{
    if (Seed ==0)
        Seed=1;
}

  
void Myway::SetSeed(long Seed_)
{
  Seed=Seed_;
  if (Seed ==0)
        Seed=1;
}

unsigned long Myway::Max()
{
    return m-1;
}

unsigned long Myway::Min()
{
    return 1;
}

long Myway::GetOneRandomInteger()
{
	srand(time(NULL));
	Seed = rand() %2147483647;

    return Seed;
}


RandomMyway::RandomMyway(unsigned long Dimensionality, unsigned long Seed)
:    RandomBase(Dimensionality),
    InnerGenerator(Seed),
    InitialSeed(Seed)
{
    Reciprocal = 1/(1.0+InnerGenerator.Max());
}

RandomBase* RandomMyway::clone() const
{
    return new RandomMyway(*this);   
}

void RandomMyway::GetUniforms(MJArray& variates)
{
    for (unsigned long j=0; j < GetDimensionality(); j++)
        variates[j] = InnerGenerator.GetOneRandomInteger()*Reciprocal;

}
    
void RandomMyway::Skip(unsigned long numberOfPaths)
{
    MJArray tmp(GetDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        GetUniforms(tmp);
}

void RandomMyway::SetSeed(unsigned long Seed)
{
    InitialSeed = Seed;
    InnerGenerator.SetSeed(Seed);
}

void RandomMyway::Reset()
{
    InnerGenerator.SetSeed(InitialSeed);
}


void RandomMyway::ResetDimensionality(unsigned long NewDimensionality)
{
    RandomBase::ResetDimensionality(NewDimensionality);
    InnerGenerator.SetSeed(InitialSeed);
}

 