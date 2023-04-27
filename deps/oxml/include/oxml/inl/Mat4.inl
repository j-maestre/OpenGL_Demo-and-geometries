#include <math.h>

#include <oxml/assert.h>
#include <oxml/Mat3.h>
#include <oxml/Vec3.h>


namespace oxml {

  inline Mat4 Mat4::Identity() {
    Mat4 m;
    m.m[0] = 1.0f;
    m.m[1] = 0.0f;
    m.m[2] = 0.0f;
    m.m[3] = 0.0f;
    m.m[4] = 0.0f;
    m.m[5] = 1.0f;
    m.m[6] = 0.0f;
    m.m[7] = 0.0f;
    m.m[8] = 0.0f;
    m.m[9] = 0.0f;
    m.m[10] = 1.0f;
    m.m[11] = 0.0f;
    m.m[12] = 0.0f;
    m.m[13] = 0.0f;
    m.m[14] = 0.0f;
    m.m[15] = 1.0f;
    return m;
  }

  inline Mat4 Mat4::Multiply(const Mat4& other) const {
    Mat4 r;
    r.m[0] = ((this->m[0] * other.m[0]) + (this->m[1] * other.m[4]) + (this->m[2] * other.m[8]) + (this->m[3] * other.m[12]));
    r.m[1] = ((this->m[0] * other.m[1]) + (this->m[1] * other.m[5]) + (this->m[2] * other.m[9]) + (this->m[3] * other.m[13]));
    r.m[2] = ((this->m[0] * other.m[2]) + (this->m[1] * other.m[6]) + (this->m[2] * other.m[10]) + (this->m[3] * other.m[14]));
    r.m[3] = ((this->m[0] * other.m[3]) + (this->m[1] * other.m[7]) + (this->m[2] * other.m[11]) + (this->m[3] * other.m[15]));
    r.m[4] = ((this->m[4] * other.m[0]) + (this->m[5] * other.m[4]) + (this->m[6] * other.m[8]) + (this->m[7] * other.m[12]));
    r.m[5] = ((this->m[4] * other.m[1]) + (this->m[5] * other.m[5]) + (this->m[6] * other.m[9]) + (this->m[7] * other.m[13]));
    r.m[6] = ((this->m[4] * other.m[2]) + (this->m[5] * other.m[6]) + (this->m[6] * other.m[10]) + (this->m[7] * other.m[14]));
    r.m[7] = ((this->m[4] * other.m[3]) + (this->m[5] * other.m[7]) + (this->m[6] * other.m[11]) + (this->m[7] * other.m[15]));
    r.m[8] = ((this->m[8] * other.m[0]) + (this->m[9] * other.m[4]) + (this->m[10] * other.m[8]) + (this->m[11] * other.m[12]));
    r.m[9] = ((this->m[8] * other.m[1]) + (this->m[9] * other.m[5]) + (this->m[10] * other.m[9]) + (this->m[11] * other.m[13]));
    r.m[10] = ((this->m[8] * other.m[2]) + (this->m[9] * other.m[6]) + (this->m[10] * other.m[10]) + (this->m[11] * other.m[14]));
    r.m[11] = ((this->m[8] * other.m[3]) + (this->m[9] * other.m[7]) + (this->m[10] * other.m[11]) + (this->m[11] * other.m[15]));
    r.m[12] = ((this->m[12] * other.m[0]) + (this->m[13] * other.m[4]) + (this->m[14] * other.m[8]) + (this->m[15] * other.m[12]));
    r.m[13] = ((this->m[12] * other.m[1]) + (this->m[13] * other.m[5]) + (this->m[14] * other.m[9]) + (this->m[15] * other.m[13]));
    r.m[14] = ((this->m[12] * other.m[2]) + (this->m[13] * other.m[6]) + (this->m[14] * other.m[10]) + (this->m[15] * other.m[14]));
    r.m[15] = ((this->m[12] * other.m[3]) + (this->m[13] * other.m[7]) + (this->m[14] * other.m[11]) + (this->m[15] * other.m[15]));
    return r;
  }

