#ifndef SOFT_RTR_H
#define SOFT_RTR_H
//defs
#include "MESSAGES.h"

//math
#include "../math/Tools.h"
#include "../math/Vectors.h"
#include "../math/Matrixes.h"
#include "../math/Compute.h"

//sdl_display
#include "../sdl_display/Display.h"
#include "../sdl_display/DisplayStructs.h"

//renderer
#include "../renderer/Frame.h"
#include "../renderer/Object.h"
#include "../renderer/Scene.h"
#include "../renderer/Camera.h"
#include "../renderer/Light.h"
#include "../renderer/ParallelLight.h"
#include "../renderer/Renderer.h"
#include "../renderer/Fragment.h"
#include "../renderer/Primitive.h"
#include "../renderer/VertexShade.h"
#include "../renderer/Clip.h"
#include "../renderer/Rasterizer.h"
#include "../renderer/FragmentShade.h"
#include "../renderer/OutputMerger.h"

//driver
#include "../driver/Loader.h"
#include "../driver/PngLoader.h"

//data
#include "../data/Model.h"
#include "../data/ModelPool.h"
#include "../data/HEdge.h"
#include "../data/Material.h"
#include "../data/Mesh.h"
#include "../data/Texture.h"
#include "../data/Triangle.h"
#include "../data/Vertex.h"
#include "../data/AABB.h"

//threads
#include "../threads/MultThreadArgs.h"

#endif
