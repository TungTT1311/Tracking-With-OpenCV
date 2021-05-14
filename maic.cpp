#include <opencv4/opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
#include <iostream>
#include <cstring>
using namespace std;
using namespace cv;
int main( int argc, char** argv ){
  // show help
  // if(argc<2){
  //   cout<<
  //     " Usage: tracker <video_name>\n"
  //     " examples:\n"
  //     " example_tracking_kcf Bolt/img/%04d.jpg\n"
  //     " example_tracking_kcf faceocc2.webm\n"
  //     << endl;
  //   return 0;
  // }
  // declares all required variables
  Rect roi;
  Mat frame;
  VideoCapture m_pVideoCapture;
  // create a tracker object

  Ptr<Tracker> tracker = TrackerGOTURN::create();
  // set input video
  int deviceID = 0;             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
	// open selected camera using selected API
	m_pVideoCapture.open(deviceID, apiID);
	// check if we succeeded
    if (!m_pVideoCapture.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
	m_pVideoCapture.read(frame);

  // get bounding box
  roi=selectROI("tracker",frame);
  //quit if ROI was not selected
  if(roi.width==0 || roi.height==0)
    return 0;
  // initialize the tracker
  tracker->init(frame,roi);
  // perform the tracking process
  printf("Start the tracking process, press ESC to quit.\n");
  for ( ;; ){
    // get frame from the video
    m_pVideoCapture.read(frame);
    // stop the program if no more images
    if(frame.rows==0 || frame.cols==0)
      break;
    // update the tracking result
    tracker->update(frame,roi);
    // draw the tracked object
    rectangle( frame, roi, Scalar( 255, 0, 0 ), 2, 1 );
    // show image with the tracked object
    imshow("tracker",frame);
    //quit on ESC button
    if(waitKey(1)==27)break;
  }
  return 0;
}
