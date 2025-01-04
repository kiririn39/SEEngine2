//
// Created by Vlad Boroday on 2025-01-03.
//

#ifndef SEMATH_H
#define SEMATH_H

#include "raymath.h"

#ifdef RAYMATH_DISABLE_CPP_OPERATORS
#undef RAYMATH_DISABLE_CPP_OPERATORS
#endif

namespace SE
{
	constexpr Vector3 UP = Vector3(0.0f, 1.0f, 0.0f);
	constexpr Vector3 DOWN = Vector3(0.0f, -1.0f, 0.0f);

	constexpr Vector3 LEFT = Vector3(-1.0f, 0.0f, 0.0f);
	constexpr Vector3 RIGHT = Vector3(1.0f, 0.0f, 0.0f);

	constexpr Vector3 FORWARD = Vector3(0.0f, 0.0f, 1.0f);
	constexpr Vector3 BACK = Vector3(0.0f, 0.0f, -1.0f);
	
	class semath
	{
	};
}


#endif //SEMATH_H
