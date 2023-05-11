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
#include "material_custom.h"

#include "ESAT_extra/imgui.h"
#include "EDK3/dev/opengl.h"


//Unnamed struct and it's unique instance:
struct {
  EDK3::ref_ptr<EDK3::CameraCustom> camera;
  EDK3::ref_ptr<EDK3::Node> root;
} GameState;

const int kWindowWidth = 1024;
const int kWindowHeight = 768;

const int kTerrainWidth = 256;
const int kTerrainHeight = 256;

bool followBoat_ = true;
ESAT::Vec3 boatPos = {0.0f, 0.773f, 0.0f};
EDK3::ref_ptr<DirLight> dirLight;
EDK3::ref_ptr<PointLight> pointLight;




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


  // Create terrain
  EDK3::ref_ptr<EDK3::TerrainCustom> terrain;
  terrain.alloc();
  terrain->init(kTerrainWidth, kTerrainHeight, 0.5f);

  // Create water
  EDK3::ref_ptr<EDK3::TerrainCustom> water;
  water.alloc();
  water->init(kTerrainWidth,kTerrainHeight, 0.2f);

  // Create boat
  EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> boat;
  EDK3::LoadObj("./test/boat/boat.obj", &boat, nullptr);
  if(!boat.get()){
    printf("No hay BOAT OBJ!!!\n");
  }



  // Create material
  EDK3::ref_ptr<EDK3::MaterialCustom> mat;
  mat.alloc();
  mat->init("./test/terrain_vertex.shader","./test/terrain_fragment.shader");

  EDK3::ref_ptr<EDK3::MaterialCustom> mat_water;
  mat_water.alloc();
  mat_water->init("./test/water_vertex.shader","./test/water_fragment.shader");

  EDK3::ref_ptr<EDK3::MatDiffuse> mat_boat;
  mat_boat.alloc();
  //mat_boat->init("./test/boat/boat_vertex.shader", "./test/boat/boat_fragment.shader");




  // Create texture
  EDK3::ref_ptr<EDK3::Texture> t_texture;
  EDK3::Texture::Load("./test/T_EDK_Logo.png", &t_texture);

  EDK3::ref_ptr<EDK3::Texture> w_texture;
  EDK3::Texture::Load("./test/T_EDK_Logo.png", &w_texture);

  EDK3::ref_ptr<EDK3::Texture> b_texture;
  //EDK3::Texture::Load("./test/boat/boat_img.jpg", &b_texture);
  EDK3::Texture::Load("./test/T_EDK_Logo.png", &b_texture);
  if(!b_texture){
    printf("No hay textura del boat!!!\n");
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

  // Boat
  float boat_color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
  EDK3::ref_ptr<EDK3::MatDiffuse::Settings> mat_sett_boat;
  mat_sett_boat.alloc();
  mat_sett_boat->set_color(boat_color);




  // Lights
  dirLight.alloc();
  dirLight->active = 1;
  dirLight->dir[0] = 1.0f;
  dirLight->dir[1] = -0.91f;
  dirLight->dir[2] = 0.0001f;
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

  mat_settings->set_dir_light(dirLight);
  water_mat_settings->set_dir_light(dirLight);
  mat_settings->set_point_light(pointLight);
  water_mat_settings->set_point_light(pointLight);
  //mat_sett_boat->set_dir_light(dirLight);

  // Drawable
  EDK3::ref_ptr<EDK3::Drawable> node;
  EDK3::ref_ptr<EDK3::Node> root_2;
  root_2.alloc();

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
  GameState.camera->set_view_direction(target);
  GameState.camera->setEnabled(true);
  GameState.camera->setSpeed(0.02f);
  GameState.camera->setSensitibity(1.0f);
  GameState.camera->initViewTarget(kWindowWidth,kWindowHeight);
  GameState.camera->setFollowObject(boatPos);

  GameState.camera->setupPerspective(70.0f, 8.0f / 6.0f, 1.0f, 1500.0f);
  mat_settings->set_camera_position(GameState.camera->position());
  water_mat_settings->set_camera_position(GameState.camera->position());
  
  EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

void UpdateFn(double dt) {
  GameState.camera->set_clear_color(1.0f, 1.0f, 0.75f, 1.0f);
  GameState.camera->update(dt, kWindowWidth, kWindowHeight);
  //GameState.camera->set_clear_color(0.94f, 1.0f, 0.94f, 1.0f);

  if(followBoat_){
    // Actualizamos la posicion del barco
    MoveBoat(dt);

    // Le pasamos la nueva posicion a la camara
    GameState.camera->setFollowObject(boatPos);
    const float target[] = {boatPos.x,boatPos.y+5.0f,boatPos.z};
    GameState.camera->set_view_target(target);

  }

  EDK3::ref_ptr<EDK3::Node> boat = GameState.root->child(1);
  boat->set_scale(0.01f, 0.01f, 0.01f);
  boat->set_rotation_z(90.0f);
  boat->set_rotation_x(-90.0f);
  boat->set_position(boatPos.x, boatPos.y, boatPos.z);


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
    ImGui::DragFloat("X: ",&boatPos.x, 0.001f, -100.0f,100.0f, "%f");
    ImGui::DragFloat("Y: ",&boatPos.y, 0.001f, -100.0f,100.0f, "%f");
    ImGui::DragFloat("Z: ",&boatPos.z, 0.001f, -100.0f,100.0f, "%f");
    
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
