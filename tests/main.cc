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
#include "EDK3/drawable.h"
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
  EDK3::ref_ptr<EDK3::Camera> camera;
  EDK3::ref_ptr<EDK3::Node> root;
} GameState;

const int kWindowWidth = 1024;
const int kWindowHeight = 768;

const int kTerrainWidth = 256;
const int kTerrainHeight = 256;


void Oleaje(EDK3::ref_ptr<EDK3::TerrainCustom> terrain){

}

void InitScene() {
  //Allocating root node:
  EDK3::Node* root = GameState.root.alloc();
  
  // Create terrain
  EDK3::ref_ptr<EDK3::TerrainCustom> terrain;
  terrain.alloc();
  terrain->init(kTerrainWidth, kTerrainHeight);

  EDK3::ref_ptr<EDK3::TerrainCustom> water;
  water.alloc();
  water->init(kTerrainWidth,kTerrainHeight, 0.2f);


  // Create material
  EDK3::ref_ptr<EDK3::MaterialCustom> mat;
  mat.alloc();
  mat->init("./test/terrain_vertex.shader","./test/terrain_fragment.shader");

  EDK3::ref_ptr<EDK3::MaterialCustom> mat_water;
  mat_water.alloc();
  mat_water->init("./test/water_vertex.shader","./test/water_fragment.shader");


  // Create texture
  EDK3::ref_ptr<EDK3::Texture> t_texture;
  EDK3::Texture::Load("./test/T_EDK_Logo.png", &t_texture);

  EDK3::ref_ptr<EDK3::Texture> w_texture;
  EDK3::Texture::Load("./test/T_EDK_Logo.png", &w_texture);

  // Material custom settings

  // Terrain
  EDK3::ref_ptr<EDK3::MaterialCustom::MaterialCustomSettings> mat_settings;
  mat_settings.alloc();
  mat_settings->set_diffuse_texture(t_texture);
  mat_settings->set_specular_texture(t_texture);

  // Water

  float color[4] = {0.0f, 0.0f, 1.0f, 1.0f};
  EDK3::ref_ptr<EDK3::MaterialCustom::MaterialCustomSettings> water_mat_settings;
  water_mat_settings.alloc();
  water_mat_settings->set_diffuse_texture(w_texture);
  water_mat_settings->set_specular_texture(w_texture);
  water_mat_settings->set_color(color);


  // Lights
  EDK3::ref_ptr<DirLight> dirLight;
  dirLight.alloc();
  dirLight->active = 1;
  dirLight->dir[0] = 0.0001f;
  dirLight->dir[1] = 1.0f;
  dirLight->dir[2] = 0.0001f;
  dirLight->diffuse_color[0] = 0.0f;
  dirLight->diffuse_color[1] = 0.6f;
  dirLight->diffuse_color[2] = 0.0f;
  dirLight->specular_color[0] = 1.0f;
  dirLight->specular_color[1] = 1.0f;
  dirLight->specular_color[2] = 1.0f;
  dirLight->specular_strength = 1.0f;
  dirLight->specular_shininess = 1.0f;
  mat_settings->set_dir_light(dirLight);
  water_mat_settings->set_dir_light(dirLight);

  // Drawable
  EDK3::ref_ptr<EDK3::Drawable> node;

  // Terrain
  node.alloc();
  node->set_geometry(terrain.get());
  node->set_material(mat.get());
  node->set_material_settings(mat_settings.get());
  node->set_position(-1.0f, 0.0f, -1.0f);
  root->addChild(node.get());  

  // Water
  node.alloc();
  node->set_geometry(water.get());
  node->set_material(mat_water.get());
  node->set_material_settings(water_mat_settings.get());
  node->set_position(-1.0f,0.0f,-1.0f);
  root->addChild(node.get()); 

  //Allocating and initializing the camera:
  GameState.camera.alloc();
  float pos[] = { 120.0f / 2.0f, 140.0f / 2.0f, 120.0f / 2.0f };
  float view[] = { -120.0f, -140.0f, -120.0f };
  GameState.camera->set_position(pos);
  GameState.camera->set_view_direction(view);
  GameState.camera->setupPerspective(70.0f, 8.0f / 6.0f, 1.0f, 1500.0f);
  
  mat_settings->set_camera_position(GameState.camera->position());
  water_mat_settings->set_camera_position(GameState.camera->position());
  
  EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

void UpdateFn() {
  GameState.camera->set_clear_color(0.94f, 1.0f, 0.94f, 1.0f);
}

void RenderFn() {
  //For every frame... determine what's visible:
  GameState.camera->doCull(GameState.root.get());

  //dynamic_cast<EDK3::TerrainCustom>(GameState.root->child(0));
  //Oleaje( GameState.root->child(1));

  //Rendering the scene:
  EDK3::dev::GPUManager::CheckGLError("begin Render-->");
  GameState.camera->doRender();
  EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

void ImGuiFn(double dt) {
  ImGui::Begin("FPS Window");
  ImGui::Text("FPS: %0.1f", 1000.0 / dt);
  ImGui::Text("Delta time: %0.3f ms", dt);
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
    UpdateFn();
    RenderFn();
    dt = ESAT::Time() - last_time;
    last_time = ESAT::Time();
    ImGuiFn(dt);
    ESAT::WindowFrame();
  }
  return 0;
}
