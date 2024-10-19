#include <iostream>
#include <cmath>

using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace Eigen;

// This program demonstrates the use of the Eigen geometry module

int main(int argc, char **argv) {

  // The Eigen/Geometry module provides various representations of rotations and translations
  // 3D rotation matrices directly using Matrix3d or Matrix3f.
  Matrix3d rotation_matrix = Matrix3d::Identity();
  // Rotation vectors use AngleAxis, which is not directly a matrix at the bottom, but the operations can be treated as matrices (because of the overloaded operators).
  AngleAxisd rotation_vector(M_PI / 4, Vector3d(0, 0, 1));     //Rotate 45 degrees along the Z-axis
  cout.precision(3);
  cout << "rotation matrix =\n" << rotation_vector.matrix() << endl;   //Use matrix() to convert to a matrix.
  // 也可以直接赋值
  rotation_matrix = rotation_vector.toRotationMatrix();
  // Coordinate transformations are possible with AngleAxis.
  Vector3d v(1, 0, 0);
  Vector3d v_rotated = rotation_vector * v;
  cout << "(1,0,0) after rotation (by angle axis) = " << v_rotated.transpose() << endl;
  // Or use the rotation matrix
  v_rotated = rotation_matrix * v;
  cout << "(1,0,0) after rotation (by matrix) = " << v_rotated.transpose() << endl;

  // Euler angles: You can convert rotation matrices directly to Euler angles.
  Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0); // ZYX order, i.e. yaw-pitch-roll order
  cout << "yaw pitch roll = " << euler_angles.transpose() << endl;

  // 欧氏变换矩阵使用 Eigen::Isometry
  Isometry3d T = Isometry3d::Identity();                // Although it's called 3d, it's essentially a 4*4 matrix.
  T.rotate(rotation_vector);                                     // Rotation according to rotation_vector
  T.pretranslate(Vector3d(1, 3, 4));                     // Set the translation vector to (1,3,4)
  cout << "Transform matrix = \n" << T.matrix() << endl;

  //Coordinate transformations with transformation matrices
  Vector3d v_transformed = T * v;                              // Equivalent to R*v+t
  cout << "v tranformed = " << v_transformed.transpose() << endl;

  // quaternion
  // It is possible to assign AngleAxis directly to quaternions and vice versa
  Quaterniond q = Quaterniond(rotation_vector);
  cout << "quaternion from rotation vector = " << q.coeffs().transpose()
       << endl;   // Note that the order of coeffs is (x,y,z,w), with w being the real part and the first three being the imaginary parts
  // You can also assign a rotation matrix to it
  q = Quaterniond(rotation_matrix);
  cout << "quaternion from rotation matrix = " << q.coeffs().transpose() << endl;
  // Rotate a vector using quaternions, just use overloaded multiplication
  v_rotated = q * v; // Note that the math is qvq^{-1}
  cout << "(1,0,0) after rotation = " << v_rotated.transpose() << endl;
  // Expressed in terms of regular vector multiplication, this should be computed as follows
  cout << "should be equal to " << (q * Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose() << endl;

  return 0;
}
