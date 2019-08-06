#pragma once

namespace weles
{

void getAbsolutePath(const char* relativePath, char* outPath);
const char* getCurrentPath();
void setCurrentPath(const char* path);

} // namespace weles
