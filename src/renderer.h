#ifndef MINBE_RENDERER_H_
#define MINBE_RENDERER_H_

#include <vector>
#include <memory>

#include "modules/log/log.h"

#include "pass.h"
#include "scene.h"

namespace minbe {
  class Renderer {
    public:
      void Prepare() {
      }

      void Render(Scene *scene) {
        // build render pass
        Pass pass;
        pass.Prepare();

        // fetch renderables
        std::vector<Renderable> &renderables = scene->GetRenderables();
        for (auto &r : renderables) {
          pass.AddRenderable(r);
        }

        for (auto &r : renderables) {
          pass.Excute(r);
        }
      }

    private:
      std::vector<std::unique_ptr<Pass> > m_passes;
  };
}

#endif  // MINBE_RENDERER_H_
