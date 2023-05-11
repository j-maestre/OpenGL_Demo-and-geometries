#include "ESAT/math.h"
#include "ESAT/input.h"
#include "camera_custom.h"
#include "oxml/Mathf.h"
#include "oxml/Vec3.h"
#include "oxml/Mat4.h"


namespace EDK3{


CameraCustom::CameraCustom(){
  accum_mouse_offset_ = {0.0f, 0.0f};
  last_mouse_pos_ = {0.0f, 0.0f};
  following_ = false;
}
CameraCustom::CameraCustom(const CameraCustom& ){}
CameraCustom::~CameraCustom(){}
CameraCustom& CameraCustom::operator=(const CameraCustom&){return *this;}


void CameraCustom::initViewTarget(const float window_width, const float window_height){
    //const float *cameraPos = this->position();
    //float normalizedX =  cameraPos[0] / window_width;
    //float normalizedY =  cameraPos[1] / window_height;

    view_dir_ = { window_width * 0.5f, window_height * 0.5f, window_width * 0.5f };
    //view_dir_ = { -0.1f, -0.2f, 0.001f };
    accum_mouse_offset_.x = 0.0001f;
    accum_mouse_offset_.y = 0.0001f;
    //set_view_direction(&view_dir_.x);
}

void CameraCustom::update(const double delta_time, const float window_width, const float window_height){

  bool pressed = ESAT::MouseButtonPressed(0);
  //bool pressed = true;


  // Mouse rotation
  if(ESAT::MouseButtonPressed(1)){

    accum_mouse_offset_.x += (float)ESAT::MousePositionX() - last_mouse_pos_.x;
    accum_mouse_offset_.y += ESAT::MousePositionY() - last_mouse_pos_.y;

    float omega = accum_mouse_offset_.x / window_width * oxml::Mathf::PI * 2.0f * sensitivity_;
    float alpha = accum_mouse_offset_.y / window_height * (oxml::Mathf::PI - oxml::Mathf::PI * 0.5f) * sensitivity_;
    view_dir_ = {cosf(alpha) * cosf(omega),
                -sinf(alpha),
                cosf(alpha) * sinf(omega)};
    
    // Input movement
    if(!following_){
      const float *position = this->position();
      if(ESAT::IsKeyPressed('W')){
          float pos[] = {position[0] + (view_dir_.x * speed_ * delta_time), 
                          position[1] + (view_dir_.y * speed_ * delta_time), 
                          position[2] + (view_dir_.z * speed_ * delta_time)};
          this->set_position(pos);
      }
      if(ESAT::IsKeyPressed('S')){
          float pos[] = {position[0] - (view_dir_.x * speed_ * delta_time),
                          position[1] - (view_dir_.y * speed_ * delta_time),
                          position[2] - (view_dir_.z * speed_ * delta_time) };
          this->set_position(pos);
      }

      // Sacar vec right con cross entre forward y up

      // Calcular up verdadero empezando por uno ficticio (0,1,0)
      oxml::Vec3 upDir = {0.0f, 1.0f, 0.0f};
      oxml::Vec3 forward = {view_dir_.x, view_dir_.y, view_dir_.z};
      oxml::Vec3 rightDir = oxml::Vec3::Cross(upDir,forward);

      if(ESAT::IsKeyPressed('D')){
          float pos[] = {position[0] - (rightDir.x * speed_ * delta_time),
                          position[1] - (rightDir.y * speed_ * delta_time),
                          position[2] - (rightDir.z * speed_ * delta_time)};
          this->set_position(pos);
      }
      if(ESAT::IsKeyPressed('A')){
          float pos[] = {position[0] + (rightDir.x * speed_ * delta_time),
                          position[1] + (rightDir.y * speed_ * delta_time),
                          position[2] + (rightDir.z * speed_ * delta_time) };

          this->set_position(pos);
      }

    }

      this->set_view_direction(&view_dir_.x);
    }

    const float* position = this->position();
    //printf("ViewDir X[%f] Y[%f] Z[%f] \n", view_dir_.x, view_dir_.y, view_dir_.z);
    //printf("Pos X[%f] Y[%f] Z[%f] \n", position[0],position[1], position[2]);

    last_mouse_pos_.x = ESAT::MousePositionX();
    last_mouse_pos_.y = ESAT::MousePositionY();

  }

  void CameraCustom::setFollowObject(ESAT::Vec3 pos){
    following_ = true;
    followingPosition_ = pos;
    float posCam[] = { pos.x, pos.y + 5.0f, pos.z - 10.0f};
    this->set_position(posCam);
  }


  void CameraCustom::setEnabled(const bool enabled){
    enabled_ = enabled;

  }
  void CameraCustom::setSpeed(const float speed){
    speed_ = speed;
  }
  void CameraCustom::setSensitibity(const float sensitivity){
    sensitivity_ = sensitivity;
  }

  const bool CameraCustom::enabled() const{
    return enabled_;
  }
  float CameraCustom::speed() const{
    return speed_;
  }
  float CameraCustom::sensitivity() const{
    return sensitivity_;
  }
  ESAT::Vec3 CameraCustom::direction() const{
    return view_dir_;
  }



}
