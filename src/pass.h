#ifndef MINBE_PASS_H_
#define MINBE_PASS_H_

#include "drivers/gl/opengl_driver.h"

namespace minbe {
static const char VERTEX_SHADER[] =
    "#version 330 core\n"
    "layout(location = 1) in vec3 pos;\n"
    "layout(location = 2) in vec2 tc;\n"
    "out vec2 v_tc;\n"
    "void main() {\n"
    "    gl_Position = vec4(pos, 1.0);\n"
    "    v_tc = tc;\n"
    "}\n";

static const char FRAGMENT_SHADER[] =
    "#version 330 core\n"
    "in vec2 v_tc;\n"
    "out vec4 out_color;\n"
    "void main() {\n"
    "    out_color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

class Renderable;

class Pass {
  public:
    GLuint m_pro;

    virtual ~Pass() { }

    void Prepare() {
      m_pro = driver::gl::create_program(VERTEX_SHADER, FRAGMENT_SHADER);

      glUseProgram(m_pro);

    }

void AddRenderable(Renderable &renderable);

void Excute(Renderable &renderable);
};
}

#endif  // MINBE_PASS_H_
