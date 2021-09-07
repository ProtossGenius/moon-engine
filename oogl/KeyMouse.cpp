#include "KeyMouse.h"
namespace oogl {
class NilKeyMouse : public KeyMouseItf {
  public:
    void MouseButton(int button, int action, int mods) override {}
    void KeyBoards(int key, int scancode, int action, int mode) override {}
    void MouseScroll(double offset) override {}
    void Update() override {}
};
} // namespace oogl

namespace smgame {
template <> std::shared_ptr<oogl::KeyMouseItf> nil<oogl::KeyMouseItf>() {
    static std::shared_ptr<oogl::KeyMouseItf> instance(new oogl::NilKeyMouse());
    return instance;
}
} // namespace smgame