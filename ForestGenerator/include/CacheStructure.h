//----------------------------------------------------------------------------------------------------------------------
/// @file Instance.h
/// @author Ben Carey
/// @version 1.0
/// @date 30/07/19
//----------------------------------------------------------------------------------------------------------------------

#ifndef CACHESTRUCTURE_H_
#define CACHESTRUCTURE_H_

#include <vector>


//----------------------------------------------------------------------------------------------------------------------
/// @class CacheStructure
/// @brief this class makes it easier to store the nesting of a cache structure
//----------------------------------------------------------------------------------------------------------------------

template<class T>
class CacheStructure
{
  CacheStructure() = default;

  std::vector<std::vector<std::vector<T>>> m_cache;

  void resizeCache(size_t _numBranches, size_t _numGenerations);

  template<class U>
  void resizeCache(CacheStructure<U> &_otherCacheStructure);

  T getElement(size_t _id, size_t _age, size_t _innerIndex) const;

  void setElement(size_t _id, size_t _age, size_t _innerIndex, T _value);

  void forEachElement(void (*_function)());

  template<class U>
  void forEachElement(void (*_function)(U), U _parameter);

  template<class U, class V>
  V forEachElement(V (*_function)(U), U _parameter);
};


#endif //CACHESTRUCTURE_H_
