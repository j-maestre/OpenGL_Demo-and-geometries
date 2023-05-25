//
// main.cc
// Ivan Sancho, Escuela Superior de Arte y Tecnologia
// Programacion Grafica
// ESAT 2022-2023
//

#include <stdio.h>
#include <math.h>
#include "ESAT/window.h"
#include "ESAT/input.h"
#include "ESAT/draw.h"
#include "ESAT/time.h"

#include "EDK3/geometry.h"
#include "EDK3/camera.h"
#include "camera_custom.h"
#include "EDK3/drawable.h"
#include "EDK3/matdiffuse.h"
#include "EDK3/matdiffusetexture.h"
#include "EDK3/texture.h"
#include "Lights.h"
#include "EDK3/dev/gpumanager.h"
#include "geometry_custom_terrain.h"
#include "geometry_custom_sphere.h"
#include "material_custom.h"
#include "joystick.h"
#include "oxml/Mat4.h"
#include "oxml/Vec3.h"
#include "oxml/Vec4.h"
#include "cubemap_material.h"
#include "custom_gpu_cubemap.h"
#include "geometry_custom_cube.h"

#include "ESAT_extra/imgui.h"
#include "EDK3/dev/opengl.h"
#include "EDK3/dev/glfw3.h"


//Unnamed struct and it's unique instance:
struct {
  EDK3::ref_ptr<EDK3::CameraCustom> camera;
  EDK3::ref_ptr<EDK3::Node> root;
} GameState;

std::vector<std::string> cube_map_tex = {
  "./test/skybox/right.jpg",
  "./test/skybox/left.jpg",
  "./test/skybox/top.jpg",
  "./test/skybox/bottom.jpg",
  "./test/skybox/front.jpg",
  "./test/skybox/back.jpg",
};

const int kWindowWidth = 1024;
const int kWindowHeight = 768;

const int kTerrainWidth = 256;
const int kTerrainHeight = 256;

bool followBoat_ = false;
ESAT::Vec3 boatPos = {0.0f, 0.773f, 0.0f};
ESAT::Vec3 faroPos = {41.8f, -27.127f, 43.2f};
EDK3::ref_ptr<DirLight> dirLight;
EDK3::ref_ptr<PointLight> pointLight;
EDK3::ref_ptr<SpotLight> spotLight;
EDK3::ref_ptr<Joystick> joystick;

bool joystickAdded = false;
int conected = -1;
const float *axes;

bool rotate_spot_light = true;
float rotation_speed = 5.0f;

float sphere_pivot[3];
float sphere_pos[3] = {0.0f, 0.0f, 0.0f};

char controller_type;



void MoveBoat(double dt){

  ESAT::Vec3 direction = GameState.camera->direction();
  float speed = GameState.camera->speed() * 0.5f;

  float pos[] = {boatPos.x, boatPos.y, boatPos.z};  

  //if(ESAT::MouseButtonPressed(1)){


    if(ESAT::IsKeyPressed('W')){
      pos[0] += (direction.x * speed * dt);
      pos[2] += (direction.z * speed * dt);

      //this->set_position(pos);
    }
    if(ESAT::IsKeyPressed('S')){
      pos[0] -= (direction.x * speed * dt);
      pos[2] -= (direction.z * speed * dt);
        //this->set_position(pos);
    }

    boatPos.x = pos[0];
    boatPos.z = pos[2];
  
  //}
}

void ControllerSetUp(){
  
  conected = glfwJoystickPresent(0);
  //  printf("Joystick %d\n",conected);

  if(conected){
    int axesCount;
    axes = glfwGetJoystickAxes(0, &axesCount);
  }

}


