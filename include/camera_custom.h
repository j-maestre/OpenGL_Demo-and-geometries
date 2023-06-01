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

/**
 * @class CameraCustom
 * @brief Custom camera class derived from EDK3::Camera.
 *
 * This class represents a custom camera used for graphic programming.
 */
class CameraCustom : public EDK3::Camera {
 public:
   /**
   * @brief Default constructor.
   */
  CameraCustom();

  /**
   * @brief Initializes the camera view target.
   *
   * @param window_width The width of the window.
   * @param window_height The height of the window.
   */
  void initViewTarget(const float window_width,
                      const float window_height);
  
  /**
   * @brief Updates the camera.
   *
   * @param dt The time step.
   * @param window_width The width of the window.
   * @param window_height The height of the window.
   */
  void update(const double dt, const float window_width,
              const float window_height);

  /**
   * @brief Sets the camera's enabled state.
   *
   * @param enabled The enabled state.
   */
  void setEnabled(const bool enabled);

  /**
   * @brief Sets the camera's speed.
   *
   * @param speed The camera speed.
   */
  void setSpeed(const float speed);

  /**
   * @brief Sets the camera's sensitivity.
   *
   * @param sensitivity The camera sensitivity.
   */
  void setSensitibity(const float sensitivity);

  /**
   * @brief Sets the camera to follow an object.
   *
   * @param pos The position of the object to follow.
   */
  void setFollowObject(ESAT::Vec3 pos);

  /**
   * @brief Returns the enabled state of the camera.
   *
   * @return The enabled state.
   */
  const bool enabled() const;

  /**
   * @brief Returns the camera speed.
   *
   * @return The camera speed.
   */
  float speed() const;

  /**
   * @brief Returns the camera sensitivity.
   *
   * @return The camera sensitivity.
   */
  float sensitivity() const;

  /**
   * @brief Returns the camera direction.
   *
   * @return The camera direction.
   */
  ESAT::Vec3 direction() const;

  /**
   * @brief Performs the culling operation on the camera.
   *
   * @param root_node The root node for culling.
   */
  virtual void doCull(const Node* root_node) override;

  /**
   * @brief Performs the rendering operation on the camera.
   */
  virtual void doRender() const override;

  /**
   * @brief Sets the wireframe mode.
   *
   * @param wireframe The wireframe mode.
   */
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
