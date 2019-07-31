//----------------------------------------------------------------------------------------------------------------------
/// @file Instance.h
/// @author Ben Carey
/// @version 1.0
/// @date 30/07/19
//----------------------------------------------------------------------------------------------------------------------

#ifndef CACHESTRUCTURE_H_
#define CACHESTRUCTURE_H_

#include <vector>
#include <memory>
#include <ngl/AbstractVAO.h>


//----------------------------------------------------------------------------------------------------------------------
/// @class CacheStructure
/// @brief this class makes it easier to store the nesting of a cache structure
//----------------------------------------------------------------------------------------------------------------------

template<class T>
class CacheStructure
{

public:

  CacheStructure() = default;
  ~CacheStructure() = default;

  std::vector<std::vector<std::vector<T>>> m_cache = {};

  void resizeCache(size_t _numBranches, size_t _numGenerations);
  template<class U>
  void resizeCache(CacheStructure<U> &_otherCacheStructure);

  size_t numInstancesAt(size_t _id, size_t _age);

  T* getElement(size_t _id, size_t _age, size_t _innerIndex);
  void setElement(size_t _id, size_t _age, size_t _innerIndex, T& _value);
  T* getLastElementAt(size_t _id, size_t _age);
  void pushBackElement(size_t _id, size_t _age, T& _value);

  template<class functor>
  void forEachElement(functor _function);
};

//----------------------------------------------------------------------------------------------------------------------
///specialization
//----------------------------------------------------------------------------------------------------------------------

template<>
class CacheStructure<std::unique_ptr<ngl::AbstractVAO>>
{

public:

  CacheStructure() = default;

  //delete copy ctors so we don't copy unique_ptr
  CacheStructure(const CacheStructure&) = delete;
  CacheStructure& operator=(const CacheStructure&) = delete;

  ~CacheStructure() = default;

  std::vector<std::vector<std::vector<std::unique_ptr<ngl::AbstractVAO>>>> m_cache = {};

  void resizeCache(size_t _numBranches, size_t _numGenerations);
  template<class U>
  void resizeCache(CacheStructure<U> &_otherCacheStructure);

  size_t numInstancesAt(size_t _id, size_t _age);

  std::unique_ptr<ngl::AbstractVAO>* getElement(size_t _id, size_t _age, size_t _innerIndex);
  void setElement(size_t _id, size_t _age, size_t _innerIndex, std::unique_ptr<ngl::AbstractVAO>& _value);
  std::unique_ptr<ngl::AbstractVAO>* getLastElementAt(size_t _id, size_t _age);
  void pushBackElement(size_t _id, size_t _age, std::unique_ptr<ngl::AbstractVAO>& _value);

  template<class functor>
  void forEachElement(functor _function);
};

//----------------------------------------------------------------------------------------------------------------------
///note that because this is a template class, all definitions need to be in the header file
//----------------------------------------------------------------------------------------------------------------------

template <class T>
void CacheStructure<T>::resizeCache(size_t _numBranches, size_t _numGenerations)
{
  m_cache = {};
  m_cache.resize(_numBranches,{});
  for(auto &vec : m_cache)
  {
    vec.resize(_numGenerations+1,{});
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
size_t CacheStructure<T>::numInstancesAt(size_t _id, size_t _age)
{
  return m_cache[_id][_age].size();
}

template <class T>
T* CacheStructure<T>::getElement(size_t _id, size_t _age, size_t _innerIndex)
{
  return &m_cache[_id][_age][_innerIndex];
}

template <class T>
void CacheStructure<T>::setElement(size_t _id, size_t _age, size_t _innerIndex, T& _value)
{
  m_cache[_id][_age][_innerIndex] = _value;
}

template <class T>
T* CacheStructure<T>::getLastElementAt(size_t _id, size_t _age)
{
  return &m_cache[_id][_age].back();
}

template <class T>
void CacheStructure<T>::pushBackElement(size_t _id, size_t _age, T& _value)
{
  m_cache[_id][_age].push_back(_value);
}

template<class T>
template<class functor>
void CacheStructure<T>::forEachElement(functor _function)
{
  for(size_t id=0; id<m_cache.size(); id++)
  {
    for(size_t age=0; age<m_cache[id].size(); age++)
    {
      for(size_t innerIndex=0; innerIndex<m_cache[id][age].size(); innerIndex++)
      {
        _function(m_cache[id][age][innerIndex], id, age, innerIndex);
      }
    }
  }
}


#endif //CACHESTRUCTURE_H_
