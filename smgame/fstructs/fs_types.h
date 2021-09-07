#pragma once
#include "fs_file.h"
#include "smgame/errors.h"
#include "smgame/nil.h"
#include <iostream>
#include <string>

namespace smgame {
template <typename Type> class FsType {
  public:
    FsType()
        : m_pos(new int(0)) {}
    FsType(int *pos)
        : m_pos(pos) {}

  public:
    const Type &getVal();

  private:
    int *m_pos;
};
} // namespace smgame