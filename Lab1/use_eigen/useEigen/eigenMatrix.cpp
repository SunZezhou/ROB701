#include <iostream>

using namespace std;

#include <ctime>
// Eigen Core
#include <Eigen/Core>
// Algebraic operations on dense matrices (inverse, eigenvalues, etc.)
#include <Eigen/Dense>

using namespace Eigen;

#define MATRIX_SIZE 50

/****************************
* This program demonstrates the use of Eigen's basic types.
****************************/

int main(int argc, char **argv) {
  // All vectors and matrices in Eigen are Eigen::Matrix, which is a template class. Its first three parameters are: data type, rows, columns
  // Declare a 2*3 float matrix
  Matrix<float, 2, 3> matrix_23;

  // Meanwhile, Eigen provides a number of built-in types via typedef, but the underlying layer is still Eigen::Matrix
  // For example, Vector3d is essentially Eigen::Matrix<double, 3, 1>, i.e. a 3D vector.
  Vector3d v_3d;
  // smae
  Matrix<float, 3, 1> vd_3d;

  // Matrix3d is essentially Eigen::Matrix<double, 3, 3>.
  Matrix3d matrix_33 = Matrix3d::Zero(); //初始化为零
  // If you are not sure of the matrix size, you can use a dynamically sized matrix
  Matrix<double, Dynamic, Dynamic> matrix_dynamic;
  // simpler
  MatrixXd matrix_x;
  // There are many more of these types, and we won't list them all!

  // Here's how it works for the Eigen formation
  // Input data (initialization)
  matrix_23 << 1, 2, 3, 4, 5, 6;
  // Output
  cout << "matrix 2x3 from 1 to 6: \n" << matrix_23 << endl;

  // Accessing elements of a matrix with ()
  cout << "print matrix 2x3: " << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) cout << matrix_23(i, j) << "\t";
    cout << endl;
  }

  // Multiplication of matrices and vectors (actually still matrices and matrices)
  v_3d << 3, 2, 1;
  vd_3d << 4, 5, 6;

  // But in Eigen you can't mix two different types of matrices, like this is wrong
  // Matrix<double, 2, 1> result_wrong_type = matrix_23 * v_3d;
  // Should be explicitly converted
  Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
  cout << "[1,2,3;4,5,6]*[3,2,1]=" << result.transpose() << endl;

  Matrix<float, 2, 1> result2 = matrix_23 * vd_3d;
  cout << "[1,2,3;4,5,6]*[4,5,6]: " << result2.transpose() << endl;

  // Again, you can't mistake the dimensions of the matrix
  // Try uncommenting the following to see what error Eigen reports
  // Eigen::Matrix<double, 2, 3> result_wrong_dimension = matrix_23.cast<double>() * v_3d;

  // Some matrix operations
  // Instead of demonstrating the four operations, you can just use +-*/.
  matrix_33 = Matrix3d::Random();      // random number matrix
  cout << "random matrix: \n" << matrix_33 << endl;
  cout << "transpose: \n" << matrix_33.transpose() << endl;      // transpose
  cout << "sum: " << matrix_33.sum() << endl;            // sum
  cout << "trace: " << matrix_33.trace() << endl;          // trace
  cout << "times 10: \n" << 10 * matrix_33 << endl;               // times
  cout << "inverse: \n" << matrix_33.inverse() << endl;        // inverse
  cout << "det: " << matrix_33.determinant() << endl;    // determinant

  // Eigen values
  // Real symmetric matrices guarantee successful diagonalization
  SelfAdjointEigenSolver<Matrix3d> eigen_solver(matrix_33.transpose() * matrix_33);
  cout << "Eigen values = \n" << eigen_solver.eigenvalues() << endl;
  cout << "Eigen vectors = \n" << eigen_solver.eigenvectors() << endl;

  // solve the equation
  // We solve the equation matrix_NN * x = v_Nd
  // The size of N is defined in the preceding macro, which is generated by the random number
  // The direct inverse is naturally the most direct, but it is computationally intensive.

  Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN
      = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
  matrix_NN = matrix_NN * matrix_NN.transpose();  // Guaranteed Semi-Positive
  Matrix<double, MATRIX_SIZE, 1> v_Nd = MatrixXd::Random(MATRIX_SIZE, 1);

  clock_t time_stt = clock(); // measure time
  // inverse
  Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
  cout << "time of normal inverse is "
       << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << endl;
  cout << "x = " << x.transpose() << endl;

  // It is usually much faster to find it with a matrix factorization, such as the QR factorization
  time_stt = clock();
  x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
  cout << "time of Qr decomposition is "
       << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << endl;
  cout << "x = " << x.transpose() << endl;

  // For positive definite matrices, the cholesky decomposition can also be used to solve the equation
  time_stt = clock();
  x = matrix_NN.ldlt().solve(v_Nd);
  cout << "time of ldlt decomposition is "
       << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << endl;
  cout << "x = " << x.transpose() << endl;

  return 0;
}