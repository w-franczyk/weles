#pragma once

const char* getCurrentPath()
{
  extern char* sigCurrentPath;
  return sigCurrentPath;
}
