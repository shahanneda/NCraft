#include <Vec3f.h>

Vec3f::Vec3f(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

std::vector<float> Vec3f::UnPackArray(std::vector<Vec3f> arr)
{
  std::vector<float> points(arr.size() * 3);
  int i = 0;
  for (auto vert : arr)
  {
    points[i] = vert.x;
    points[i + 1] = vert.y;
    points[i + 2] = vert.z;
    i += 3;
  }

  return points;
}
