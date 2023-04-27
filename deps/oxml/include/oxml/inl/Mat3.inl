namespace oxml {

  inline Mat3 Mat3::operator+(const Mat3& other) const {
    Mat3 aux;
    for(int i = 0; i< 9; i++){
      aux.m[i] = m[i]+other.m[i];
    }
    return aux;
  }

  inline Mat3& Mat3::operator+=(const Mat3& other) {
    for(int i = 0; i < 9; i++){
      m[i] += other.m[i];
    }
    return (*this);
  }

  inline Mat3 Mat3::operator+(float value) const {
    Mat3 aux;
    for(int i = 0; i < 9; i++){
      aux.m[i] = m[i] + value;
    }

    return aux;
  }

  inline Mat3& Mat3::operator+=(float value) {
    for(int i = 0; i < 9; i++){
      m[i] += value;
    }
    return (*this);
  }

  inline Mat3 Mat3::operator-(const Mat3& other) const {
    Mat3 aux;
    for(int i = 0; i< 9; i++){
      aux.m[i] = m[i]-other.m[i];
    }
    return aux;
  }

  inline Mat3& Mat3::operator-=(const Mat3& other) {
    for(int i = 0; i < 9; i++){
      m[i] -= other.m[i];
    }
    return (*this);
  }

  inline Mat3 Mat3::operator-(float value) const {
    Mat3 aux;
    for(int i = 0; i < 9; i++){
      aux.m[i] = m[i] - value;
    }

    return aux;
  }

  inline Mat3& Mat3::operator-=(float value) {
    for(int i = 0; i < 9; i++){
      m[i] -= value;
    }
    return (*this);
  }

  inline Mat3 Mat3::operator*(float value) const {
    Mat3 aux;
    for(int i = 0; i< 9; i++){
      aux.m[i] = m[i]*value;
    }
    return aux;
  }

  inline Mat3& Mat3::operator*=(float value) {
    for(int i = 0; i < 9; i++){
      m[i] *= value;
    }
    return (*this);
  }

  inline Mat3 Mat3::operator/(float value) const {
    Mat3 aux;
    for(int i = 0; i< 9; i++){
      aux.m[i] = m[i]/value;
    }
    return aux;
  }

  inline Mat3& Mat3::operator/=(float value) {
    for(int i = 0; i < 9; i++){
      m[i] /= value;
    }
    return (*this);
  }

  inline bool Mat3::operator==(const Mat3& other) const {
    for(int i = 0; i < 9; i++){
      if(m[i]!= other.m[i]){
        return false;
      }
    }
    return true;
  }

  inline bool Mat3::operator!=(const Mat3& other) const {
    for(int i = 0; i < 9; i++){
      if(m[i]!= other.m[i]){
        return true;
      }
    }
    return false;
  }

  inline void Mat3::operator=(const Mat3& other) {
    for (int i = 0; i < 9; i++){
      m[i] = other.m[i];
    }
  }

  inline Mat3 Mat3::Identity() {
    Mat3 m;
    m.m[0] = 1.0f; m.m[1] = 0.0f; m.m[2] = 0.0f;
    m.m[3] = 0.0f; m.m[4] = 1.0f; m.m[5] = 0.0f;
    m.m[6] = 0.0f; m.m[7] = 0.0f; m.m[8] = 1.0f;
    return m;
  }

  inline float Mat3::Determinant() const {
    return ((m[0]* m[4]*m[8]) + (m[3]*m[7]*m[2]) + (m[6]*m[1]*m[5])) - ((m[2]* m[4]*m[6]) + (m[5]*m[7]*m[0]) + (m[8]*m[1]*m[3]));
  }

  inline bool Mat3::GetInverse(Mat3& out) const {
    if(this->Determinant() != 0){
      out = this->Adjoint().Transpose() / this->Determinant();
      return true;
    }

    return false;
  }

  inline bool Mat3::Inverse() {
    if(this->Determinant() != 0){
      (*this) = this->Adjoint().Transpose() / this->Determinant();
      return true;
    }

    return false;

  }

  inline Mat3 Mat3::Translate(const Vec2& mov_vector) {
    Mat3 aux(Identity());
    aux.m[2] = mov_vector.x;
    aux.m[5] = mov_vector.y;
    return aux;
  }

  inline Mat3 Mat3::Translate(float x, float y) {
    Mat3 aux(Identity());
    aux.m[2] = x;
    aux.m[5] = y;
    return aux;
  }

  inline Mat3 Mat3::Rotate(const float rotation) {
    Mat3 aux(Identity());
    aux.m[0] = cosf(rotation);
    aux.m[1] = sinf(rotation);
    aux.m[3] = sinf(rotation) * -1.0f;
    aux.m[4] = cosf(rotation);
    // GUSTAVO: There's a return statement missing here.
  }

  inline Mat3 Mat3::Multiply(const Mat3& other) const {
    Mat3 result;
    Vec3 fila;
    Vec3 columna;

    // Primera posicion
    fila.x = m[0]; fila.y = m[1]; fila.z = m[2];
    columna.x = other.m[0];columna.y = other.m[3]; columna.z = other.m[6];
    result.m[0] = Vec3::Dot(fila,columna);
    
    //Segunda posicion
    columna.x = other.m[1];columna.y = other.m[4]; columna.z = other.m[7];
    result.m[1] = Vec3::Dot(fila,columna);
    
    //Tercera posicion
    columna.x = other.m[2];columna.y = other.m[5]; columna.z = other.m[8];
    result.m[2] = Vec3::Dot(fila,columna);

    //Cuarta posicion
    fila.x = m[3]; fila.y = m[4]; fila.z = m[5];
    columna.x = other.m[0];columna.y = other.m[3]; columna.z = other.m[6];
    result.m[3] = Vec3::Dot(fila,columna);
    
    //Quinta posicion
    columna.x = other.m[1];columna.y = other.m[4]; columna.z = other.m[7];
    result.m[4] = Vec3::Dot(fila,columna);
    
    //Sexta posicion
    columna.x = other.m[2];columna.y = other.m[5]; columna.z = other.m[8];
    result.m[5] = Vec3::Dot(fila,columna);

    //Septima posicion
    fila.x = m[6]; fila.y = m[7]; fila.z = m[8];
    columna.x = other.m[0];columna.y = other.m[3]; columna.z = other.m[6];
    result.m[6] = Vec3::Dot(fila,columna);
    
    //Octava posicion
    columna.x = other.m[1];columna.y = other.m[4]; columna.z = other.m[7];
    result.m[7] = Vec3::Dot(fila,columna);
    
    //Novena posicion
    columna.x = other.m[2];columna.y = other.m[5]; columna.z = other.m[8];
    result.m[8] = Vec3::Dot(fila,columna);

    return result;
  }
  
  inline Mat3 Mat3::Adjoint() const {
    //Primero lo del determinante de quitar filas y columnas

    Mat3 mcof;
    //Primera posicion
    mcof.m[0] = (m[4]*m[8])-(m[5]*m[7]);

    //Segunda posicion
    mcof.m[1] = -((m[3]*m[8])-(m[6]*m[5])); //Falla aqui

    //Tercera posicion
    mcof.m[2] = (m[3]*m[7])-(m[6]*m[4]);

    //Cuarta posicion
    mcof.m[3] = -((m[1]*m[8])-(m[7]*m[2]));

    //Quinta posicion
    mcof.m[4] = (m[0]*m[8])-(m[6]*m[2]);
    
    //Sexta posicion
    mcof.m[5] = -((m[0]*m[7])-(m[6]*m[1]));
    
    //Septima posicion
    mcof.m[6] = (m[1]*m[5])-(m[4]*m[2]);
    
    //Octava posicion
    mcof.m[7] = -((m[0]*m[5])-(m[3]*m[2]));
    
    //Novena posicion
    mcof.m[8] = (m[0]*m[4])-(m[3]*m[1]);
    
    return mcof;
    //return mcof.Transpose();
  }

  inline Mat3 Mat3::Transpose() const {
    Mat3 trans;
    trans.m[0] = m[0];
    trans.m[1] = m[3];
    trans.m[2] = m[6];

    trans.m[3] = m[1];
    trans.m[4] = m[4];
    trans.m[5] = m[7];

    trans.m[6] = m[2];
    trans.m[7] = m[5];
    trans.m[8] = m[8];

    return trans;
  }

  inline Vec3 Mat3::GetColum(int colum) const {

    return Vec3(m[colum],m[colum+3],m[colum+6]);
  }

  inline Vec3 Mat3::GetRow(int row) const {

    return Vec3(m[row*3],m[(row*3)+1],m[(row*3)+2]);
  }

}