  inline float Mat4::Determinant() const {
    float det_0[9] = { this->m[5], this->m[9], this->m[13],
                     this->m[6], this->m[10], this->m[14],
                     this->m[7], this->m[11], this->m[15] };

    float det_1[9] = { this->m[4], this->m[8], this->m[12],
                       this->m[6], this->m[10], this->m[14],
                       this->m[7], this->m[11], this->m[15] };

    float det_2[9] = { this->m[4], this->m[8], this->m[12],
                       this->m[5], this->m[9], this->m[13],
                       this->m[7], this->m[11], this->m[15] };

    float det_3[9] = { this->m[4], this->m[8], this->m[12],
                       this->m[5], this->m[9], this->m[13],
                       this->m[6], this->m[10], this->m[14] };

    return (this->m[0] * Mat3(det_0).Determinant() - this->m[1] * Mat3(det_1).Determinant()
            + this->m[2] * Mat3(det_2).Determinant() - this->m[3] * Mat3(det_3).Determinant());
  }

  inline Mat4 Mat4::Adjoint() const {
    Mat3 aux_m;
    Mat4 result;
    //Adjoint matrix is the matrix formed by cofactors´s determinant
    //First Line
    aux_m.m[0] = m[5];
    aux_m.m[1] = m[6];
    aux_m.m[2] = m[7];

    aux_m.m[3] = m[9];
    aux_m.m[4] = m[10];
    aux_m.m[5] = m[11];

    aux_m.m[6] = m[13];
    aux_m.m[7] = m[14];
    aux_m.m[8] = m[15];

    result.m[0] = aux_m.Determinant();

    aux_m.m[0] = m[4];
    aux_m.m[3] = m[8];
    aux_m.m[6] = m[12];

    result.m[1] = aux_m.Determinant();

    aux_m.m[1] = m[5];
    aux_m.m[4] = m[9];
    aux_m.m[7] = m[13];

    result.m[2] = aux_m.Determinant();

    aux_m.m[2] = m[6];
    aux_m.m[5] = m[10];
    aux_m.m[8] = m[14];

    result.m[3] = aux_m.Determinant();
    //Second Line
    aux_m.m[0] = m[1];
    aux_m.m[1] = m[2];
    aux_m.m[2] = m[3];

    aux_m.m[3] = m[9];
    aux_m.m[4] = m[10];
    aux_m.m[5] = m[11];

    aux_m.m[6] = m[13];
    aux_m.m[7] = m[14];
    aux_m.m[8] = m[15];

    result.m[4] = aux_m.Determinant();

    aux_m.m[0] = m[0];
    aux_m.m[3] = m[8];
    aux_m.m[6] = m[12];

    result.m[5] = aux_m.Determinant();

    aux_m.m[1] = m[1];
    aux_m.m[4] = m[9];
    aux_m.m[7] = m[13];

    result.m[6] = aux_m.Determinant();

    aux_m.m[2] = m[2];
    aux_m.m[5] = m[10];
    aux_m.m[8] = m[14];

    result.m[7] = aux_m.Determinant();
       
    // SIGUE DESPUES
//Third Line
    aux_m.m[0] = m[1];
    aux_m.m[1] = m[2];
    aux_m.m[2] = m[3];

    aux_m.m[3] = m[5];
    aux_m.m[4] = m[6];
    aux_m.m[5] = m[7];

    aux_m.m[6] = m[13];
    aux_m.m[7] = m[14];
    aux_m.m[8] = m[15];

    result.m[8] = aux_m.Determinant();

    aux_m.m[0] = m[0];
    aux_m.m[3] = m[4];
    aux_m.m[6] = m[12];

    result.m[9] = aux_m.Determinant();

    aux_m.m[1] = m[1];
    aux_m.m[4] = m[5];
    aux_m.m[7] = m[13];

    result.m[10] = aux_m.Determinant();

    aux_m.m[2] = m[2];
    aux_m.m[5] = m[6];
    aux_m.m[8] = m[14];

    result.m[11] = aux_m.Determinant();
    //Fourth Line
    aux_m.m[0] = m[1];
    aux_m.m[1] = m[2];
    aux_m.m[2] = m[3];

    aux_m.m[3] = m[5];
    aux_m.m[4] = m[6];
    aux_m.m[5] = m[7];

    aux_m.m[6] = m[9];
    aux_m.m[7] = m[10];
    aux_m.m[8] = m[11];

    result.m[12] = aux_m.Determinant();

    aux_m.m[0] = m[0];
    aux_m.m[3] = m[4];
    aux_m.m[6] = m[8];

    result.m[13] = aux_m.Determinant();

    aux_m.m[1] = m[1];
    aux_m.m[4] = m[5];
    aux_m.m[7] = m[9];

    result.m[14] = aux_m.Determinant();

    aux_m.m[2] = m[2];
    aux_m.m[5] = m[6];
    aux_m.m[8] = m[10];

    result.m[15] = aux_m.Determinant();


    result.m[1] = -result.m[1];
    result.m[3] = -result.m[3];
    result.m[4] = -result.m[4];
    result.m[6] = -result.m[6];
    result.m[9] = -result.m[9];
    result.m[11] = -result.m[11];
    result.m[12] = -result.m[12];
    result.m[14] = -result.m[14];

    result = result.Transpose();

    return result;
  }

