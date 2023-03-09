#ifndef INCLUDE_EDK3_MATERIALSETTINGS_H_
#define INCLUDE_EDK3_MATERIALSETTINGS_H_ 1

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Jose L. Hidalgo 
// MaterialSettings Class.
// ----------------------------------------------------------------------------

#include "referenced.h"

namespace EDK3 {

  class MaterialSettings : public virtual Referenced {
  public:

  protected:
    MaterialSettings() {}
    virtual ~MaterialSettings() {}

  private:
    MaterialSettings(const MaterialSettings&);
    MaterialSettings& operator=(const MaterialSettings &);
  };

} /* end of EDK3 Namespace */

#endif
