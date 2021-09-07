#pragma once
#include <string>
namespace smgame {
class Serializable {
    virtual Serializable &parseMsg(const std::string &) = 0; // return itself.
    virtual std::string   asMessage() const             = 0;
};
} // namespace smgame