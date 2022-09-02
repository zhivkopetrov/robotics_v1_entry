#ifndef RED_EYE_UTILS_FUNCTION_TRACER
#define RED_EYE_UTILS_FUNCTION_TRACER

#include <chrono>
#include <string>
#include <iostream>

template <typename Ratio>
class FunctionTracer {
public:
  FunctionTracer(std::string_view funcName, std::string_view postfix)
      : mFuncName(funcName), mPostfix(postfix) {
    std::cout << "[" << mFuncName << "] Starting time measurement "
              << std::endl;
  }

  ~FunctionTracer() {
    const int64_t duration = captureDuration();
    std::cout << "[" << mFuncName << "] took: " << duration << ' ' << mPostfix
    << std::endl;
  }

  int64_t captureDuration() const {
    const auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<Ratio>(end - mStart).count();
  }

private:
  const std::chrono::system_clock::time_point mStart =
      std::chrono::system_clock::now();
  std::string mFuncName;
  std::string mPostfix;
};

#endif // RED_EYE_UTILS_FUNCTION_TRACER
