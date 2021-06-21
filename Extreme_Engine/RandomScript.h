#pragma once

#include <time.h>
#include <random>
using namespace std;

class GameRandom
{
private:
	static random_device RD;
	static mt19937 Mt;
	//static mt19937_64 Mt64;

public:
	// 무조건 float의 최소부터 최대값의 난수를 리턴한다.
	static float RandomFloat() {
		return (float)Mt();
	}

	static double RandomDouble(double _Min, double _Max) {

		if (_Min > _Max)
		{
			double temp = _Min;
			_Min = _Max;
			_Max = temp;
		}

		uniform_real_distribution<double> FUID = uniform_real_distribution<double>(_Min, _Max);

		return FUID(Mt);
	}

	static float RandomFloat(float _Min, float _Max) {

		uniform_real_distribution<float> FUID = uniform_real_distribution<float>(_Min, _Max);

		return FUID(Mt);
	}

	static float RandomFloat(float _Max) {

		uniform_real_distribution<float> FUID = uniform_real_distribution<float>(0.0f, _Max);

		return FUID(Mt);
	}

	static int RandomInt(int _Max) {

		uniform_int_distribution<int> UID = uniform_int_distribution<int>(0, _Max);

		return UID(Mt);
	}

	static int RandomInt(int _Min, int _Max) {

		uniform_int_distribution<int> UID = uniform_int_distribution<int>(_Min, _Max);

		return UID(Mt);
	}

	static int RandomInt() {

		return Mt();
	}

private:
	GameRandom() {}
	~GameRandom() {}

private:

};
