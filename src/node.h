#ifndef MINBE_NODE_H_
#define MINBE_NODE_H_

#include <string>
#include <vector>

#include <Eigen/Dense>

using Eigen::MatrixXf;

struct cgltf_primitive;

namespace minbe {
  enum class NodeType { Unknown, Mesh, Camera, Light };

  class Node {
    public:
    Node() : type(NodeType::Unknown), parent(nullptr) {
      MatrixXf mat(4, 4);
      mat(0, 0) = 1.0F;
      mat(1, 1) = 1.0F;
      mat(2, 2) = 1.0F;
      mat(3, 3) = 1.0F;
    }
    virtual ~Node() {}

    NodeType type;
    std::string name;
    Node *parent;
    std::vector<Node *>children;
  };

  class MeshNode : public Node {
    public:
      MeshNode() : primitives(nullptr), primitive_size(0),
      primitive_update(true) { }
      cgltf_primitive *primitives;
      size_t primitive_size;
      bool primitive_update;
  };

  class CameraNode : public Node {

  };
}
#endif  // MINBE_NODE_H_
