//
// Created by Vlad Boroday on 2024-12-30.
//

#ifndef UNTITLED4_INCLUDES_H
#define UNTITLED4_INCLUDES_H

#include "raylib.h"
#include "fmt/format.h"
#include "simpleTypes.h"
#include "glm/glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL
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

#endif //UNTITLED4_INCLUDES_H
