#include "scene.h"

#include <vector>

#include "src/modules/log/log.h"
#include "thirdparty/cgltf/cgltf.h"
#include "renderable.h"
#include "node.h"

minbe::Scene::Scene() : scene_{nullptr}, root_node_{nullptr} { }

minbe::Scene::~Scene() {
  if (root_node_) {
    //TODO delete node
  }
}
int minbe::Scene::ParseGLTFData(cgltf_data *gltf_data) {
        cgltf_scene* scene = gltf_data->scenes;
        scene_ = scene;

        for (cgltf_size i = 0; i < scene_->nodes_count; ++i) {
          auto *root = BuildNode(scene_->nodes[i], nullptr);
          log::log_print("Build nodes and root node is %s", root->name.data());
          root_node_ = root;
          break;
        }
        return kMinbeRetOk;
}

void minbe::Scene::GetRenderables(std::vector<Renderable> &renderables) {
  if (root_node_) GetRenderableFromNode(root_node_, renderables);
}

std::vector<minbe::Renderable> &minbe::Scene::GetRenderables() {
  if (root_node_) GetRenderableFromNode(root_node_, renderable_items_);
  return renderable_items_;
}

minbe::Node *minbe::Scene::BuildNode(cgltf_node *gltf_node, Node *parent) {
  Node *node = nullptr;

  if (gltf_node->mesh) {
    auto *mesh_node = new MeshNode();
    mesh_node->type = NodeType::Mesh;
    cgltf_mesh *mesh = gltf_node->mesh;
    mesh_node->primitives = mesh->primitives;
    mesh_node->primitive_size = mesh->primitives_count;
    mesh_node->name = gltf_node->name;
    log::log_print("new Node %s ", gltf_node->name);

    node = mesh_node;
  }

  node->parent = parent;
  if (parent) {
    parent->children.push_back(node);
  }

  for (cgltf_size i = 0; i < gltf_node->children_count; ++i) {
    BuildNode(gltf_node->children[i], node);
  }
  return node;
}

void minbe::Scene::GetRenderableFromNode(Node *node, std::vector<Renderable> &renderables) {
  if (node->type == NodeType::Mesh) {
    auto *mesh_node = dynamic_cast<MeshNode *>(node);
    for (size_t j = 0; j < mesh_node->primitive_size; ++j) {
      cgltf_primitive &primitive = mesh_node->primitives[j];
      auto key = reinterpret_cast<std::uintptr_t>(&primitive);
      auto found = renderable_map_.find(key);
      if (found == renderable_map_.end() ) {
        Renderable r(primitive);
        r.need_update_ = mesh_node->primitive_update;
        renderables.push_back(r);
        renderable_map_.emplace(key, renderables.size() - 1);
        log::log_print("insert new renderable %d %d ", key, renderables.size() - 1);
      } else {
        auto &r = renderables[found->second];
        log::log_print("get exist rendrable %d %d", key, found->second);
        r.need_update_ = mesh_node->primitive_update;
      }
      mesh_node->primitive_update = false;
    }
  }

  for (auto *n : node->children) {
    GetRenderableFromNode(n, renderables);
  }

}