  inline bool Mat4::Inverse() {
    float det = Determinant();
    if (det == 0) {
      return false;
    }

    if (det == 0.0f || det == -0.0f) {
      return false;
    }

    (*this) = ((this->Adjoint()) / det);

    return true;
  }

  inline bool Mat4::GetInverse(Mat4& out) const {
    float det = Determinant();
    if (det == 0.0f || det == -0.0f) {
      return false;
    }
    out = ((this->Adjoint().Transpose()) / det);
    return true;
  }

  inline Mat4 Mat4::Transpose() const {
    Mat4 r;
    r.m[0] = m[0];
    r.m[1] = m[4];
    r.m[2] = m[8];
    r.m[3] = m[12];
    r.m[4] = m[1];
    r.m[5] = m[5];
    r.m[6] = m[9];
    r.m[7] = m[13];
    r.m[8] = m[2];
    r.m[9] = m[6];
    r.m[10] = m[10];
    r.m[11] = m[14];
    r.m[12] = m[3];
    r.m[13] = m[7];
    r.m[14] = m[11];
    r.m[15] = m[15];
    return r;
  }

  inline Mat4 Mat4::Translate(const Vec3& position) {
    Mat4 identity = Identity();
    identity.m[12] = position.x;
    identity.m[13] = position.y;
    identity.m[14] = position.z;
    return identity;
  }

  inline Mat4 Mat4::Translate(float x, float y, float z) {
    Mat4 identity = Identity();
    identity.m[12] = x;
    identity.m[13] = y;
    identity.m[14] = z;
    return identity;
  }

  inline Mat4 Mat4::Scale(const Vec3& scale) {
    Mat4 identity = Identity();
    identity.m[0] = scale.x;
    identity.m[5] = scale.y;
    identity.m[10] = scale.z;
    return identity;
  }

  inline Mat4 Mat4::Scale(float x, float y, float z) {
    Mat4 identity = Identity();
    identity.m[0] = x;
    identity.m[5] = y;
    identity.m[10] = z;
    return identity;
  }

  inline Mat4 Mat4::RotateX(float radians) {
    Mat4 identity = Identity();
    identity.m[5] = cosf(radians);
    identity.m[6] = -sinf(radians);
    identity.m[9] = sinf(radians);
    identity.m[10] = cosf(radians);

    return identity;
  }

  inline Mat4 Mat4::RotateY(float radians) {
    Mat4 identity = Identity();

    identity.m[0] = cosf(radians);
    identity.m[2] = sinf(radians);
    
    identity.m[8] = -sinf(radians);
    identity.m[10] = -cosf(radians);

    return identity;
  }

  inline Mat4 Mat4::RotateZ(float radians) {
    Mat4 identity = Identity();
    identity.m[0] = cosf(radians);
    identity.m[1] = -sinf(radians);
    identity.m[4] = sinf(radians);
    identity.m[5] = cosf(radians);

    return identity;
  }

  inline Mat4 Mat4::TRS(const Vec3& translate, const Vec3& scale, const Vec3& rotation){
    Mat4 identity = Identity();
    identity = identity.Multiply(Translate(translate));
    identity = identity.Multiply(Scale(scale));
    identity = identity.Multiply(RotateX(rotation.x));
    identity = identity.Multiply(RotateY(rotation.y));
    identity = identity.Multiply(RotateZ(rotation.z));
    return identity;
  }

  inline Mat4 Mat4::TRS(float trans_x, float trans_y, float trans_z, float scale_x, float scale_y, float scale_z, float rotateX, float rotateY, float rotateZ) {
    Mat4 identity = Identity();
    identity = identity.Multiply(Translate(trans_x,trans_y,trans_z));
    identity = identity.Multiply(Scale(scale_x,scale_y,scale_z));
    identity = identity.Multiply(RotateX(rotateX));
    identity = identity.Multiply(RotateY(rotateY));
    identity = identity.Multiply(RotateZ(rotateZ));
    return identity;
  }

