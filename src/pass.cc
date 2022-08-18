#include "pass.h"

#include "thirdparty/cgltf/cgltf.h"
#include "renderable.h"
#include "src/modules/log/log.h"

void minbe::Pass::AddRenderable(Renderable &renderable) {
  if (renderable.need_update_) {
    renderable.Setup();
  }
}

void minbe::Pass::Excute(Renderable &renderable) {
  glUseProgram(m_pro);

  glBindVertexArray(renderable.vao_);
  glDrawElements(renderable.mode_, renderable.count_, GL_UNSIGNED_SHORT, NULL);

  log::log_print("Draw mode %d count %d", renderable.mode_, renderable.count_);
  driver::gl::check_gl_error("end of draw");
}
