//----------------------------------------------------------------------------------------------------------------------
/// @file Camera.cpp
/// @brief implementation file for Camera struct
//----------------------------------------------------------------------------------------------------------------------

#include "Camera.h"

Camera::Camera()
{
  reset();
}

void Camera::reset()
{
  m_from = {0,40,50};
  m_to = {0,10,0};
  m_up = {0,1,0};
  m_axis = {0,1,0};
}