  inline Vec4 Mat4::GetColum(int colum) const {

    return Vec4(m[colum], m[colum +4], m[colum + 8], m[colum + 12]);
  }

  inline Vec4 Mat4::GetRow(int row) const {
    return Vec4(m[row * 4 + 0], m[row * 4 + 1], m[row * 4 + 2], m[row * 4 + 3]);
  }

  inline Mat4 Mat4::Perspective(float fov, float aspect, float near, float far) {
    Mat4 prespective(0.0f);
    float fFovRad = 1.0f/tanf(fov*0.5f);
    prespective.m[0] = aspect * fFovRad;
    prespective.m[5] = fFovRad;
    prespective.m[10] = far / (far-near);
    prespective.m[11] = 1.0f;
    prespective.m[14] = (-far * near) / (far - near);

    return prespective;
  }

  inline Mat4 Mat4::Ortho(float right, float left, float top, float valuebottom, float near, float far) {
    right = 0;
    left = 0;
    top = 0;
    valuebottom = 0;
    near = 0;
    far = 0;
    return Mat4();
  }

  inline Mat4 Mat4::LookAt(const Vec3& from, const Vec3& to, const Vec3& up){
    Vec3 forward = from - to;
    forward.Normalize();
    Vec3 right = Vec3::Cross(up, forward);
    right.Normalize();
    Vec3 newup = Vec3::Cross(forward, right);

    Mat4 lokAt(0.0f);
    lokAt.m[0] = right.x;
    lokAt.m[1] = right.y;
    lokAt.m[2] = right.z;
    
    lokAt.m[4] = newup.x;
    lokAt.m[5] = newup.y;
    lokAt.m[6] = newup.z;    
    
    lokAt.m[8] = forward.x;
    lokAt.m[9] = forward.y;
    lokAt.m[10] = forward.z;

    lokAt.m[12] = from.x;
    lokAt.m[13] = from.y;
    lokAt.m[14] = from.z;
    lokAt.m[15] = 1.0f;
    return lokAt;
  }

  inline Mat4 Mat4::operator+(const Mat4& other) const {
    Mat4 rslt;
    rslt.m[0] = other.m[0] + this->m[0];
    rslt.m[1] = other.m[1] + this->m[1];
    rslt.m[2] = other.m[2] + this->m[2];
    rslt.m[3] = other.m[3] + this->m[3];
    rslt.m[4] = other.m[4] + this->m[4];
    rslt.m[5] = other.m[5] + this->m[5];
    rslt.m[6] = other.m[6] + this->m[6];
    rslt.m[7] = other.m[7] + this->m[7];
    rslt.m[8] = other.m[8] + this->m[8];
    rslt.m[9] = other.m[9] + this->m[9];
    rslt.m[10] = other.m[10] + this->m[10];
    rslt.m[11] = other.m[11] + this->m[11];
    rslt.m[12] = other.m[12] + this->m[12];
    rslt.m[13] = other.m[13] + this->m[13];
    rslt.m[14] = other.m[14] + this->m[14];
    rslt.m[15] = other.m[15] + this->m[15];
    return rslt;
  }

  inline Mat4& Mat4::operator+=(const Mat4& other) {
    this->m[0] += other.m[0];
    this->m[1] += other.m[1];
    this->m[2] += other.m[2];
    this->m[3] += other.m[3];
    this->m[4] += other.m[4];
    this->m[5] += other.m[5];
    this->m[6] += other.m[6];
    this->m[7] += other.m[7];
    this->m[8] += other.m[8];
    this->m[9] += other.m[9];
    this->m[10] += other.m[10];
    this->m[11] += other.m[11];
    this->m[12] += other.m[12];
    this->m[13] += other.m[13];
    this->m[14] += other.m[14];
    this->m[15] += other.m[15];
    return (*this);
  }

  inline Mat4 Mat4::operator+(float value) const {
    Mat4 rslt;
    rslt.m[0] = value + this->m[0];
    rslt.m[1] = value + this->m[1];
    rslt.m[2] = value + this->m[2];
    rslt.m[3] = value + this->m[3];
    rslt.m[4] = value + this->m[4];
    rslt.m[5] = value + this->m[5];
    rslt.m[6] = value + this->m[6];
    rslt.m[7] = value + this->m[7];
    rslt.m[8] = value + this->m[8];
    rslt.m[9] = value + this->m[9];
    rslt.m[10] = value + this->m[10];
    rslt.m[11] = value + this->m[11];
    rslt.m[12] = value + this->m[12];
    rslt.m[13] = value + this->m[13];
    rslt.m[14] = value + this->m[14];
    rslt.m[15] = value + this->m[15];
    return rslt;
  }

