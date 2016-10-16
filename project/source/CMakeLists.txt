get_filename_component(DIR ${CMAKE_CURRENT_LIST_DIR} NAME)

# Define this folder as project
project(${DIR})

# Create a variable for all sources
set(SOURCES)

# Add the Meshes
set(MESHES_DIR meshes)
include_directories(${MESHES_DIR})

# Add the Scenes
set(SCENES_DIR scenes)
include_directories(${SCENES_DIR})

set(SOURCES ${SOURCES}
  ${MESHES_DIR}/Skybox.cpp
  ${MESHES_DIR}/Cloud.cpp
  ${MESHES_DIR}/Water.cpp
  ${MESHES_DIR}/Terrain.cpp
  ${MESHES_DIR}/TerrainShadow.cpp
  ${MESHES_DIR}/ShadowMap.cpp
  ${MESHES_DIR}/Mirror.cpp
  ${MESHES_DIR}/Displacement.cpp
  ${MESHES_DIR}/Blur.cpp
  ${MESHES_DIR}/Bloom.cpp
  ${MESHES_DIR}/DeferredQuad.cpp
  ${SCENES_DIR}/MainScene.cpp
)

# Add the ThreeC++ library
set(THREECPP_DIR threecpp)
include_directories(${THREECPP_DIR})

set(SOURCES ${SOURCES}
  ${THREECPP_DIR}/Window.cpp
  ${THREECPP_DIR}/Scene.cpp
  ${THREECPP_DIR}/Object.cpp
  ${THREECPP_DIR}/Mesh.cpp
  ${THREECPP_DIR}/Model.cpp
  ${THREECPP_DIR}/camera/Camera.cpp
  ${THREECPP_DIR}/camera/PerspectiveCamera.cpp
  ${THREECPP_DIR}/camera/OrthographicCamera.cpp
  ${THREECPP_DIR}/camera/BufferCamera.cpp
  ${THREECPP_DIR}/controller/LeapController.cpp
  ${THREECPP_DIR}/material/Material.cpp
  ${THREECPP_DIR}/material/StaticMaterial.cpp
  ${THREECPP_DIR}/material/PhongMaterial.cpp
  ${THREECPP_DIR}/material/TextureMaterial.cpp
  ${THREECPP_DIR}/material/BillboardMaterial.cpp
  ${THREECPP_DIR}/light/Light.cpp
  ${THREECPP_DIR}/light/PointLight.cpp
  ${THREECPP_DIR}/light/DirectedLight.cpp
  ${THREECPP_DIR}/geometry/Geometry.cpp
  ${THREECPP_DIR}/geometry/BoxGeometry.cpp
  ${THREECPP_DIR}/geometry/BoxIndicesGeometry.cpp
  ${THREECPP_DIR}/geometry/StripBoxGeometry.cpp
  ${THREECPP_DIR}/geometry/PlaneGeometry.cpp
  ${THREECPP_DIR}/geometry/PlaneVert.cpp
  ${THREECPP_DIR}/geometry/Bezier.cpp
  ${THREECPP_DIR}/geometry/Surface.cpp
  ${THREECPP_DIR}/event/Event.cpp
  ${THREECPP_DIR}/event/Dispatcher.cpp
  ${THREECPP_DIR}/event/UpdateEvent.cpp
  ${THREECPP_DIR}/event/KeyEvent.cpp
  ${THREECPP_DIR}/event/MouseEvent.cpp
  ${THREECPP_DIR}/event/WheelEvent.cpp
  ${THREECPP_DIR}/event/ResizeEvent.cpp
  ${THREECPP_DIR}/event/LeapEvent.cpp
  ${THREECPP_DIR}/event/LeapLeftEvent.cpp
)

# Create an executable
add_executable(${DIR} ${SOURCES} main.cpp)

# Link Libraries
target_link_libraries(${DIR} ${COMMON_LIBS})

# Deploy the textures directory
target_deploy_dir(${DIR} textures)

# Compile and deploy the shaders
# Unfortunately, we have to call this in the current folder
# trust me, I tried everything!
target_stringify_shader(${DIR} _simple_vshader)
target_stringify_shader(${DIR} _simple_fshader)
target_stringify_shader(${DIR} _phong_vshader)
target_stringify_shader(${DIR} _phong_fshader)
target_stringify_shader(${DIR} _texture_3d_vshader)
target_stringify_shader(${DIR} _texture_2d_fshader)
target_stringify_shader(${DIR} _texture_3d_fshader)
target_stringify_shader(${DIR} _buffer_fshader)
target_stringify_shader(${DIR} _billboard_fshader)
target_stringify_shader(${DIR} _billboard_vshader)
target_stringify_shader(${DIR} _heightmap_fshader)
target_stringify_shader(${DIR} _heightmap_vshader)
target_stringify_shader(${DIR} _terrain_fshader)
target_stringify_shader(${DIR} _terrain_vshader)
target_stringify_shader(${DIR} _terrain_shadow_fshader)
target_stringify_shader(${DIR} _terrain_shadow_vshader)
target_stringify_shader(${DIR} _water_fshader)
target_stringify_shader(${DIR} _water_vshader)
target_stringify_shader(${DIR} _blur_fshader)
target_stringify_shader(${DIR} _blur_vshader)
target_stringify_shader(${DIR} _bloom_fshader)
target_stringify_shader(${DIR} _bloom_vshader)
target_stringify_shader(${DIR} _gBuffer_fshader)
target_stringify_shader(${DIR} _pass_vshader)
target_stringify_shader(${DIR} _shadow_fshader)
target_stringify_shader(${DIR} _shadow_vshader)