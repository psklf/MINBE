#include "pass.h"

#include "thirdparty/cgltf/cgltf.h"
#include "renderable.h"
#include "src/modules/log/log.h"

void minbe::Pass::AddRenderable(Renderable &renderable) {
  if (!renderable.need_update_) { return; }
  // build vao vbo
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  renderable.vao_ = vao;

  // get data from renderable
  auto &primitive = renderable.GetPrimitve();

  // rendering mode
  renderable.mode_ = primitive.type;

  // Attributes
  for (cgltf_size i = 0; i < primitive.attributes_count; ++i) {
    cgltf_attribute &attr = primitive.attributes[i];
    if (attr.type == cgltf_attribute_type_position) {
      log::log_print("Add Renderable %s", attr.name);

      cgltf_accessor &accessor = attr.data[attr.index];
      void *data = accessor.buffer_view->buffer->data;

      GLuint vbo = 0;
      glGenBuffers(1, &vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, accessor.buffer_view->size, data, GL_STATIC_DRAW);
      glEnableVertexAttribArray(1);

      GLenum type = driver::gl::component_type_parse(accessor.component_type);
      glVertexAttribPointer(1, 3, type, accessor.normalized, accessor.stride, 0);
      log::log_print("Position Attribute size %d stride %d component_type %d",
          accessor.buffer_view->size, accessor.stride, type);

      renderable.count_ = accessor.count;
      driver::gl::check_gl_error("end of Vertex Attribute");
    }
  }

  // Indices
  auto *i_accessor = primitive.indices;

  log::log_print("accessor byteoffset %d; bufferview offset %d;",
      i_accessor->offset,
      i_accessor->buffer_view->offset);
  auto *indices_data = reinterpret_cast<uint8_t *>(
      i_accessor->buffer_view->buffer->data) + i_accessor->buffer_view->offset;

  GLuint ibo = 0;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_accessor->buffer_view->size, indices_data,
      GL_STATIC_DRAW);
  for (cgltf_size in = 0; in < renderable.count_; ++in) {
    //  log::log_print("indices %u ", indices_data[in]);
  }

  driver::gl::check_gl_error("end of indices");

  renderable.need_update_ = false;
}

void minbe::Pass::Excute(Renderable &renderable) {
  glUseProgram(m_pro);

  glBindVertexArray(renderable.vao_);
  glDrawElements(renderable.mode_, renderable.count_, GL_UNSIGNED_SHORT, NULL);

  log::log_print("Draw mode %d count %d", renderable.mode_, renderable.count_);
  driver::gl::check_gl_error("end of draw");
}