void InitScene() {
  //Allocating root node:
  EDK3::Node* root = GameState.root.alloc();

  // Enable transparences
  EDK3::dev::GPUManager::BlendParam src = EDK3::dev::GPUManager::BlendParam::kBlendParam_SourceAlpha;
  EDK3::dev::GPUManager::BlendParam dst = EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusSourceAlpha;
  EDK3::dev::GPUManager::BlendOp op = EDK3::dev::GPUManager::BlendOp::kBlendOp_Add;
  float blenWhite[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  float blenBlack[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  EDK3::dev::GPUManager::Instance()->enableBlend(src, dst, op, blenBlack);

  joystick.alloc();

  // Create terrain
  EDK3::ref_ptr<EDK3::TerrainCustom> terrain;
  terrain.alloc();
  terrain->init(kTerrainWidth, kTerrainHeight, 1.2f);

  // Create water
  EDK3::ref_ptr<EDK3::TerrainCustom> water;
  water.alloc();
  water->init(kTerrainWidth,kTerrainHeight, 0.2f);

  // Create boat
  EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> boat;
  //EDK3::LoadObj("./test/boat/boat.obj", &boat, nullptr);
  EDK3::LoadObj("./test/boat/boatJosefa.obj", &boat, nullptr);
  if(!boat.get()){
    printf("No hay BOAT OBJ!!!\n");
  }
  
  // Create faro
  EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> faro;
  EDK3::LoadObj("./test/faro/faro.obj", &faro, nullptr);
  if(!faro.get()){
    printf("No hay FARO OBJ!!!\n");
  }

  // Create sphere
  EDK3::ref_ptr<EDK3::SphereCustom> sphere;
  sphere.alloc();
  sphere->init(3.0f);

  // Create cube map
  EDK3::ref_ptr<CustomGPUCubeMap> cube_map;
  cube_map.alloc();
  cube_map->init(cube_map_tex);

  EDK3::ref_ptr<EDK3::CubeCustom> cube_geo;
  cube_geo.alloc();
  cube_geo->init(1.0f, false, true);


  // Create material

  // Terrain
  EDK3::ref_ptr<EDK3::MaterialCustom> mat;
  mat.alloc();
  mat->init("./test/terrain_vertex.shader","./test/terrain_fragment.shader");

  // Watter
  EDK3::ref_ptr<EDK3::MaterialCustom> mat_water;
  mat_water.alloc();
  mat_water->init("./test/water_vertex.shader","./test/water_fragment.shader");

  // Boat
  EDK3::ref_ptr<EDK3::MatDiffuseTexture> mat_boat;
  mat_boat.alloc();
  //mat_boat->init("./test/boat/boat_vertex.shader", "./test/boat/boat_fragment.shader");

  // Faro
  EDK3::ref_ptr<EDK3::MatDiffuse> mat_faro;
  mat_faro.alloc();

  // Sphere
  EDK3::ref_ptr<EDK3::MaterialCustom> mat_sphere;
  mat_sphere.alloc();
  mat_sphere->init("./test/sphere_vertex.shader","./test/sphere_fragment.shader");

  // Cube Map
  EDK3::ref_ptr<EDK3::MaterialCubeMap> mat_custom;
  mat_custom.alloc();
  mat_custom->init("./test/cubemap.vs", "./test/cubemap.fs");


  // Create texture
  EDK3::ref_ptr<EDK3::Texture> t_texture;
  EDK3::Texture::Load("./test/T_EDK_Logo.png", &t_texture);

  EDK3::ref_ptr<EDK3::Texture> w_texture;
  EDK3::Texture::Load("./test/T_EDK_Logo.png", &w_texture);
  
  EDK3::ref_ptr<EDK3::Texture> s_texture;
  EDK3::Texture::Load("./test/T_Chopper.jpg", &s_texture);

  EDK3::ref_ptr<EDK3::Texture> b_texture;
  //EDK3::Texture::Load("./test/boat/boat_img.jpg", &b_texture);
  EDK3::Texture::Load("./test/boat/barcoJosefaDiffuse.png", &b_texture);
  if(!b_texture){
    printf("No hay textura del boat!!!\n");
  }
  
  EDK3::ref_ptr<EDK3::Texture> f_texture;
  //EDK3::Texture::Load("./test/boat/boat_img.jpg", &b_texture);
  EDK3::Texture::Load("./test/T_EDK_Logo.png", &f_texture);
  if(!f_texture){
    printf("No hay textura del faro!!!\n");
  }

  // Material custom settings

  // Terrain
  float terrain_color[4] = {0.0f, 1.0f, 0.0f, 1.0f};
  EDK3::ref_ptr<EDK3::MaterialCustom::MaterialCustomSettings> mat_settings;
  mat_settings.alloc();
  mat_settings->set_diffuse_texture(t_texture);
  mat_settings->set_specular_texture(t_texture);
  mat_settings->set_color(terrain_color);

  // Water
  float water_color[4] = {0.0f, 0.0f, 1.0f, 1.0f};
  EDK3::ref_ptr<EDK3::MaterialCustom::MaterialCustomSettings> water_mat_settings;
  water_mat_settings.alloc();
  water_mat_settings->set_diffuse_texture(w_texture);
  water_mat_settings->set_specular_texture(w_texture);
  water_mat_settings->set_color(water_color);
  water_mat_settings->setResolution(kWindowWidth,kWindowHeight);

  // Sphere
  float sphere_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  EDK3::ref_ptr<EDK3::MaterialCustom::MaterialCustomSettings> sphere_mat_settings;
  sphere_mat_settings.alloc();
  sphere_mat_settings->set_diffuse_texture(s_texture);
  sphere_mat_settings->set_specular_texture(s_texture);
  sphere_mat_settings->set_color(sphere_color);


  // Boat
  float boat_color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
  EDK3::ref_ptr<EDK3::MatDiffuseTexture::Settings> mat_sett_boat;
  mat_sett_boat.alloc();
  mat_sett_boat->set_texture(b_texture.get());
  //mat_sett_boat->set_color(boat_color);
  
  // Faro
  float faro_color[4] = {0.5f, 0.5f, 0.5f, 1.0f};
  EDK3::ref_ptr<EDK3::MatDiffuse::Settings> mat_sett_faro;
  mat_sett_faro.alloc();
  mat_sett_faro->set_color(faro_color);

  // Cube Map
  EDK3::ref_ptr<EDK3::MaterialCubeMap::Settings> mat_custom_settings;
  mat_custom_settings.alloc();
  mat_custom_settings->set_cube_map(cube_map);


  // Lights
  dirLight.alloc();
  dirLight->active = 1;
  dirLight->dir[0] = 1.0f;
  dirLight->dir[1] = 0.6f;
  dirLight->dir[2] = 0.5f;
  dirLight->diffuse_color[0] = 1.0f;
  dirLight->diffuse_color[1] = 1.0f;
  dirLight->diffuse_color[2] = 1.0f;
  dirLight->specular_color[0] = 1.0f;
  dirLight->specular_color[1] = 1.0f;
  dirLight->specular_color[2] = 1.0f;
  dirLight->specular_strength = 1.0f;
  dirLight->specular_shininess = 1.0f;
  
  pointLight.alloc();
  pointLight->active = 1;
  pointLight->diffuse_color[0] = 1.0f;
  pointLight->diffuse_color[1] = 0.0f;
  pointLight->diffuse_color[2] = 0.0f;
  pointLight->pos[0] = boatPos.x;
  pointLight->pos[1] = boatPos.y +2.0f;
  pointLight->pos[2] = boatPos.z;
  pointLight->specular_color[0] = 1.0f;
  pointLight->specular_color[1] = 1.0f;
  pointLight->specular_color[2] = 1.0f;
  pointLight->specular_strength = 0.003f;
  pointLight->specular_shininess = 32.0f;
  pointLight->constant_att = 2.37f;
  pointLight->linear_att = -0.52f;
  pointLight->quadratic_att = 0.045f;

  spotLight.alloc();
  spotLight->active = 1;
  /*spotLight->pos[0] = faroPos.x;
  spotLight->pos[1] = faroPos.y + 10.0f;
  spotLight->pos[2] = faroPos.z;*/
  spotLight->pos[0] = -100.0f;
  spotLight->pos[1] = 42.03f;
  spotLight->pos[2] = 3.42f;
  spotLight->dir[0] = 0.71f;
  spotLight->dir[1] = -0.53f;
  spotLight->dir[2] = -0.59f;
  spotLight->cutt_off = 0.3f;
  spotLight->outer_cut_off = 1.0f;
  spotLight->diffuse_color[0] = 1.0f;
  spotLight->diffuse_color[1] = 1.0f;
  spotLight->diffuse_color[2] = 1.0f;
  spotLight->specular_color[2] = 1.0f;
  spotLight->specular_color[2] = 1.0f;
  spotLight->specular_color[2] = 1.0f;
  spotLight->specular_strength = 0.003f;
  spotLight->specular_shininess = 32.0f;
  spotLight->constant_att = 1.0f;
  spotLight->linear_att = 0.007f;
  spotLight->quadratic_att = 0.0002f;


  mat_settings->set_dir_light(dirLight);
  water_mat_settings->set_dir_light(dirLight);
  sphere_mat_settings->set_dir_light(dirLight);

  mat_settings->set_point_light(pointLight);
  water_mat_settings->set_point_light(pointLight);
  sphere_mat_settings->set_point_light(pointLight);

  mat_settings->set_spot_light(spotLight);
  water_mat_settings->set_spot_light(spotLight);
  sphere_mat_settings->set_spot_light(spotLight);

  //mat_sett_boat->set_dir_light(dirLight);

  // Drawable
  EDK3::ref_ptr<EDK3::Drawable> node;

  // Terrain
  node.alloc();
  node->set_geometry(terrain.get());
  node->set_material(mat.get());
  node->set_material_settings(mat_settings.get());
  node->set_position(-1.0f, 0.0f, -1.0f);
  root->addChild(node.get());  


  
  // Boat
  EDK3::ref_ptr<EDK3::Drawable> drawable;
  EDK3::ref_ptr<EDK3::Node> boat_node;
  
  boat_node.alloc();
  for(int i = 0; i < boat.size(); i++){
    drawable.alloc();
    drawable->set_geometry(boat[i].get());
    drawable->set_material(mat_boat.get());
    drawable->set_material_settings(mat_sett_boat.get());
    drawable->set_position(boatPos.x, boatPos.y, boatPos.z);
    boat_node->addChild(drawable.get());
  }
  root->addChild(boat_node.get());
  
  // Faro
  EDK3::ref_ptr<EDK3::Node> faro_node;
  
  faro_node.alloc();
  for(int i = 0; i < faro.size(); i++){
    drawable.alloc();
    drawable->set_geometry(faro[i].get());
    drawable->set_material(mat_faro.get());
    drawable->set_material_settings(mat_sett_faro.get());
    drawable->set_position(faroPos.x, faroPos.y, faroPos.z);
    faro_node->addChild(drawable.get());
  }
  root->addChild(faro_node.get());

  // Sphere
  EDK3::ref_ptr<EDK3::Drawable> sphere_drawable;
  EDK3::ref_ptr<EDK3::Node> sphere_node;
  sphere_pos[0] = 9.0f;
  sphere_drawable.alloc();
  sphere_drawable->set_geometry(sphere.get());
  sphere_drawable->set_material(mat_sphere.get());
  sphere_drawable->set_material_settings(sphere_mat_settings.get());
  sphere_drawable->set_position(sphere_pos[0], sphere_pos[1], sphere_pos[2]);

  // Sphere pivot
  sphere_pivot[0] = -100.0f;
  sphere_pivot[1] = 40.73f;
  sphere_pivot[2] = 3.13f;

  sphere_node.alloc();
  sphere_node->set_position(sphere_pivot[0], sphere_pivot[1], sphere_pivot[2]);
  sphere_node->addChild(sphere_drawable.get());
    
  root->addChild(sphere_node.get());


    EDK3::ref_ptr<EDK3::Drawable> cube;
    cube.alloc();
    cube->set_geometry(cube_geo.get());
    cube->set_position(1.0f, 0.0f, -3.0);
    cube->set_scale(1.0f, 1.0f, 1.0f);
    cube->set_material(mat_custom.get());
    cube->set_material_settings(mat_custom_settings.get());
    cube->set_HPR(0.0f, 0.0f, 0.0f);
    root->addChild(cube.get());


  // Water
  node.alloc();
  node->set_geometry(water.get());
  node->set_material(mat_water.get());
  node->set_material_settings(water_mat_settings.get());
  node->set_position(-1.0f,0.0f,-1.0f);
  root->addChild(node.get()); 


  //root->addChild(root_2.get());
  //Allocating and initializing the camera:
  GameState.camera.alloc();
  //float pos[] = { 120.0f / 2.0f, 140.0f / 2.0f, 120.0f / 2.0f };
  //float view[] = { -120.0f, -140.0f, -120.0f };

  float pos[] = { 0.0f, 4.0f, 40.0f };
  float view[] = { 0.0f, 0.0f, -6.0f };
  GameState.camera->set_position(pos);
  
  const float target[] = {boatPos.x,boatPos.y+5.0f,boatPos.z};
  //GameState.camera->set_view_target(target);
  GameState.camera->set_view_direction(view);
  GameState.camera->setEnabled(true);
  GameState.camera->setSpeed(0.02f);
  GameState.camera->setSensitibity(1.0f);
  GameState.camera->initViewTarget(kWindowWidth,kWindowHeight);
  //GameState.camera->setFollowObject(boatPos);

  GameState.camera->setupPerspective(70.0f, 8.0f / 6.0f, 1.0f, 1500.0f);
  mat_settings->set_camera_position(GameState.camera->position());
  water_mat_settings->set_camera_position(GameState.camera->position());
  sphere_mat_settings->set_camera_position(GameState.camera->position());
  
  EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

void SetLightToBolinga(){
    
    EDK3::ref_ptr<EDK3::Node> sphere_center = GameState.root->child(3);
    EDK3::ref_ptr<EDK3::Node> sphere = sphere_center->child(0);
    sphere->set_position(sphere_pos[0],sphere_pos[1],sphere_pos[2]);

    // Pivot values
    const float *pivot_escale = sphere_center->scale();
    const float *pivot_rotation = sphere_center->rotation_xyz();
    const float *pivot_position = sphere_center->position();
    oxml::Vec3 pi_scale = oxml::Vec3(pivot_escale[0],pivot_escale[1],pivot_escale[2]);
    oxml::Vec3 pi_rotation = oxml::Vec3(pivot_rotation[0],pivot_rotation[1],pivot_rotation[2]);
    oxml::Vec3 pi_position = oxml::Vec3(pivot_position[0],pivot_position[1],pivot_position[2]);

    // Sphere values
    const float *sphere_scale = sphere->scale();
    const float *sphere_rotation = sphere->rotation_xyz();
    const float *sphere_position = sphere->position();
    oxml::Vec3 sph_scale = oxml::Vec3(sphere_scale[0],sphere_scale[1],sphere_scale[2]);
    oxml::Vec3 sph_rotation = oxml::Vec3(sphere_rotation[0],sphere_rotation[1],sphere_rotation[2]);
    oxml::Vec3 sph_position = oxml::Vec3(sphere_position[0],sphere_position[1],sphere_position[2]);

    // Pivot model matrix
    oxml::Mat4 pivot_identity = oxml::Mat4::Identity();
    pivot_identity = pivot_identity.Multiply(oxml::Mat4::Scale(pi_scale));
    pivot_identity = pivot_identity.Multiply(oxml::Mat4::RotateX(pi_rotation[0]));
    pivot_identity = pivot_identity.Multiply(oxml::Mat4::RotateY(pi_rotation[1]));
    pivot_identity = pivot_identity.Multiply(oxml::Mat4::RotateZ(pi_rotation[2]));
    pivot_identity = pivot_identity.Multiply(oxml::Mat4::Translate(pi_position));
    
    // Sphere model matrix
    oxml::Mat4 sphere_identity = oxml::Mat4::Identity();
    sphere_identity = sphere_identity.Multiply(oxml::Mat4::Scale(sph_scale));
    sphere_identity = sphere_identity.Multiply(oxml::Mat4::RotateX(sph_rotation[0]));
    sphere_identity = sphere_identity.Multiply(oxml::Mat4::RotateY(sph_rotation[1]));
    sphere_identity = sphere_identity.Multiply(oxml::Mat4::RotateZ(sph_rotation[2]));
    sphere_identity = sphere_identity.Multiply(oxml::Mat4::Translate(sph_position));

    // Sphere model matrix in world position
    oxml::Mat4 sphere_world_model = pivot_identity.Multiply(sphere_identity);
    oxml::Vec4 sphere_worl_pos = sphere_world_model.Transpose() * oxml::Vec4(0.0f, 0.0f, 0.0f, 1.0f);

    spotLight->pos[0] = sphere_worl_pos[0];
    spotLight->pos[1] = sphere_worl_pos[1];
    spotLight->pos[2] = sphere_worl_pos[2];

    //spotLight->dir[0] = pivot_rotation[0];
    spotLight->dir[1] = sinf(pivot_rotation[1]);
    //spotLight->dir[2] = pivot_rotation[2];

    // padre * hijo y me da la matrix model del hijo en mundo, la multiplico por vec4(0,0,0,1) y me da la posicion del hijo en mundo

}

void UpdateFn(double dt) {
  GameState.camera->set_clear_color(1.0f, 1.0f, 0.75f, 1.0f);
  GameState.camera->update(dt, kWindowWidth, kWindowHeight);
  //GameState.camera->set_clear_color(0.94f, 1.0f, 0.94f, 1.0f);

  //ControllerSetUp();
  if(joystickAdded && joystick->isConected()){
    if(controller_type == 'P'){
      joystick->getInputFromPS4();
    }

    if(controller_type == 'X'){
      joystick->getInputFromXBox();
    }
  }

  if(followBoat_){
    // Actualizamos la posicion del barco
    MoveBoat(dt);

    // Le pasamos la nueva posicion a la camara
    GameState.camera->setFollowObject(boatPos);
    const float target[] = {boatPos.x,boatPos.y+5.0f,boatPos.z};
    GameState.camera->set_view_target(target);

  }
  
  if(rotate_spot_light){
    spotLight->dir[0] = cosf(ESAT::Time() * 0.0001f * rotation_speed);
    spotLight->dir[2] = sinf(ESAT::Time() * 0.0001f * rotation_speed);
  }

  EDK3::ref_ptr<EDK3::Node> sphere_center = GameState.root->child(3);
  //sphere_pivot->set_position(spotLight->pos[0],spotLight->pos[1],spotLight->pos[2]);
  sphere_center->set_position(sphere_pivot[0],sphere_pivot[1],sphere_pivot[2]);
  sphere_center->set_rotation_y(ESAT::Time() * 0.05f);

  SetLightToBolinga();


  EDK3::ref_ptr<EDK3::Node> boat = GameState.root->child(1);
  //boat->set_scale(0.01f, 0.01f, 0.01f);
  boat->set_scale(1.0f, 1.0f, 1.0f);
  //boat->set_rotation_z(90.0f);
  //boat->set_rotation_z(0.0f);
  //boat->set_rotation_x(-90.0f);
  boat->set_position(boatPos.x, boatPos.y, boatPos.z);

  EDK3::ref_ptr<EDK3::Node> faro = GameState.root->child(2);
  faro->set_position(faroPos.x, faroPos.y, faroPos.z);

  //boat->set_rotation_xyz(ESAT::Time() * 0.005f, ESAT::Time() * 0.005f, ESAT::Time() * 0.005f);
  //boat->set_scale(0.2f, 0.2f, 0.2f);
}

void RenderFn() {
  //For every frame... determine what's visible:
  GameState.camera->doCull(GameState.root.get());

  //Rendering the scene:
  EDK3::dev::GPUManager::CheckGLError("begin Render-->");
  GameState.camera->doRender();
  EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

void ImGuiFn(double dt) {
  ImGui::Begin("FPS Window");
  ImGui::Text("FPS: %0.1f", 1000.0 / dt);
  ImGui::Text("Delta time: %0.3f ms", dt);
  if(ImGui::CollapsingHeader("Camera")){
    ImGui::Text("View target");
    ESAT::Vec3 view_dir = GameState.camera->direction(); 
    const float* view = GameState.camera->target(); 
    ImGui::Text("X: %f",view[0]);
    ImGui::Text("Y: %f",view[1]);
    ImGui::Text("Z: %f",view[2]);
    
    ImGui::Text("View direction");
    ImGui::DragFloat("X: ",&view_dir.x,0.005f,-100.0f,100.0f, "%f");
    ImGui::DragFloat("Y: ",&view_dir.y,0.005f,-100.0f,100.0f, "%f");
    ImGui::DragFloat("Z: ",&view_dir.z,0.005f,-100.0f,100.0f, "%f");

    const float* pos = GameState.camera->position();
    ImGui::Text("Position");
    ImGui::Text("X: %f",pos[0]);
    ImGui::Text("Y: %f",pos[1]);
    ImGui::Text("Z: %f",pos[2]);

    ImGui::Text("Speed");
    float movementSpeed = GameState.camera->speed();
    ImGui::DragFloat("Movement", &movementSpeed, 0.01f, 0.0f,2.0f, "%f");
    GameState.camera->setSpeed(movementSpeed);
    float sensitivity = GameState.camera->sensitivity();
    ImGui::DragFloat("Sensitivity", &sensitivity, 0.01f, 0.0f,4.0f, "%f");
    GameState.camera->setSensitibity(sensitivity);

  }

  ImGui::Checkbox("Follow Boat",&followBoat_);
  GameState.camera->following_ = followBoat_;

  if(ImGui::CollapsingHeader("Boat")){
    ImGui::Text("Position");
    ImGui::DragFloat("Boat X: ",&boatPos.x, 0.001f, -1000.0f,1000.0f, "%f");
    ImGui::DragFloat("Boat Y: ",&boatPos.y, 0.001f, -1000.0f,1000.0f, "%f");
    ImGui::DragFloat("Boat Z: ",&boatPos.z, 0.001f, -1000.0f,1000.0f, "%f");
    
  }
  
  if(ImGui::CollapsingHeader("Faro")){
    ImGui::Text("Position");
    ImGui::DragFloat("Faro X: ",&faroPos.x, 0.1f, -1000.0f,1000.0f, "%f");
    ImGui::DragFloat("Faro Y: ",&faroPos.y, 0.1f, -1000.0f,1000.0f, "%f");
    ImGui::DragFloat("Faro Z: ",&faroPos.z, 0.1f, -1000.0f,1000.0f, "%f");
    
    if(ImGui::CollapsingHeader("Bolinga")){
      ImGui::DragFloat3("Pivot",sphere_pivot,0.1f,-100.0f,100.0f);
      ImGui::DragFloat3("Sphere",sphere_pos,0.1f,-100.0f,100.0f);
    }
  }

  if(ImGui::CollapsingHeader("Lights")){

    if(ImGui::CollapsingHeader("Directional")){
      ImGui::DragFloat("X: ",&dirLight->dir[0], 0.001f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Y: ",&dirLight->dir[1], 0.001f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Z: ",&dirLight->dir[2], 0.001f, -100.0f,100.0f, "%f");
    }

    if(ImGui::CollapsingHeader("Point")){
      ImGui::Text("Point Boat");
      ImGui::DragFloat("Position X: ",&pointLight->pos[0], 0.01f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Position Y: ",&pointLight->pos[1], 0.01f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Position Z: ",&pointLight->pos[2], 0.01f, -100.0f,100.0f, "%f");

      ImGui::DragFloat("Constant ",&pointLight->constant_att, 0.005f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Linear ",&pointLight->linear_att, 0.005f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Quadratic ",&pointLight->quadratic_att, 0.005f, -100.0f,100.0f, "%f");
      
      ImGui::DragFloat("Specular shininess",&pointLight->specular_shininess, 0.001f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Specular Strenght ",&pointLight->specular_strength, 0.001f, -100.0f,100.0f, "%f");
      if(ImGui::Button("Reset")){
        pointLight->pos[0] = boatPos.x;
        pointLight->pos[1] = boatPos.y +2.0f;
        pointLight->pos[2] = boatPos.z;
        pointLight->specular_strength = 0.8f;
        pointLight->specular_shininess = 32.0f;
        pointLight->constant_att = 1.0f;
        pointLight->linear_att = 0.0014f;
        pointLight->quadratic_att = 0.000007f;
      }
    }
    
    if(ImGui::CollapsingHeader("Spot")){
      ImGui::Text("Spot faro");
      ImGui::DragFloat("Position X: ",&spotLight->pos[0], 0.01f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Position Y: ",&spotLight->pos[1], 0.01f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Position Z: ",&spotLight->pos[2], 0.01f, -100.0f,100.0f, "%f");


      
      ImGui::DragFloat("Direction X: ",&spotLight->dir[0], 0.01f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Direction Y: ",&spotLight->dir[1], 0.01f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Direction Z: ",&spotLight->dir[2], 0.01f, -100.0f,100.0f, "%f");

      ImGui::DragFloat("Cutt off ",&spotLight->cutt_off, 0.005f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Outer Cutt off ",&spotLight->outer_cut_off, 0.005f, -100.0f,100.0f, "%f");
      
      ImGui::DragFloat("Constant ",&spotLight->constant_att, 0.005f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Linear ",&spotLight->linear_att, 0.005f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Quadratic ",&spotLight->quadratic_att, 0.005f, -100.0f,100.0f, "%f");
      
      ImGui::DragFloat("Specular shininess",&spotLight->specular_shininess, 0.001f, -100.0f,100.0f, "%f");
      ImGui::DragFloat("Specular Strenght ",&spotLight->specular_strength, 0.001f, -100.0f,100.0f, "%f");
      if(ImGui::Button("Rotate light")){
        rotate_spot_light = !rotate_spot_light;
      }
      ImGui::DragFloat("Rotation Speed",&rotation_speed, 0.01f,0.0f,10.0f);
      //float *color = spotLight->diffuse_color;
      ImGui::ColorEdit3("Light Color",spotLight->diffuse_color);
      ImGui::Text("R->%f G->%f B->%f A->%f",spotLight->diffuse_color[0],spotLight->diffuse_color[1],spotLight->diffuse_color[2],spotLight->diffuse_color[3]);
      if(ImGui::CollapsingHeader("Distance default values")){
        if(ImGui::Button("Distance 7")){
          spotLight->constant_att = 1.0f;
          spotLight->linear_att = 0.7f;
          spotLight->quadratic_att = 1.8f;
        }
        if(ImGui::Button("Distance 13")){
          spotLight->constant_att = 1.0f;
          spotLight->linear_att = 0.35f;
          spotLight->quadratic_att = 0.44f;
        }
        if(ImGui::Button("Distance 20")){
          spotLight->constant_att = 1.0f;
          spotLight->linear_att = 0.22f;
          spotLight->quadratic_att = 0.20f;
        }
        if(ImGui::Button("Distance 32")){
          spotLight->constant_att = 1.0f;
          spotLight->linear_att = 0.14f;
          spotLight->quadratic_att = 0.07f;
        }
        if(ImGui::Button("Distance 50")){
          spotLight->constant_att = 1.0f;
          spotLight->linear_att = 0.09f;
          spotLight->quadratic_att = 0.032f;
        }
        if(ImGui::Button("Distance 65")){
          spotLight->constant_att = 1.0f;
          spotLight->linear_att = 0.07f;
          spotLight->quadratic_att = 0.017f;
        }
        if(ImGui::Button("Distance 100")){
          spotLight->constant_att = 1.0f;
          spotLight->linear_att = 0.045f;
          spotLight->quadratic_att = 0.0075f;
        }
        if(ImGui::Button("Distance 160")){
          spotLight->constant_att = 1.0f;
          spotLight->linear_att = 0.027f;
          spotLight->quadratic_att = 0.0028f;
        }
        if(ImGui::Button("Distance 200")){
          spotLight->constant_att = 1.0f;
          spotLight->linear_att = 0.022f;
          spotLight->quadratic_att = 0.0019f;
        }
        if(ImGui::Button("Distance 325")){
          spotLight->constant_att = 1.0f;
          spotLight->linear_att = 0.014f;
          spotLight->quadratic_att = 0.0007f;
        }
        if(ImGui::Button("Distance 600")){
          spotLight->constant_att = 1.0f;
          spotLight->linear_att = 0.007f;
          spotLight->quadratic_att = 0.0002f;
        }
        if(ImGui::Button("Distance 3250")){
          spotLight->constant_att = 1.0f;
          spotLight->linear_att = 0.0014f;
          spotLight->quadratic_att = 0.000007f;
        }
      }
      if(ImGui::Button("Reset")){
        spotLight->pos[0] = -100.0f;
        spotLight->pos[1] = 10.53f;
        spotLight->pos[2] = 8.23f;
        spotLight->dir[0] = 0.71f;
        spotLight->dir[1] = -0.53f;
        spotLight->dir[2] = -0.59f;
        spotLight->cutt_off = 0.3f;
        spotLight->outer_cut_off = 1.0f;
        spotLight->diffuse_color[0] = 1.0f;
        spotLight->diffuse_color[1] = 1.0f;
        spotLight->diffuse_color[2] = 1.0f;
        spotLight->specular_color[2] = 1.0f;
        spotLight->specular_color[2] = 1.0f;
        spotLight->specular_color[2] = 1.0f;
        spotLight->specular_strength = 0.003f;
        spotLight->specular_shininess = 32.0f;
        spotLight->constant_att = 1.0f;
        spotLight->linear_att = 0.007f;
        spotLight->quadratic_att = 0.0002f;
      }

      
    }

  }

  // Joystick
  if(!joystickAdded){
    if(ImGui::Button("Add PS4 Controller")){
      joystick->conect();
      controller_type = 'P';
      if(joystick->isConected()){
        joystickAdded = true;
        GameState.camera->joysticConected_ = true;
        GameState.camera->joystick_ = joystick;
      }
    }
    if(ImGui::Button("Add XBox Controller")){
      joystick->conect();
      controller_type = 'X';
      if(joystick->isConected()){
        joystickAdded = true;
        GameState.camera->joysticConected_ = true;
        GameState.camera->joystick_ = joystick;
      }
    }
  }

  if(joystick->isConected()){
    if(ImGui::CollapsingHeader("Joystick")){
      ImGui::Text("Left X Axis %f",joystick->leftAxis_[0]);
      ImGui::Text("Left Y Axis %f",joystick->leftAxis_[1]);
      ImGui::Text("Right X Axis %f",joystick->rightAxis_[0]);
      ImGui::Text("Right Y Axis %f",joystick->rightAxis_[1]);
      ImGui::Text("Left Trigger/L2 %f",joystick->l2Trigger_);
      ImGui::Text("Right Trigger/R2  %f",joystick->r2Trigger_);

      ImGui::DragFloat("Right Dead Zone",&joystick->rightDeadZone_,0.001f,-1.0f,1.0f);
      ImGui::DragFloat("Left Dead Zone",&joystick->leftDeadZone_,0.001f,-1.0f,1.0f);

      ImGui::DragFloat("Movement Speed", &GameState.camera->joystickMovementSpeed_,0.005f,0.005f,1.0f);
      ImGui::DragFloat("Sensitivity", &GameState.camera->joystickSensitivity_,0.01f,0.1f,20.0f);
      ImGui::DragFloat("Turbo", &GameState.camera->turboSpeed_,0.01f,0.01f,1.0f);
    }
  }


  ImGui::End();
  ImGui::Render();
}

int ESAT::main(int argc, char** argv) {
  ESAT::WindowInit(kWindowWidth, kWindowHeight);
  InitScene();
  double dt = 0.0;
  double last_time = ESAT::Time();
  while (!ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape) && 
         ESAT::WindowIsOpened()) {
    UpdateFn(dt);
    RenderFn();
    dt = ESAT::Time() - last_time;
    last_time = ESAT::Time();
    ImGuiFn(dt);
    ESAT::WindowFrame();
  }
  return 0;
}
