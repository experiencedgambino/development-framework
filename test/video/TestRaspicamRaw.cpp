/**
*/
#include <ctime>
#include <fstream>
#include <iostream>
#include <raspicam/raspicam.h>
#include <thread>
#include "opencv2/videoio.hpp"
#include <opencv2/imgcodecs.hpp>
using namespace std;
 
int main ( int argc,char **argv ) {
	raspicam::RaspiCam Camera; //Camera object
	//Open camera 
	cout<<"Opening Camera..."<<endl;
	if ( !Camera.open()) {cerr<<"Error opening camera"<<endl;return -1;}
	//wait a while until camera stabilizes
	cout<<"Sleeping for 3 secs"<<endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	//capture
	Camera.grab();
	//allocate memory
	unsigned char *data=new unsigned char[  Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
	//extract the image in rgb format
	// Camera.retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );//get camera image
	Camera.retrieve ( data);//get camera image
  std::cout << "Size of data is " << Camera.getImageTypeSize (raspicam::RASPICAM_FORMAT_RGB) << std::endl;
	//save
	std::ofstream outFile ( "raspicam_image.ppm",std::ios::binary );
	outFile<<"P6\n"<<Camera.getWidth() <<" "<<Camera.getHeight() <<" 255\n";
	outFile.write ( ( char* ) data, Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
	cout<<"Image saved at raspicam_image.ppm"<<endl;

  cv::Mat mat(Camera.getHeight(), Camera.getWidth(), CV_8UC3);

  std::memcpy(mat.data, data, Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ));
  cv::imwrite("image.png", mat);

  std::cout << mat.channels() << std::endl;

	//free resrources    
	delete data;
	return 0;
}
