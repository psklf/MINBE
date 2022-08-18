#ifndef MINBE_RENDERABLE_H_
#define MINBE_RENDERABLE_H_

#include "drivers/gl/opengl_driver.h"

struct cgltf_primitive;

namespace minbe {
  class Renderable {
    public:
      Renderable(cgltf_primitive &p);

      void Setup();

      cgltf_primitive &GetPrimitve() { return primitive_; }

      GLuint vao_;
      GLenum mode_;
      GLsizei count_;
      bool need_update_;
    private:
      cgltf_primitive &primitive_;
  };
}

#endif  // MINBE_RENDERABLE_H_
