#include "RandomScript.h"
random_device GameRandom::RD;
mt19937 GameRandom::Mt = mt19937(RD());