#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

void get_data(std::vector<std::vector<double>>& mat, const std::string& file_name);

int main() {
  const std::string file_name = "data.csv";
  std::vector<std::vector<double>> mat;
  get_data(mat, file_name);
  const int N = mat.size();
  int N_col = N;
  for (const std::vector<double>& mat_row : mat) {
    if (mat_row[N] != 0) {
      N_col++;
      break;
    }
  }
  std::vector<int> skip_col;
  skip_col.reserve(N);
  for (int i = 0, j = 0; j < N; ++j) {
    double pivot = 0;
    for (int i2 = i; i2 < N; ++i2) {
      if (mat[i2][j] == 0) continue;
      pivot = mat[i2][j];
      mat[i].swap(mat[i2]);
      break;
    }
    if (pivot == 0) {
      skip_col.push_back(j);
      continue;
    }
    for (int j2 = j+1; j2 < N_col; ++j2) {
      mat[i][j2] /= pivot;
    }
    mat[i].swap(mat[0]);
    for (int i2 = 1; i2 < N; ++i2) {
      for (int j2 = j+1; j2 < N_col; ++j2) {
        mat[i2][j2] -= mat[0][j2] * mat[i2][j];
      }
    }
    mat[i].swap(mat[0]);
    ++i;
  }
  int coe_mat_rank = N - skip_col.size();
  if (N_col != N) {
    // 非斉次
    if (coe_mat_rank == N) {
      // 1つの解
      std::cout << "非斉次，ただ１つの解を持つ．" << std::endl;
      std::cout << "解:" << std::endl;
      for (const std::vector<double> mat_row : mat) {
        std::cout << mat_row[N] << " ";
      }
      std::cout << std::endl;
    }
    else {
      int arg_coe_mat_rank = coe_mat_rank;
      for (int i = N-1; i > coe_mat_rank-1; --i) {
        if (mat[i][N] != 0) {
          arg_coe_mat_rank = i+1;
          break;
        }
      }
      if (arg_coe_mat_rank == coe_mat_rank) {
        // 無数の解
        std::cout << "非斉次，無数の解を持つ．" << std::endl;
        std::cout << "解の自由度: " << skip_col.size() << std::endl;
        std::cout << "未知数:" << std::endl;
        skip_col.push_back(N);
        int skip_pre = -1;
        for (const int& skip_val : skip_col) {
          for (int i = skip_pre+1; i < skip_val; ++i) {
            std::cout << i+1 << " ";
          }
          skip_pre = skip_val;
        }
        skip_col.pop_back();
        std::cout << std::endl << "に対する解は，別の未知数と定数：" << std::endl;
        for (const int& skip_variable : skip_col) {
          std::cout << skip_variable+1 << " ";
        }
        std::cout << "1(const.)" << std::endl;
        std::cout << "と，次の列ベクトルの線形結合で表せる．" << std::endl;
        for (const int& skip_val : skip_col) {
          for (int i = 0; i < coe_mat_rank; ++i) {
            std::cout << -mat[i][skip_val] << " ";
          }
          std::cout << std::endl;
        }
        for (int i = 0; i < coe_mat_rank; ++i) {
          std::cout << mat[i][N] << " ";
        }
        std::cout << std::endl;
      }
      else {
        // 解なし
        for (int i = coe_mat_rank-1; i < N; ++i) {
          std::cout << "解なし" << std::endl;
          std::cout << "係数行列のrank: " << coe_mat_rank << "，拡大係数行列のrank: " << arg_coe_mat_rank << std::endl;
        }
      }
    }
  }
  else {
    // 斉次
    if (coe_mat_rank == N) {
      // 1つの解(0のみ)
      std::cout << "斉次，自明解のみを持つ．" << std::endl;
    }
    else {
      // 無数の解
      std::cout << "斉次，非自明解を持つ．" << std::endl;
      std::cout << "解の自由度: " << skip_col.size() << std::endl;
      std::cout << "未知数：" << std::endl;
      skip_col.push_back(N);
      int skip_pre = -1;
      for (const int& skip_val : skip_col) {
        for (int i = skip_pre+1; i < skip_val; ++i) {
          std::cout << i+1 << " ";
        }
        skip_pre = skip_val;
      }
      skip_col.pop_back();
      std::cout << std::endl << "に対する解は，別の未知数：" << std::endl;
      for (const int& skip_variable : skip_col) {
        std::cout << skip_variable+1 << " ";
      }
      std::cout << std::endl;
      std::cout << "と，次の列ベクトルの線形結合で表せる．" << std::endl;
      for (const int& skip_val : skip_col) {
        for (int i = 0; i < coe_mat_rank; ++i) {
          std::cout << -mat[i][skip_val] << " ";
        }
        std::cout << std::endl;
      }
    }
  }
}

void get_data(std::vector<std::vector<double>>& mat, const std::string& file_name) {
  std::ifstream data_file (file_name);
  int n;
  data_file >> std::dec >> n;
  mat.reserve(n*(n+1));
  mat = std::vector<std::vector<double>>(n, std::vector<double>(n+1, 0));
  for (std::vector<double>& mat_row: mat) {
    for (double& x: mat_row) {
      data_file >> std::dec >> x;
    }
  }
}