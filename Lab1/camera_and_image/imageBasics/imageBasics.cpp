#include <iostream>
#include <chrono>

using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv) {
  // Load the image specified by argv[1]
  cv::Mat image;
  image = cv::imread(argv[1]); //The cv::imread function loads an image from the specified path

  // Check if the image file was loaded correctly
  if (image.data == nullptr) { //Data not found, the file may not exist
    cerr << "Data" << argv[1] << "not found." << endl;
    return 0;
  }

  // The file was successfully loaded. Let's start by printing some basic information
  // cout << "width: " << image.cols << ",height: " << image.rows << ",channel: " << image.channels() << endl;
  cv::imshow("image", image);      // Display the image using cv::imshow
  cv::waitKey(0);                  // Pause the program and wait for input.

  // Determine the type of image
  if (image.type() != CV_8UC1 && image.type() != CV_8UC3) {
    // Image type does not meet the requirements
    cout << "Please input a color or grayscale image." << endl;
    return 0;
  }

  // Iterate over the image, please note that the following iterations can also be used to access random pixels
  // Using std::chrono to time the algorithm
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  for (size_t y = 0; y < image.rows; y++) {
    // Get the row pointer of the image with cv::Mat::ptr
    unsigned char *row_ptr = image.ptr<unsigned char>(y);  // row_ptr is the header pointer to row y
    for (size_t x = 0; x < image.cols; x++) {
      // Access pixels at x,y
      unsigned char *data_ptr = &row_ptr[x * image.channels()]; // data_ptr points to the pixel data to be accessed
      // Output each channel of the pixel, only one channel if it's a grayscale image.
      for (int c = 0; c != image.channels(); c++) {
        unsigned char data = data_ptr[c]; // data is the value of the cth channel of I(x,y)
      }
    }
  }
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast < chrono::duration < double >> (t2 - t1);
  // cout << "Time spent traversing the image:"" << time_used.count() << " seconds." << endl.

  // A copy of cv::Mat
  // Direct assignment does not copy data
  cv::Mat image_another = image;
  // Changing image_another will cause the image to change.
  image_another(cv::Rect(0, 0, 100, 100)).setTo(0); // Zero the 100*100 block in the upper left corner
  cv::imshow("image", image);
  cv::waitKey(0);

  // Using the clone function to copy data
  cv::Mat image_clone = image.clone();
  image_clone(cv::Rect(0, 0, 100, 100)).setTo(255);
  cv::imshow("image", image);
  cv::imshow("image_clone", image_clone);
  cv::waitKey(0);

  // For the image there are many basic operations, such as cut, rotate, zoom, etc., 
  // limited to space will not be introduced one by one, 
  // please refer to the official OpenCV documentation to query the call method of each function.
  cv::destroyAllWindows();
  return 0;
}
