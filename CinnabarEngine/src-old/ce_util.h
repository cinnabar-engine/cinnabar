#include <memory>

#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "rendering/Vertex.h"
#include "rendering/Mesh.h"

#define PTR std::shared_ptr
#define PTR_CAST = dynamic_pointer_cast
#define OBJMAP(x) std::map<std::string,PTR<x>>
