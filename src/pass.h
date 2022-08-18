#ifndef MINBE_PASS_H_
#define MINBE_PASS_H_

#include <string>

#include "drivers/gl/opengl_driver.h"

namespace minbe {
static const char VERTEX_SHADER[] =
    "#version 330 core\n"
    "layout(location = 1) in vec3 pos;\n"
    "layout(location = 2) in vec2 tc;\n"
    "layout(location = 3) in vec3 normal;\n"
    "out vec2 v_tc;\n"
    "out vec3 v_normal;\n"
    "void main() {\n"
    "    gl_Position = vec4(pos, 1.0);\n"
    "    v_tc = tc;\n"
    "    v_normal = normal;\n"
    "}\n";

static const std::string FRAGMENT_SHADER = R"(#version 330 core
    in vec2 v_tc;
    in vec3 v_normal;
    out vec4 out_color;

    vec4 base_color = vec4(0.3, 0.1, 0.1, 1.0);

    void main() {
      out_color = vec4(1.0, 0.0, 0.0, 1.0);
      out_color.rgb = (v_normal + 1.0) * 0.5;
    }
    )";

class Renderable;

class Pass {
  public:
    GLuint m_pro;

    virtual ~Pass() { }

    void Prepare() {
      m_pro = driver::gl::create_program(VERTEX_SHADER, FRAGMENT_SHADER.c_str());

      glUseProgram(m_pro);

    }

void AddRenderable(Renderable &renderable);

void Excute(Renderable &renderable);
};
}

#endif  // MINBE_PASS_H_