  inline Mat4& Mat4::operator+=(float value) {
    this->m[0] += value;
    this->m[1] += value;
    this->m[2] += value;
    this->m[3] += value;
    this->m[4] += value;
    this->m[5] += value;
    this->m[6] += value;
    this->m[7] += value;
    this->m[8] += value;
    this->m[9] += value;
    this->m[10] += value;
    this->m[11] += value;
    this->m[12] += value;
    this->m[13] += value;
    this->m[14] += value;
    this->m[15] += value;
    return (*this);
  }

  inline Mat4 Mat4::operator-(const Mat4& other) const {
    Mat4 rslt;
    rslt.m[0] = this->m[0] - other.m[0];
    rslt.m[1] = this->m[1] - other.m[1];
    rslt.m[2] = this->m[2] - other.m[2];
    rslt.m[3] = this->m[3] - other.m[3];
    rslt.m[4] = this->m[4] - other.m[4];
    rslt.m[5] = this->m[5] - other.m[5];
    rslt.m[6] = this->m[6] - other.m[6];
    rslt.m[7] = this->m[7] - other.m[7];
    rslt.m[8] = this->m[8] - other.m[8];
    rslt.m[9] = this->m[9] - other.m[9];
    rslt.m[10] = this->m[10] - other.m[10];
    rslt.m[11] = this->m[11] - other.m[11];
    rslt.m[12] = this->m[12] - other.m[12];
    rslt.m[13] = this->m[13] - other.m[13];
    rslt.m[14] = this->m[14] - other.m[14];
    rslt.m[15] = this->m[15] - other.m[15];
    return rslt;
  }

  inline Mat4& Mat4::operator-=(const Mat4& other) {
    this->m[0] -= other.m[0];
    this->m[1] -= other.m[1];
    this->m[2] -= other.m[2];
    this->m[3] -= other.m[3];
    this->m[4] -= other.m[4];
    this->m[5] -= other.m[5];
    this->m[6] -= other.m[6];
    this->m[7] -= other.m[7];
    this->m[8] -= other.m[8];
    this->m[9] -= other.m[9];
    this->m[10] -= other.m[10];
    this->m[11] -= other.m[11];
    this->m[12] -= other.m[12];
    this->m[13] -= other.m[13];
    this->m[14] -= other.m[14];
    this->m[15] -= other.m[15];
    return (*this);
  }

  inline Mat4 Mat4::operator-(float value) const {
    Mat4 rslt;
    rslt.m[0] = this->m[0] - value;
    rslt.m[1] = this->m[1] - value;
    rslt.m[2] = this->m[2] - value;
    rslt.m[3] = this->m[3] - value;
    rslt.m[4] = this->m[4] - value;
    rslt.m[5] = this->m[5] - value;
    rslt.m[6] = this->m[6] - value;
    rslt.m[7] = this->m[7] - value;
    rslt.m[8] = this->m[8] - value;
    rslt.m[9] = this->m[9] - value;
    rslt.m[10] = this->m[10] - value;
    rslt.m[11] = this->m[11] - value;
    rslt.m[12] = this->m[12] - value;
    rslt.m[13] = this->m[13] - value;
    rslt.m[14] = this->m[14] - value;
    rslt.m[15] = this->m[15] - value;
    return rslt;
  }

  inline Mat4& Mat4::operator-=(float value) {
    this->m[0] -= value;
    this->m[1] -= value;
    this->m[2] -= value;
    this->m[3] -= value;
    this->m[4] -= value;
    this->m[5] -= value;
    this->m[6] -= value;
    this->m[7] -= value;
    this->m[8] -= value;
    this->m[9] -= value;
    this->m[10] -= value;
    this->m[11] -= value;
    this->m[12] -= value;
    this->m[13] -= value;
    this->m[14] -= value;
    this->m[15] -= value;
    return (*this);
  }

  inline Mat4& Mat4::operator*=(float value) {
    this->m[0] *= value;
    this->m[1] *= value;
    this->m[2] *= value;
    this->m[3] *= value;
    this->m[4] *= value;
    this->m[5] *= value;
    this->m[6] *= value;
    this->m[7] *= value;
    this->m[8] *= value;
    this->m[9] *= value;
    this->m[10] *= value;
    this->m[11] *= value;
    this->m[12] *= value;
    this->m[13] *= value;
    this->m[14] *= value;
    this->m[15] *= value;
    return (*this);
  }

