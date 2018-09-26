#ifndef GLUTILS
#define GLUTILS 1 

#include <stdio.h>
#include <iostream>
#include <glad/glad.h>

GLuint createShader(GLenum shaderType, const char* src);
GLuint createProgram(const char* vtxSrc, const char* fragSrc);
bool checkGlError(const char* funcName);

#endif
