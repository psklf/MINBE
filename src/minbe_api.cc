#include "minbe_api.h"

#define CGLTF_IMPLEMENTATION
#include "thirdparty/cgltf/cgltf.h"

#include "modules/log/log.h"
#include "renderer.h"
#include "scene.h"

minbe::Renderer *renderer = nullptr;
minbe::Scene *gScene = nullptr;
cgltf_data *gData = nullptr;

int minbe_init() {
  gScene = new minbe::Scene();
  return 0;
}

int minbe_load(const char *gltf) {
  cgltf_options options = {};
  cgltf_data* data = NULL;
  cgltf_result result = cgltf_parse_file(&options, gltf, &data);
  if (result != cgltf_result_success) { return kMinbeRetLoadFail; }
  result = cgltf_load_buffers(&options, data, gltf);
  if (result != cgltf_result_success) { return kMinbeRetLoadFail; }

  gData = data;
  gScene->ParseGLTFData(data);

  return kMinbeRetOk;
}

int tick(float time) {
  gScene->Update(time);
  return 0;
}

int minbe_render() {
  if (!renderer) {
    minbe::log::log_print("new Renderer...");
    renderer = new minbe::Renderer();
    renderer->Prepare();
  }
  renderer->Render(gScene);
  return 0;
}

int minbe_destroy() {
  minbe::log::log_print("Destroy... ");
  delete renderer;
  cgltf_free(gData);
  return 0;
}
