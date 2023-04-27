#include <oxml/assert.h>

namespace oxml {

  inline float Vec3::Magnitude() const {
    return sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
  }

  inline void Vec3::Normalize() {

    /*float inverseMagnitude = 1.0f / Magnitude();
    *this *= inverseMagnitude;*/
    float hipotenusa = sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
    this->x /= hipotenusa;
    this->y /= hipotenusa;
    this->z /= hipotenusa;
  }

  inline Vec3 Vec3::Normalized() const {
    float hipotenusa = sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
    return Vec3(this->x / hipotenusa, this->y / hipotenusa, this->z / hipotenusa);
  }

  inline float Vec3::Dot(const Vec3& a, const Vec3& other) {

    return (a.x * other.x) + (a.y * other.y) + (a.z * other.z);
  }

  inline float Vec3::Angle(const Vec3& a, const Vec3& b){

    return acosf((Dot(a,b)/(a.Magnitude() * b.Magnitude())));
  }

  inline Vec3 Vec3::Cross(const Vec3& a, const Vec3& b){

    return Vec3((a.y * b.z) - (a.z*b.y), (a.z*b.x) - (a.x*b.z), (a.x * b.y) - (a.y*b.x));
  }

  inline float Vec3::SqrMagnitude() const {

    return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
  }

  inline void Vec3::Scale(const Vec3& other){
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
  }

  inline Vec3 Vec3::Lerp(const Vec3& a, const Vec3& b, float t) {
    t = Mathf::Clamp01(t);
    return Vec3(a + (b - a) * t);
  }

  inline Vec3 Vec3::LerpUnclamped(const Vec3& a, const Vec3& b, float t) {
    return Vec3(a + (b - a) * t);
  }

  inline float Vec3::Distance(const Vec3& a, const Vec3& b) {
    //Vec3 aux(b-a);
    //return aux.Magnitude();
    return Vec3(b - a).Magnitude();
  }

  inline Vec3 Vec3::Reflect(const Vec3& direction, const Vec3& normal) {
    Vec3 rslt;
    Vec3 aux = normal.Normalized() * (-2.0f * Dot(direction, normal.Normalized()));
    rslt = direction + aux;
    return rslt;
  }

  inline bool Approximately(const Vec3& a, const Vec3& b, float tolerance){
    return Mathf::Abs(b.x - a.x) <= tolerance && Mathf::Abs(b.y - a.y) <= tolerance && Mathf::Abs(b.z - a.z) <= tolerance;
  }

  inline Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
  }

  inline Vec3 Vec3::operator+(float value) const {
    return Vec3(this->x+value, this->y+value, this->z+value);
  }

  inline Vec3& Vec3::operator+=(const Vec3& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
  }

  inline Vec3& Vec3::operator+=(float value) {
    this->x += value;
    this->y += value;
    this->z += value;
    return *this;
  }

  inline Vec3 Vec3::operator-() {
    return Vec3(this->x*(-1.0f),this->y*(-1.0f),this->z*(-1.0f));
  }

  inline Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
  }

  inline Vec3 Vec3::operator-(float value) const {
    return Vec3(this->x - value, this->y - value, this->z - value);
  }

  inline Vec3& Vec3::operator-=(const Vec3& other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
  }

  inline Vec3& Vec3::operator-=(float value) {
    this->x -= value;
    this->y -= value;
    this->z -= value;
    return *this;
  }

  inline bool Vec3::operator==(const Vec3& other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z;
  }

  inline bool Vec3::operator!=(const Vec3& other) const {
    return this->x != other.x && this->y != other.y && this->z != other.x;
  }

  inline void Vec3::operator=(const Vec3& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
  }

  inline void Vec3::operator=(float value) {
    this->x = value;
    this->y = value;
    this->z = value;
  }

  inline Vec3 Vec3::operator*(float value) const {
    
    return Vec3(this->x * value,this->y * value,this->z * value);
  }

  inline Vec3& Vec3::operator*=(float value) {
    this->x *= value;
    this->y *= value;
    this->z *= value;
    return *this;
  }

  inline Vec3 Vec3::operator/(float value) const {
    return Vec3(this->x / value,this->y / value,this->z / value);
  }

  inline Vec3& Vec3::operator/=(float value) {
    this->x /= value;
    this->y /= value;
    this->z /= value;
    return *this;
  }

  inline float& Vec3::operator[](int index) {
    oxml_assert(index<=2 && index>0, "Index out of range");
    switch(index){
     default:
     case 0:
      return this->x;
     case 1:
      return this->y;
     case 2:
      return this->z;
    }
  }

  inline const float& Vec3::operator[](int index) const {
    oxml_assert(index<=2 && index>0, "Index out of range");
    switch(index){
     default:
     case 0:
      return this->x;
     case 1:
      return this->y;
     case 2:
      return this->z;
    }
  }
  
}