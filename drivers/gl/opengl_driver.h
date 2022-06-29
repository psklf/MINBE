#ifndef MINBE_OPENGL_DRIVER_H_
#define MINBE_OPENGL_DRIVER_H_

#include <glad/glad.h>

namespace minbe {
  namespace driver {
    namespace gl {
      GLuint create_program(const char* vtxSrc, const char* fragSrc);

      bool check_gl_error(const char* funcName);

      GLenum component_type_parse(int type);
    }
  }
}

#endif  // MINBE_OPENGL_DRIVER_H_
