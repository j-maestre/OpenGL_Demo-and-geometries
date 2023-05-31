/**
 *
 * @brief Custom camera header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __CAMERA_CUSTOM_H__
#define __CAMERA_CUSTOM_H__ 1

#include "EDK3/camera.h"
#include "ESAT/math.h"
#include "joystick.h"


namespace EDK3 {

class CameraCustom : public EDK3::Camera {
 public:
  CameraCustom();

  void initViewTarget(const float window_width,
                      const float window_height);

  void update(const double dt, const float window_width,
              const float window_height);

  void setEnabled(const bool enabled);
  void setSpeed(const float speed);
  void setSensitibity(const float sensitivity);

  void setFollowObject(ESAT::Vec3 pos);

  const bool enabled() const;
  float speed() const;
  float sensitivity() const;
  ESAT::Vec3 direction() const;

  virtual void doCull(const Node* root_node) override;
  virtual void doRender() const override;

  void set_wireframe(bool wireframe);

  bool following_;
  bool joysticConected_;
  EDK3::ref_ptr<Joystick> joystick_;
  float joystickMovementSpeed_;
  float joystickSensitivity_;
  float turboSpeed_;
  ESAT::Vec2 accum_joystick_offset_;
  ESAT::Vec2 last_joystick_offset_;

  struct CamData;
 protected:
  virtual ~CameraCustom();

  //TODO anything with these vars, these vars can be changed:
  bool enabled_;
  float speed_;
  float sensitivity_;
  float atenuation_;
  ESAT::Vec2 accum_mouse_offset_;
  ESAT::Vec3 view_dir_;
  ESAT::Vec2 last_mouse_pos_;
  ESAT::Vec3 followingPosition_;
  EDK3::scoped_ptr<CamData> data_;
  bool wireframe_;
  

 private:
  CameraCustom(const CameraCustom&);
  //CameraCustom(CameraCustom&&);
  CameraCustom& operator=(const CameraCustom&);
};

} //EDK3

#endif //__CAMERA_CUSTOM_H__
