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
  joysticConected_ = false;
  joystickMovementSpeed_ = 0.01f;
  joystickSensitivity_ = 8.0f;
  turboSpeed_ = 0.2f;
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

    accum_joystick_offset_.x = 0.0001f;
    accum_joystick_offset_.y = 0.0001f;
    //set_view_direction(&view_dir_.x);
}

void CameraCustom::update(const double delta_time, const float window_width, const float window_height){

  bool clickPressed = ESAT::MouseButtonPressed(1);

  // Mouse rotation
  if(clickPressed || joysticConected_){

    accum_mouse_offset_.x += (float)ESAT::MousePositionX() - last_mouse_pos_.x;
    accum_mouse_offset_.y += ESAT::MousePositionY() - last_mouse_pos_.y;

    float omega = 0.0f;
    float alpha = 0.0f;


    if(joysticConected_ && joystick_->rightAxis_[0] >= -1.0f && joystick_->rightAxis_[0] <= 1.0f){
      accum_joystick_offset_.x += joystick_->rightAxis_[0];
      accum_joystick_offset_.y += joystick_->rightAxis_[1];

      omega = accum_joystick_offset_.x / window_width * oxml::Mathf::PI * 2.0f * joystickSensitivity_;
      alpha = accum_joystick_offset_.y / window_height * (oxml::Mathf::PI - oxml::Mathf::PI * 0.5f) * joystickSensitivity_;
    }
    
    if(clickPressed){

      omega = accum_mouse_offset_.x / window_width * oxml::Mathf::PI * 2.0f * sensitivity_;
      alpha = accum_mouse_offset_.y / window_height * (oxml::Mathf::PI - oxml::Mathf::PI * 0.5f) * sensitivity_;
    }
    
    view_dir_ = {cosf(alpha) * cosf(omega),
                -sinf(alpha),
                cosf(alpha) * sinf(omega)};
    
    // Input movement
    if(!following_){

      const float *position = this->position();

      // Movement by keyboard
      if(clickPressed){
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
      }

      // Movement by joystick
      if(joysticConected_){
        const float *position = this->position();
          if(abs(joystick_->leftAxis_[1]) > joystick_->leftDeadZone_ && joystick_->leftAxis_[1] >= -1.0f && joystick_->leftAxis_[1] <= 1.0f){ // Y axis
              float turbo =  (joystickMovementSpeed_ + ((joystick_->r2Trigger_ * 0.5f + 0.5f)) * turboSpeed_);
              float pos[] = {position[0] -  (joystick_->leftAxis_[1] * view_dir_.x * delta_time * turbo), 
                              position[1] - (joystick_->leftAxis_[1] * view_dir_.y * delta_time * turbo), 
                              position[2] - (joystick_->leftAxis_[1] * view_dir_.z * delta_time * turbo)};
              this->set_position(pos);
          }
          
      }



      // Sacar vec right con cross entre forward y up

      // Calcular up verdadero empezando por uno ficticio (0,1,0)
      oxml::Vec3 upDir = {0.0f, 1.0f, 0.0f};
      oxml::Vec3 forward = {view_dir_.x, view_dir_.y, view_dir_.z};
      oxml::Vec3 rightDir = oxml::Vec3::Cross(upDir,forward);

      // Movement by keyboard
      if(clickPressed){
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

      // Movement by controller
      if(joysticConected_){
         if(abs(joystick_->leftAxis_[0]) > joystick_->leftDeadZone_ && joystick_->leftAxis_[0] >= -1.0f && joystick_->leftAxis_[0] <= 1.0f){
          float turbo =  (joystickMovementSpeed_ + ((joystick_->r2Trigger_ * 0.5f + 0.5f)) * turboSpeed_);

          float pos[] = {position[0] - (joystick_->leftAxis_[0] * rightDir.x * delta_time * turbo),
                         position[1] - (joystick_->leftAxis_[0] * rightDir.y * delta_time * turbo),
                         position[2] - (joystick_->leftAxis_[0] * rightDir.z * delta_time * turbo)};
          this->set_position(pos);
         }
      }

    }

      this->set_view_direction(&view_dir_.x);
    }


    const float* position = this->position();
    //printf("ViewDir X[%f] Y[%f] Z[%f] \n", view_dir_.x, view_dir_.y, view_dir_.z);
    //printf("Pos X[%f] Y[%f] Z[%f] \n", position[0],position[1], position[2]);

  

    last_mouse_pos_.x = ESAT::MousePositionX();
    last_mouse_pos_.y = ESAT::MousePositionY();

    if(joysticConected_){
      last_joystick_offset_.x = oxml::Mathf::Clamp(abs(joystick_->rightAxis_[0]),joystick_->rightDeadZone_,1.0f) * oxml::Mathf::Sign(joystick_->rightAxis_[0]);
      last_joystick_offset_.y = oxml::Mathf::Clamp(abs(joystick_->rightAxis_[1]),joystick_->rightDeadZone_,1.0f) * oxml::Mathf::Sign(joystick_->rightAxis_[1]);
    }
  

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
