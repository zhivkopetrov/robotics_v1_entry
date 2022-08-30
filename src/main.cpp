#include "utils/FileParser.h"
#include "utils/Image.h"
#include "utils/SolutionEvaluator.h"
#include "Solution.h"

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char *argv[]) {
  //Use the provided implementation that best suits your needs
//  using Image = PackedImage;
  using Image = StrideImage;

  std::vector<Image> inputImages;
  std::vector<Image> outputImages;
  int32_t err = FileParser<Image>::generateData(inputImages, outputImages);
  if (EXIT_SUCCESS != err) {
    std::cerr << "FileParser::generateData() failed" << std::endl;
    return EXIT_FAILURE;
  }

  Solution solution;
  solution.compute(inputImages);

  err = SolutionEvaluator<Image>::compare(inputImages, outputImages);
  if (EXIT_SUCCESS != err) {
    std::cout << "Solution status - [FAIL]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Solution status - [SUCCESS]" << std::endl;
  return EXIT_SUCCESS;
}

