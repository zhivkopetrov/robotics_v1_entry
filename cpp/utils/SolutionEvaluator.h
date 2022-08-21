#ifndef SOLUTIONEVALUATOR_H_
#define SOLUTIONEVALUATOR_H_

#include <cstdint>
#include <vector>

template <typename T>
class SolutionEvaluator {
public:
  SolutionEvaluator() = delete;

  static int32_t compare(const std::vector<T> &computed,
                         const std::vector<T> &predefined) {
    const size_t size = computed.size();
    if (size != predefined.size()) {
      std::cout << "Computed size: " << size << " vs Predefined size: "
                << predefined.size() << " mismatch" << std::endl;
      return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
      if (computed[i] == predefined[i]) {
        continue;
      }

      std::cout << "Computed size: vs Predefined mismatch found at imageIdx: "
                << i << "\nTerminating future comparisons" << std::endl;
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }
};

#endif /* SOLUTIONEVALUATOR_H_ */
