#include "InstanceCacheVAO.h"
#include <iostream>
namespace ngl
{
  InstanceCacheVAO::~InstanceCacheVAO()
  {
    removeVAO();
  }

  void InstanceCacheVAO::draw() const
  {
    if(m_allocated == false)
    {
      msg->addWarning("Warning trying to draw an unallocated VOA");
    }
    if(m_bound == false)
    {
      msg->addWarning("Warning trying to draw an unbound VOA");
    }
    glDrawElementsInstanced(m_mode,
                            static_cast<GLsizei>(m_indicesCount),
                            m_indexType,
                            static_cast<GLvoid *>(nullptr),
                            m_instanceCount);
  }

  void InstanceCacheVAO::removeVAO()
  {
    if(m_bound == true)
    {
      unbind();
    }
    if( m_allocated ==true)
    {
        glDeleteBuffers(1,&m_buffer);
        glDeleteBuffers(1,&m_idxBuffer);
    }
    glDeleteVertexArrays(1,&m_id);
    m_allocated=false;
    }


  //void SimpleIndexVAO::setData(size_t _size, const GLfloat &_data, unsigned int _indexSize, const GLvoid *_indexData, GLenum _indexType, GLenum _mode  )
  void InstanceCacheVAO::setData(const AbstractVAO::VertexData &_data)
  {
    const VertexData &data = static_cast<const VertexData &>(_data);
    if(m_bound == false)
    {
      msg->addWarning("trying to set VOA data when unbound");
    }
    if( m_allocated ==true)
    {
        glDeleteBuffers(1,&m_buffer);
    }

//    GLuint vboID;
    glGenBuffers(1, &m_buffer);

//    GLuint iboID;
    glGenBuffers(1, &m_idxBuffer);

    // now we will bind an array buffer to the first one and load the data for the verts
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(data.m_size), &data.m_data, data.m_mode);
    // we need to determine the size of the data type before we set it
    // in default to a ushort
    int size=sizeof(GLushort);
    switch(data.m_indexType)
    {
      case GL_UNSIGNED_INT   : size=sizeof(GLuint);   break;
      case GL_UNSIGNED_SHORT : size=sizeof(GLushort); break;
      case GL_UNSIGNED_BYTE  : size=sizeof(GLubyte);  break;
      default : msg->addWarning("wrong data type send for index value"); break;
    }
    // now for the indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idxBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.m_indexSize * static_cast<GLsizeiptr>(size), const_cast<GLvoid *>(data.m_indexData),data.m_mode);

    m_allocated=true;
    m_indexType=data.m_indexType;

    m_instanceCount = data.m_instanceCount;
  }

  Real * InstanceCacheVAO::mapBuffer(unsigned int _index, GLenum _accessMode)
  {
    Real *ptr=nullptr;
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    ptr = static_cast<Real *>(glMapBuffer(GL_ARRAY_BUFFER, _accessMode));
    return ptr;
  }

}
