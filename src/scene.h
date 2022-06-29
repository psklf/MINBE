#ifndef MINBE_SCENE_H_
#define MINBE_SCENE_H_

#include <unordered_map>
#include <cstdint>

#include "minbe_ret_code.h"
#include "node.h"
#include "renderable.h"

struct cgltf_data;
struct cgltf_node;
struct cgltf_scene;

namespace minbe {
  class Renderable;

  class Scene {
    public:
      Scene();
      virtual ~Scene();

      int ParseGLTFData(cgltf_data *gltf_data);

      void Update(float time) {}

      void GetRenderables(std::vector<Renderable> &renderables);
      std::vector<Renderable> &GetRenderables();


    private:
      void BuildScene();
      Node *BuildNode(cgltf_node *gltf_node, Node *parent);
      void GetRenderableFromNode(Node *node, std::vector<Renderable> &renderables);

      cgltf_scene *scene_;
      Node *root_node_;
      std::vector<Renderable> renderable_items_;
      std::unordered_map<std::uintptr_t, int> renderable_map_;
  };
}

#endif  // MINBE_SCENE_H_
