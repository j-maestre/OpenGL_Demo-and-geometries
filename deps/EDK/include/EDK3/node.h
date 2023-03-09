#ifndef INCLUDE_EDK3_NODE_H_
#define INCLUDE_EDK3_NODE_H_ 1

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Jose L. Hidalgo 
// Camera Class.
// ----------------------------------------------------------------------------

#include "referenced.h"

namespace EDK3 {

  class Node : public virtual Referenced {
  public:
    Node();

	void set_user_data(Referenced *);
	Referenced* user_data();
	const Referenced* user_data() const;

    const char *name() const;
    void set_name(const char *name);

	const float* position() const;
	const float* scale() const;
	const float* rotation_xyz() const;

    void set_position(const float p[3]);
    void set_HPR(float yaw, float pitch, float roll);
	void set_rotation_xyz(float x, float y, float z);
    void set_heading(float);
    void set_pitch(float);
    void set_roll(float);
    void set_scale(const float p[3]);
    void set_rotation_x(float f) { set_pitch(f);   }
    void set_rotation_y(float f) { set_heading(f); }
	void set_rotation_z(float f) { set_roll(f);    }

    void set_scale(float x, float y, float z) {
      float d[] = {x,y,z};
      set_scale(d);
    }

    void set_position(float x, float y , float z) {
      float d[] = {x,y,z};
      set_position(d);
    }

    void set_HPR(float *ypr) {
      set_HPR(ypr[0], ypr[1], ypr[2]);
    }

	void set_rotation_xyz(float *d) {
      set_rotation_xyz(d[0],d[1],d[2]);
    }
    
    void set_local_transform(const float p[16]);
    const float* local_transform() const;    
    const float* inverse_local_transform() const;

	// Returns the last world transform for this node
	// Depends on the camera that viewed(traversed) the node for the last time.
	// Computed as part of the camera's doCull method
	const float* last_world_transform() const;

    virtual const unsigned int addChild(Node *n);

    void removeChild(const Node *n);
    void removeChildByIndex(const unsigned int index);
    // if the child exists inside the parent returns true and fills *result with the child-index
    const bool childIndex(const Node *n, unsigned int *result) const;
    const unsigned int num_children() const;

    const Node* child(const unsigned int index) const;
    Node* child(const unsigned int index);
	const Node* parent() const;
	Node* parent();

    struct Data;
	Data * const data_;
  protected:
      virtual ~Node();
  private:
    Node(const Node&);
    Node& operator=(const Node &);

    
  };

} /* end of EDK Namespace */

#endif
