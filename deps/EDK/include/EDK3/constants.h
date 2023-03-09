// ----------------------------------------------------------------------------
// Copyright (C) 2014 Jose L. Hidalgo 
// Engine Constants
// ----------------------------------------------------------------------------

#ifndef INCLUDE_EDK3_CONSTANTS_H_
#define INCLUDE_EDK3_CONSTANTS_H_ 1

namespace EDK3 {

  enum Type {
    T_NONE = 0x0,
    T_FLOAT_1,
    T_FLOAT_2,
    T_FLOAT_3,
    T_FLOAT_4,
    
    T_DOUBLE_1,
    T_DOUBLE_2,
    T_DOUBLE_3,
    T_DOUBLE_4,
    
    T_INT_1,
    T_INT_2,
    T_INT_3,
    T_INT_4,

    T_UINT_1,
    T_UINT_2,
    T_UINT_3,
    T_UINT_4,
    
    T_BYTE_1,
    T_BYTE_2,
    T_BYTE_3,
    T_BYTE_4,

    T_UBYTE_1,
    T_UBYTE_2,
    T_UBYTE_3,
    T_UBYTE_4,

    T_SHORT_1,
    T_SHORT_2,
    T_SHORT_3,
    T_SHORT_4,

    T_USHORT_1,
    T_USHORT_2,
    T_USHORT_3,
    T_USHORT_4,

    T_MAT_4x4,
    T_MAT_3x3,
    T_MAT_2x2,

    T_SAMPLER_1D,
    T_SAMPLER_2D,
    T_SAMPLER_3D,

    // aliases
    T_FLOAT   = T_FLOAT_1,
    T_DOUBLE  = T_DOUBLE_1,
    T_INT     = T_INT_1,
    T_UINT    = T_UINT_1,
    T_BYTE    = T_BYTE_1,
    T_UBYTE   = T_UBYTE_1,
    T_SHORT   = T_SHORT_1,
    T_USHORT  = T_USHORT_1,

    //--------------------------
    T_MAX_DEFINED // max value of defined types
  };

  enum Attribute {
    A_NONE = 0x0,
    A_POSITION,
    A_NORMAL,
    A_TANGENT,
    A_BITANGENT,
    A_FOG,

    A_UV,
    A_UV0 = A_UV,
    A_UV1,
    A_UV2,
    A_UV3,
    A_UV4,
    A_UV5,
    A_UV7,

    A_COLOR,
    A_SECONDARY_COLOR,
    A_COLOR0 = A_COLOR,
    A_COLOR1 = A_SECONDARY_COLOR,
    A_COLOR2,
    A_COLOR3,
    A_COLOR4,
    A_COLOR5,
    A_COLOR6,
    A_COLOR7,
    
    A_WEIGHT,
    A_WEIGHT0 = A_WEIGHT,
    A_WEIGHT1,
    A_WEIGHT2,
    A_WEIGHT3,
    A_WEIGHT4,
    A_WEIGHT5,
    A_WEIGHT6,
    A_WEIGHT7,
    A_WEIGHT8,
    A_WEIGHT9,
    A_WEIGHT10,
    A_WEIGHT11,
    A_WEIGHT12,
    A_WEIGHT13,
    A_WEIGHT14,
    A_WEIGHT15,

    A_USER_MIN,
    A_USER_MAX = 32,

    A_MAX_INDEX_NUMBER,
  };

} // end of EDK3 Namespace

#endif
