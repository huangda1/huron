#include <stdint.h>

class CacheLine{
private:
  uint16_t bitmap;
public:
  CacheLine()
  {
    bitmap = 0x7fff;
  }
  bool isInstrumented()
  {
    if(bitmap >> 15)
    {
      return true;
    }
    return false;
  }
  bool store(int threadId)
  {
    if(this->isInstrumented())
    {
      return true;
    }
    else if (bitmap == 0x7fff)
    {
      bitmap = (uint16_t) threadId;
    }
    else if(bitmap == (uint16_t)threadId)
    {
      //do nothing
    }
    else
    {
      bitmap = bitmap | (1<<15);
      return true;
    }
    return false;
  }
  bool load(int threadId)
  {
    if(this->isInstrumented())
    {
      return true;
    }
    else if(bitmap == 0x7fff)
    {
      //do nothing
    }
    else if (bitmap != (uint16_t) threadId)
    {
      bitmap = bitmap | (1<<15);
      return true;
    }
    return false;
  }
};
