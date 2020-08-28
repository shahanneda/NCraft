#include<vector>

class Vec3f{
  public:
    float x;
    float y;
    float z;
    Vec3f(float x,float y,float z);

    static std::vector<float> UnPackArray(std::vector<Vec3f> arr) ;

};
