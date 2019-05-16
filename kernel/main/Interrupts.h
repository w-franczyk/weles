#pragma once

class Interrupts
{
public:
  Interrupts() = default;
  bool init();

private:
  initPic();
};
