//James Rogers Mar 2022 (c) Plymouth University
#include<iostream>
#include<fstream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//a drawing function that can draw a line based on rho and theta values.
//useful for drawing lines from the hough line detector.
void lineRT(Mat &Src, Vec2f L, Scalar color, int thickness){
    Point pt1, pt2;
    double a = cos(static_cast<double>(L[1]));
    double b = sin(static_cast<double>(L[1]));
    double x0 = a*static_cast<double>(L[0]);
    double y0 = b*static_cast<double>(L[0]);
    pt1.x = cvRound(x0 + 10000*(-b));
    pt1.y = cvRound(y0 + 10000*(a));
    pt2.x = cvRound(x0 - 10000*(-b));
    pt2.y = cvRound(y0 - 10000*(a));
    line(Src, pt1, pt2, color, thickness, LINE_AA);
}

int main()
{

    //Open video file
    VideoCapture CarVideo("../Task5/DashCam.mp4");
    if(!CarVideo.isOpened()){
        cout<<"Error opening video"<<endl;
        return -1;
    }

    //main program loop
    while(true){

        //open the next frame from the video file, or exit the loop if its the end
        Mat Frame;
        CarVideo.read(Frame);
        if(Frame.empty()){
            break;
        }

        //==========================Your code goes here==========================
        //Point start(0,0), end(0,BlurFrame.cols);
        Mat CanFrame, GreyFrame, BlurFrame;
        int lowerThreshold = 50, upperThreshold = 100;
        double rhoRes = 1;
        double thetaRes = M_PI/180;
        int HoughThreshold = 212;
        cvtColor(Frame, GreyFrame,COLOR_BGR2GRAY);  //greyscale, get rid of useless colour info
        blur(GreyFrame,BlurFrame, Size(3,3));
        Point start(0,0), end(BlurFrame.cols,350);
        rectangle(BlurFrame,start,end, Scalar(255,255,255), -1);
        Canny(BlurFrame, CanFrame, lowerThreshold, upperThreshold);
        vector<Vec2f> lines;
        vector<Vec4f> lines2;
        HoughLines(CanFrame, lines, rhoRes, thetaRes, HoughThreshold, 0 ,0 );
        cout << "cheese" << endl;
        for (int i =0;i < lines.size(); i++) {
            //angle check
            if((lines[i][0]<-230) ||(lines[i][0]>600)){
           lineRT(Frame,lines[i],Scalar(255,0,0),1);
        }
        }



















        //display frame
        imshow("Video", Frame);
        //imshow("can",CanFrame);
        waitKey(10);
    }
}



