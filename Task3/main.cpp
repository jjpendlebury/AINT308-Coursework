//James Rogers Jan 2021 (c) Plymouth University
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{

    //Path to image file
    string Path = "../Task3/PCB Images/";

    //loop through component images
    for(int n=0; n<10; ++n){

        //read PCB and component images
        Mat PCB = imread(Path+"PCB.png");
        Mat Component = imread(Path+"Component"+to_string(n)+".png");

        //================Your code goes here=====================
        Mat matchImage;
        matchTemplate( PCB, Component, matchImage, TM_SQDIFF_NORMED );

        double minval, maxval;
        Point minloc, maxloc, matchloc;
        minMaxLoc(matchImage, &minval, &maxval, &minloc, &maxloc);
        matchloc = minloc;
        rectangle(matchImage, matchloc, Point( matchloc.x + Component.cols, matchloc.y + Component.rows), Scalar(0,0,255), 2, 8, 0);
        rectangle(PCB, matchloc, Point( matchloc.x + Component.cols, matchloc.y + Component.rows), Scalar(0,0,255), 2, 8, 0);


        cout << matchloc << endl;
        cout << minval << endl <<endl;
        if(minval >0.01){
            cout << "Component number " << n<<" not found" << endl;
        }















        //display the results untill x is pressed
        while(waitKey(10)!='x'){
            imshow("Target", Component);
            imshow("PCB", PCB);
            imshow("Result",matchImage);
        }

    }

}
