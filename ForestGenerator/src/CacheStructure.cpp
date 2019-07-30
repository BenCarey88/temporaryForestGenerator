//----------------------------------------------------------------------------------------------------------------------
/// @file CacheStructure.cpp
/// @brief implementation file for CacheStructure class
//----------------------------------------------------------------------------------------------------------------------

#include "CacheStructure.h"
#include "PrintFunctions.h"

template <class T>
void CacheStructure<T>::resizeCache(size_t _numBranches, size_t _numGenerations)
{
  m_cache = {};
  m_cache.resize(_numBranches,{});
  for(auto &vec : m_cache)
  {
    vec.resize(_numGenerations,{});
  }
}

template <class T>
template <class U>
void CacheStructure<T>::resizeCache(CacheStructure<U> &_otherCacheStructure)
{
  m_cache = {};
  std::vector<std::vector<std::vector<U>>> otherCache = _otherCacheStructure.m_cache;
  m_cache.resize(otherCache.size(),{});
  for(size_t id=0; id<m_cache.size(); id++)
  {
    m_cache[id].resize(otherCache[id].size(),{});
    for(size_t age=0; age<m_cache[id].size(); age++)
    {
      m_cache[id][age].resize(otherCache[id][age].size(),{});
    }
  }
}

template <class T>
T CacheStructure<T>::getElement(size_t _id, size_t _age, size_t _innerIndex) const
{
  return m_cache[_id][_age][_innerIndex];
}

template <class T>
void CacheStructure<T>::setElement(size_t _id, size_t _age, size_t _innerIndex, T _value)
{
  m_cache[_id][_age][_innerIndex] = _value;
}

template<class T>
void CacheStructure<T>::forEachElement(void (*_function)())
{
  for(auto &row : m_cache)
  {
    for(auto &col : row)
    {
      for(auto &instance : col)
      {
        (*_function)();
      }
    }
  }
}

template<class T>
template<class U>
void CacheStructure<T>::forEachElement(void (*_function)(U), U _parameter)
{
  for(auto &row : m_cache)
  {
    for(auto &col : row)
    {
      for(auto &instance : col)
      {
        (*_function)(_parameter);
      }
    }
  }
}

template<class T>
template<class U, class V>
V CacheStructure<T>::forEachElement(V (*_function)(U), U _parameter)
{
  for(auto &row : m_cache)
  {
    for(auto &col : row)
    {
      for(auto &instance : col)
      {
        return (*_function)(_parameter);
      }
    }
  }
}
