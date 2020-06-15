/**
 * File              : cpu_conv.cc
 * Author            : Xianglan Piao <xianglan0502@gmail.com>
 * Date              : 2020.06.15
 * Last Modified Date: 2020.06.15
 * Last Modified By  : Xianglan Piao <xianglan0502@gmail.com>
 */

/* NOTE: convolutional output size */
/* output_size = (intput_size + 2 * padding - kernel_size) / stride + 1 */
/* input_index = output_index * stride - padding + kernel_index */

#include <iostream>
#include <vector>

using Array1D = std::vector<float>;
using Array2D = std::vector<Array1D>;

class Functional {
 public:
  Array1D conv1d(Array1D& input, Array1D& kernel, const unsigned int stride = 1,
                 const unsigned int padding = 0);
  Array2D conv2d(Array2D& input, Array2D& kernel, const unsigned int stride = 1,
                 const unsigned int padding = 0);
};

Array1D Functional::conv1d(Array1D& input, Array1D& kernel,
                           const unsigned int stride,
                           const unsigned int padding) {
  const unsigned int size =
      (input.size() + 2 * padding - kernel.size()) / stride + 1;
  Array1D output(size, 0);

  for (int i = 0; i < output.size(); i += 1) {
    for (int k = 0; k < kernel.size(); k++) {
      int col = i * stride - padding + k;
      if (col >= 0 && col < input.size()) {
        output[i] += input[col] * kernel[k];
      }
    }
  }

  return output;
}

Array2D Functional::conv2d(Array2D& input, Array2D& kernel,
                           const unsigned int stride,
                           const unsigned int padding) {
  const unsigned int row_size =
      (input.size() + 2 * padding - kernel.size()) / stride + 1;
  const unsigned int col_size =
      (input[0].size() + 2 * padding - kernel.size()) / stride + 1;
  Array2D output(row_size, Array1D(col_size, 0));

  for (int i = 0; i < output.size(); i++) {
    for (int j = 0; j < output[i].size(); j++) {
      for (int m = 0; m < kernel.size(); m++) {
        for (int n = 0; n < kernel.size(); n++) {
          int row = (i * stride - padding) + m;
          int col = (j * stride - padding) + n;
          if (row >= 0 && row < input.size() && col >= 0 &&
              col < input[i].size()) {
            output[i][j] += input[row][col] * kernel[m][n];
          }
        }
      }
    }
  }

  return output;
}

void print1d(const Array1D& data) {
  for (auto it : data) {
    std::cout << it << ", ";
  }
  std::cout << std::endl;
}

void print2d(const Array2D& data) {
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data[i].size(); j++) {
      std::cout << data[i][j] << ", ";
    }
    std::cout << std::endl;
  }
}

int main(void) {
  Functional F;
  const unsigned int input_size = 8;
  const unsigned int kernel_size = 5;
  const unsigned int stride = 2;
  const unsigned int padding = 2;

  //// 1. 1D array convolution
  std::cout << "\n--- 1D convolution ---\n" << std::endl;
  Array1D input1(input_size, 1);
  Array1D kernel1(kernel_size, 2);

  std::cout << "input: " << std::endl;
  print1d(input1);
  std::cout << std::endl;

  std::cout << "kernel: " << std::endl;
  print1d(kernel1);
  std::cout << std::endl;

  std::cout << "output: " << std::endl;
  auto output1 = F.conv1d(input1, kernel1, stride, padding);
  print1d(output1);
  std::cout << std::endl;

  //// 2. 2D array convolution
  std::cout << "\n--- 2D convolution ---\n" << std::endl;
  Array2D input2(input_size, Array1D(input_size, 1));
  Array2D kernel2(kernel_size, Array1D(kernel_size, 2));

  std::cout << "input: " << std::endl;
  print2d(input2);
  std::cout << std::endl;

  std::cout << "kernel: " << std::endl;
  print2d(kernel2);
  std::cout << std::endl;

  std::cout << "output: " << std::endl;
  auto output2 = F.conv2d(input2, kernel2, stride, padding);
  print2d(output2);
  std::cout << std::endl;

  return 0;
}
