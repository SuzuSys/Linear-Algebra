#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <time.h>

bool get_data(std::vector<std::vector<double>>& mat, const std::string& file_name);

int main() {
  clock_t start = clock();
  const std::string file_name = "data.csv";
  std::vector<std::vector<double>> mat;
  if (get_data(mat, file_name)) return 1;
  const int N = mat.size();
  double determinant = 1;
  for (int c = 0; c < N; ++c) {
    double pivot = mat[c][c];
    if (pivot == 0) {
      for (int i = c+1; i < N; ++i) {
        if (mat[i][c] == 0) continue;
        pivot = mat[i][c];
        mat[i].swap(mat[c]);
        determinant *= -1;
        break;
      }
      if (pivot == 0) {
        determinant = 0;
        break;
      }
    }
    determinant *= pivot;
    for (int i = c+1; i < N; ++i) {
      double numerator = mat[i][c] / pivot;
      for (int j = c+1; j < N; ++j) {
        mat[i][j] -= mat[c][j] * numerator;
      }
    }
  }
  std::cout << determinant << std::endl;
  clock_t end = clock();
  std::cout << end - start << std::endl;
  return 0;
}

bool get_data(std::vector<std::vector<double>>& mat, const std::string& file_name) {
  std::ifstream data_file (file_name);
  if (!data_file.is_open()) return true;
  int n;
  data_file >> std::dec >> n;
  mat.reserve(n*n);
  mat = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));
  for (std::vector<double>& mat_row: mat) {
    for (double& x: mat_row) {
      data_file >> std::dec >> x;
    }
  }
  return false;
}