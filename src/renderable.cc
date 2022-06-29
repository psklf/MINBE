#include "renderable.h"

#include "thirdparty/cgltf/cgltf.h"

minbe::Renderable::Renderable(cgltf_primitive &p) : vao_(0), mode_(GL_TRIANGLES),
         count_(0), need_update_(true), primitive_(p) {};
