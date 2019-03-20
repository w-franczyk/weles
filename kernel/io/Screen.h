#pragma once

class Screen
{
public:
  void print(const char* s, unsigned size)
  {
    for (unsigned i = 0; i < size; ++i)
    {
      *(m_writeBuff++) = s[i];
      *(m_writeBuff++) = 0xb1;
    }
  }

private:
  char* m_writeBuff = reinterpret_cast<char*>(0xb8000);
};
