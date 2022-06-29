#ifndef MINBE_ENIGNE_H_
#define MINBE_ENIGNE_H_

#include "minbe_ret_code.h"

#ifdef __cplusplus
extern "C" {
#endif

int minbe_init();

int minbe_load(const char *gltf);

int tick();

int minbe_render();

int minbe_destroy();

#ifdef __cplusplus
}
#endif

#endif  // MINBE_ENIGNE_H_

