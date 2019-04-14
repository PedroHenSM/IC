#pragma once


#include <string>
#include <vector>
#include <map>
#include <memory>

extern "C" {
    #define GLEW_STATIC
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
}

//GLM Math Headers
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

//GLM SIMD Header
//#include <glm/gtx/simd_vec4.hpp>
//#include <glm/gtx/simd_mat4.hpp>
//#include <glm/gtx/simd_quat.hpp>
#include <glm/gtc/quaternion.hpp>

#include <exception>
#include "RendererException.h"

#include "RTTI.h"

#define DeleteObject(object) if((object) != NULL) {delete object; object = NULL;}
#define DeleteObjects(objects) if((objects) != NULL) {delete[] objects; objects = NULL;}

// OpenGL delete helpers
#define DeleteFramebuffer(object) if((object)) {glDeleteFramebuffers(1, &object); object = 0;}
#define DeleteFramebuffers(object, n) if((object)) {glDeleteFramebuffers(n, &object); object = 0;}
#define DeleteTexture(object) if((object)) {glDeleteTextures(1, &object); object = 0;}
#define DeleteTextures(object, n) if((object)) {glDeleteTextures(n, &object); object = 0;}

using namespace glm;
