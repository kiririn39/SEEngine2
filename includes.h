//
// Created by Vlad Boroday on 2024-12-30.
//

#ifndef UNTITLED4_INCLUDES_H
#define UNTITLED4_INCLUDES_H

#include "raylib.h"
#include "simpleTypes.h"
#include "glm/glm.hpp"

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include "glm/ext.hpp"

#ifdef DEBUG
#define ASSERT(X) assert(X)
#else
#define ASSERT(X)
#endif

#ifdef DEBUG_EXTRA
#define ASSERT_EXTRA(X) assert(X)
#else
#define ASSERT_EXTRA(X)
#endif

#include "semath.h"
#include "sestring.h"

#endif //UNTITLED4_INCLUDES_H
