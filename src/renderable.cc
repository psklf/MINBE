#include "renderable.h"

#include "thirdparty/cgltf/cgltf.h"
#include "src/modules/log/log.h"

minbe::Renderable::Renderable(cgltf_primitive &p)
    : vao_(0),
      mode_(GL_TRIANGLES),
      count_(0),
      need_update_(true),
      primitive_(p){};

void minbe::Renderable::Setup() {
  // build vao vbo
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  this->vao_ = vao;

  // rendering mode
  mode_ = primitive_.type;

  // Attributes
  for (cgltf_size i = 0; i < primitive_.attributes_count; ++i) {
    cgltf_attribute &attr = primitive_.attributes[i];
    log::log_print("Loop Attribute %s", attr.name);
    GLuint vbo_ = 0;
    if (attr.type == cgltf_attribute_type_position) {
      cgltf_accessor &accessor = attr.data[attr.index];
      log::log_print("bufferview Offset %u; accessor Offset %u;",
                     accessor.buffer_view->offset, accessor.offset);

      if (vbo_ == 0) {
        glGenBuffers(1, &vbo_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        void *data =
            reinterpret_cast<uint8_t *>(accessor.buffer_view->buffer->data) +
            accessor.buffer_view->offset;
        glBufferData(GL_ARRAY_BUFFER, accessor.buffer_view->size, data,
                     GL_STATIC_DRAW);
      }
      glBindBuffer(GL_ARRAY_BUFFER, vbo_);
      glEnableVertexAttribArray(1);

      GLenum type = driver::gl::component_type_parse(accessor.component_type);
      glVertexAttribPointer(1, 3, type, accessor.normalized, accessor.stride,
                            reinterpret_cast<void *>(accessor.offset));
      log::log_print(
          "Position Attribute size %d stride %d component_type %x; count is %u",
          accessor.buffer_view->size, accessor.stride, type, accessor.count);

      driver::gl::check_gl_error("end of Position Attribute");
    } else if (attr.type == cgltf_attribute_type_normal) {
      cgltf_accessor &accessor = attr.data[attr.index];
      log::log_print("bufferview Offset %u; accessor Offset %u;",
                     accessor.buffer_view->offset, accessor.offset);
      GLenum type = driver::gl::component_type_parse(accessor.component_type);
      log::log_print(
          "Normal Attribute size %d stride %d component_type %x; count is %u",
          accessor.buffer_view->size, accessor.stride, type, accessor.count);

      if (vbo_ == 0) {
        void *data =
            reinterpret_cast<uint8_t *>(accessor.buffer_view->buffer->data) +
            accessor.buffer_view->offset;
        glGenBuffers(1, &vbo_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, accessor.buffer_view->size, data,
                     GL_STATIC_DRAW);
      }

      glBindBuffer(GL_ARRAY_BUFFER, vbo_);
      glVertexAttribPointer(3, 3, type, accessor.normalized, accessor.stride,
                            reinterpret_cast<void *>(accessor.offset));

      glEnableVertexAttribArray(3);
      driver::gl::check_gl_error("end of Normal Attribute");
    }
  }  // end of attributes loop

  // Indices
  auto *i_accessor = primitive_.indices;

  log::log_print(
      "Indices:\n bufferview offset %d; accessor byteoffset %d; index count %u",
      i_accessor->buffer_view->offset, i_accessor->offset, i_accessor->count);
  auto *indices_data =
      reinterpret_cast<uint8_t *>(i_accessor->buffer_view->buffer->data) +
      i_accessor->buffer_view->offset;

  GLuint ibo = 0;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_accessor->buffer_view->size,
               indices_data, GL_STATIC_DRAW);

  this->count_ = i_accessor->count;

  driver::gl::check_gl_error("end of indices");

  this->need_update_ = false;
}