  inline Mat4 Mat4::operator*(float value) const {
    Mat4 rslt;
    rslt.m[0] = value * this->m[0];
    rslt.m[1] = value * this->m[1];
    rslt.m[2] = value * this->m[2];
    rslt.m[3] = value * this->m[3];
    rslt.m[4] = value * this->m[4];
    rslt.m[5] = value * this->m[5];
    rslt.m[6] = value * this->m[6];
    rslt.m[7] = value * this->m[7];
    rslt.m[8] = value * this->m[8];
    rslt.m[9] = value * this->m[9];
    rslt.m[10] = value * this->m[10];
    rslt.m[11] = value * this->m[11];
    rslt.m[12] = value * this->m[12];
    rslt.m[13] = value * this->m[13];
    rslt.m[14] = value * this->m[14];
    rslt.m[15] = value * this->m[15];
    return rslt;
  }

  inline Mat4& Mat4::operator/=(float value) {
    this->m[0] /= value;
    this->m[1] /= value;
    this->m[2] /= value;
    this->m[3] /= value;
    this->m[4] /= value;
    this->m[5] /= value;
    this->m[6] /= value;
    this->m[7] /= value;
    this->m[8] /= value;
    this->m[9] /= value;
    this->m[10] /= value;
    this->m[11] /= value;
    this->m[12] /= value;
    this->m[13] /= value;
    this->m[14] /= value;
    this->m[15] /= value;
    return (*this);
  }

  inline Mat4 Mat4::operator/(float value) const {
    Mat4 rslt;
    rslt.m[0] = this->m[0] / value;
    rslt.m[1] = this->m[1] / value;
    rslt.m[2] = this->m[2] / value;
    rslt.m[3] = this->m[3] / value;
    rslt.m[4] = this->m[4] / value;
    rslt.m[5] = this->m[5] / value;
    rslt.m[6] = this->m[6] / value;
    rslt.m[7] = this->m[7] / value;
    rslt.m[8] = this->m[8] / value;
    rslt.m[9] = this->m[9] / value;
    rslt.m[10] = this->m[10] / value;
    rslt.m[11] = this->m[11] / value;
    rslt.m[12] = this->m[12] / value;
    rslt.m[13] = this->m[13] / value;
    rslt.m[14] = this->m[14] / value;
    rslt.m[15] = this->m[15] / value;
    return rslt;
  }

  inline bool Mat4::operator==(const Mat4& other) const {
    bool rslt = true;
    for (int i = 0; i < 16 && rslt; i++) {
      rslt = (this->m[i] == other.m[i]);
    }
    return rslt;
  }

  inline bool Mat4::operator!=(const Mat4& other) const {
    for (int i = 0; i < 16; i++) {
       if(this->m[i] != other.m[i]){
        return true;
       }
    }
    return false;
  }

  inline Mat4& Mat4::operator=(const Mat4& other) {
    this->m[0] = other.m[0];
    this->m[1] = other.m[1];
    this->m[2] = other.m[2];
    this->m[3] = other.m[3];
    this->m[4] = other.m[4];
    this->m[5] = other.m[5];
    this->m[6] = other.m[6];
    this->m[7] = other.m[7];
    this->m[8] = other.m[8];
    this->m[9] = other.m[9];
    this->m[10] = other.m[10];
    this->m[11] = other.m[11];
    this->m[12] = other.m[12];
    this->m[13] = other.m[13];
    this->m[14] = other.m[14];
    this->m[15] = other.m[15];
    return *this;
  }

  inline Vec4 Mat4::operator*(const Vec4& vector) const {
    Vec4 rslt;
    rslt.x = (vector.x * m[0]) + (vector.y * m[1]) + (vector.z * m[2]) + (vector.w * m[3]);
    rslt.y = (vector.x * m[4]) + (vector.y * m[5]) + (vector.z * m[6]) + (vector.w * m[7]);
    rslt.z = (vector.x * m[8]) + (vector.y * m[9]) + (vector.z * m[10]) + (vector.w * m[11]);
    rslt.w = (vector.x * m[12]) + (vector.y * m[13]) + (vector.z * m[14]) + (vector.w * m[15]);
    return rslt;
  }

}