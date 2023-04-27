namespace oxml {

  inline Mat2 Mat2::operator+(const Mat2& other) const {
    float points[4];
    for(int i = 0; i < 4; i++){
      points[i] = this->m[i] + other.m[i];
    }
    return Mat2(points);
  }

  inline void Mat2::operator+=(const Mat2& other) {
    for(int i = 0; i < 4; i++){
      this->m[i] += other.m[i];
    }
  }

  inline Mat2 Mat2::operator+(float value) const {
    float points[4];
    for(int i = 0; i < 4; i++){
      points[i] = this->m[i] + value;
    }
    return Mat2(points);
  }

  inline void Mat2::operator+=(float value) {
    for(int i = 0; i < 4; i++){
      this->m[i] += value;
    }
  }

  inline Mat2 Mat2::operator-(const Mat2& other) const {
    float points[4];
    for(int i = 0; i < 4; i++){
      points[i] = this->m[i] - other.m[i];
    }
    return Mat2(points);
  }

  inline void Mat2::operator-=(const Mat2& other) {
    for(int i = 0; i < 4; i++){
      this->m[i] -= other.m[i];
    }
  }

  inline Mat2 Mat2::operator-(float value) const {
    float points[4];
    for(int i = 0; i < 4; i++){
      points[i] = this->m[i] - value;
    }
    return Mat2(points);
  }

  inline void Mat2::operator-=(float value) {
    for(int i = 0; i < 4; i++){
      this->m[i] -= value;
    }
  }

  inline Mat2 Mat2::operator*(float value) const {
    float points[4];
    for(int i = 0; i < 4; i++){
      points[i] = this->m[i] * value;
    }
    return Mat2(points);
  }

  inline void Mat2::operator*=(float value) {
    for(int i = 0; i < 4; i++){
      this->m[i] *= value;
    }
  }

  inline Mat2 Mat2::operator/(float value) const {
    float points[4];
    for(int i = 0; i < 4; i++){
      points[i] = this->m[i] / value;
    }
    return Mat2(points);
  }

  inline void Mat2::operator/=(float value) {
    for(int i = 0; i < 4; i++){
      this->m[i] /= value;
    }
  }

  inline bool Mat2::operator==(const Mat2& other) const {
    for(int i = 0; i<4; i++){
      if(this->m[i] != other.m[i]){
        return false;
      }
    }
    return true;
  }

  inline bool Mat2::operator!=(const Mat2& other) const {
    for(int i = 0; i<4; i++){
      if(this->m[i] != other.m[i]){
        return true;
      }
    }
    return false;
  }

  inline void Mat2::operator=(const Mat2& other) {
    for(int i = 0; i<4; i++){
      this->m[i] = other.m[i];
    }

  }

  inline Mat2 Mat2::Identity() {
    float points[4];
    points[0] = 1;
    points[1] = 0;
    points[2] = 0;
    points[3] = 1;
    return Mat2(points);
  }

  inline float Mat2::Determinant() const {
    return (this->m[0] * this->m[3]) - (this->m[1] * this->m[2]);
  }

  inline Mat2 Mat2::Inverse() const {
    float determinante = this->Determinant();
    Mat2 inverse = this->Adjoint();
    
    return Mat2(inverse * (float) (1.0f/determinante));
  }

  inline Mat2 Mat2::Multiply(const Mat2& other) const {
    float points[4];
    points[0] = m[0] * other.m[0] + m[1] * other.m[2];
    points[1] = m[0] * other.m[1] + m[1] * other.m[3];
    points[2] = m[2] * other.m[0] + m[3] * other.m[2];
    points[3] = m[2] * other.m[1] + m[3] * other.m[3];
  
    return Mat2(points);
  }

  inline Mat2 Mat2::Adjoint() const {
    float points[4];
    points[0] = this->m[3];
    points[1] = this->m[2] * (-1.0f);
    points[2] = this->m[1] * (-1.0f);
    points[3] = this->m[0];
    return Mat2(points);
  }

  inline Mat2 Mat2::Transpose() const {
    float points[4] ={m[0],m[2],m[1],m[3]};
    return Mat2(points);
  }

  inline Vec2 Mat2::GetLine(int line) const {
    oxml_assert(line <2 && line>0, "Index out of range");
    return Vec2(m[line*2],m[line*2+1]);
  }

  inline Vec2 Mat2::GetColum(int line) const{
    oxml_assert(line <2 && line>0, "Index out of range");
    return Vec2(m[line],m[line+2]);
  }

}