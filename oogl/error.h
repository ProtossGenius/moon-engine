#pragma once
#include <exception>
#include <string>
namespace oogl {
class error : std::exception {
  public:
    error(int errNo, const std::string &reason)
        : m_errNo(errNo) {
        m_what =
            "oogl_error: " + std::to_string(m_errNo) + ", reason = " + reason;
    }
    const char *what() const noexcept override { return m_what.c_str(); }
    int         errNo() { return m_errNo; }
    int         errNo() const { return m_errNo; }

  private:
    int         m_errNo;
    std::string m_what;
};

enum ErrorEnum {
    ErrInit = 1,
};
} // namespace oogl
