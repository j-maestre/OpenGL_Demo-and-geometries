#ifndef INCLUDE_EDK3_DRAWABLE_H_
#define INCLUDE_EDK3_DRAWABLE_H_ 1

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Jose L. Hidalgo 
// Drawable Class.
// ----------------------------------------------------------------------------

#include "node.h"
#include "geometry.h"
#include "material.h"
#include "materialsettings.h"

namespace EDK3 {

  class Drawable : public Node {
  public:
    Drawable();
	void set_visible(bool b) { visible_ = b;  }
    void set_material(Material *m);
    void set_material_settings(MaterialSettings *ms);
    void set_geometry(Geometry *g);

	bool visible() const { return visible_; }
	Material* material()                  { return material_.get();          }
	MaterialSettings* material_settings() { return material_settings_.get(); }
	Geometry* geometry()                  { return geometry_.get();          }
	
    const Material* material() const                  { return material_.get(); }
    const MaterialSettings* material_settings() const { return material_settings_.get(); }
    const Geometry* geometry() const                  { return geometry_.get(); }

  protected:
    virtual ~Drawable();
  private:
    Drawable(const Drawable&);
    Drawable& operator=(const Drawable &);
	bool visible_;
    ref_ptr<Geometry> geometry_;
    ref_ptr<Material> material_;
    ref_ptr<MaterialSettings> material_settings_;
  };

} /* end of EDK Namespace */

#endif
