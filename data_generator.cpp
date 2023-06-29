#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cmath>

int main() {
  const std::string file_name = "data.csv";
  const unsigned int N = 1000;
  const unsigned int seed = 0;
  const double min = -std::pow(2, -4);
  const double max = std::pow(2, -4);

  std::ofstream data_file (file_name);
  if (!data_file.is_open()) return 1;
  data_file << N << std::endl;

  std::mt19937 engine(seed);
  std::uniform_real_distribution<double> dist(min, max);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      data_file << dist(engine) << " ";
    }
    data_file << std::endl;
  }
  return 0;
}