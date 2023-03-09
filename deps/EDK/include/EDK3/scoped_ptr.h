// ----------------------------------------------------------------------------
// Copyright (C) 2014 Jose L. Hidalgo 
// Scoped_ptr, original code from boost.
// ----------------------------------------------------------------------------
//  scoped_ptr mimics a built-in pointer except that it guarantees deletion
//  of the object pointed to, either on destruction of the scoped_ptr or via
//  an explicit reset(). scoped_ptr is a simple solution for simple needs;
// ----------------------------------------------------------------------------

#ifndef INCLUDE_EDK3_SCOPED_PTR_H_
#define INCLUDE_EDK3_SCOPED_PTR_H_

#include <cassert>
#include <algorithm>

namespace EDK3 {

  template<class T> class scoped_ptr {  // noncopyable
  public:

    scoped_ptr() : px_(NULL) {}

    typedef T element_type;

    ~scoped_ptr() {
      delete px_;
    }

    T* alloc() { internal_reset(new T()); return px_; }

    template <class T2>
    T2* allocT() { internal_reset(new T2()); return (T2*)px_; }

    void release() {
      internal_reset(NULL);
    }

    T& operator*() {
        assert(px_ != 0);
        return *px_;
    }

    const T& operator*() const {
        assert(px_ != 0);
        return *px_;
    }

    T* operator->() {
        assert(px_ != 0);
        return px_;
    }

    const T* operator->() const {
        assert(px_ != 0);
        return px_;
    }


    T* get() const {
        return px_;
    }

    operator bool() const {
        return px_ != 0;
    }

    void swap(scoped_ptr &b) {
        T * tmp = b.px_;
        b.px_ = px_;
        px_ = tmp;
      }

  private:
    T* px_;

    void internal_reset(T *p = 0) {
        assert(p == 0 || p != px_);  // catch self-reset errors
        this_type(p).swap(*this);
    }

    explicit scoped_ptr(T *p): px_(p) {
    }

    explicit scoped_ptr(scoped_ptr const &);
    scoped_ptr & operator=(scoped_ptr const &);

    typedef scoped_ptr<T> this_type;

    void operator==(scoped_ptr const&) const;
    void operator!=(scoped_ptr const&) const;
  };

  template<class T> inline void swap(scoped_ptr<T> &a, scoped_ptr<T> &b) {
      a.swap(b);
  }

  // get_pointer(p) is a generic way to say p.get()
  template<class T> inline T * get_pointer(scoped_ptr<T> const & p) {
      return p.get();
  }


}  // EDK3
#endif  // INCLUDE_EDK3_SCOPED_PTR_H_
