/**
 * \file camera.h
 * \author Hector Ochando <ochandoca@esat-alumni.com>
 * 
 */
#ifndef __OXML_ASSERT_H__
#define __OXML_ASSERT_H__ 1

#undef oxml_assert

#ifdef NDEBUG

#define oxml_assert(expression) ((void)0)

#else

  void _oxml_assert(
    const char *expression,
    const char *message, 
    const char *file, 
    const char *function, 
    unsigned int line
  );

  void _oxml_static_assert(
    bool expression, 
    const char *message, 
    const char *file, 
    const char *function, 
    unsigned int line
  );

#define oxml_assert(expression, message) (void)(                                  \
				(!!(expression)) ||                                                       \
				(_oxml_assert(#expression, message, __FILE__, __FUNCTION__, __LINE__), 0) \
)

#define oxml_static_assert(expression, message) (_oxml_static_assert(expression, message, __FILE__, __FUNCTION__, __LINE__))

#endif // NDEBUG

#endif