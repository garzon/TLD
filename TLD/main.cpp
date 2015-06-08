//
//  main.cpp
//  TLD
//
//  Created by 陈裕昕 on 11/4/14.
//  Copyright (c) 2014 Fudan. All rights reserved.
//

#include "../main.h"

using namespace std;
using namespace cv;
using namespace _TLD;

void testOnVideo(string filename)
{
    
    VideoController videoController(filename);
    ViewController viewController(&videoController);
    
    videoController.readNextFrame();
    
    Rect rect = viewController.getRect();
    cerr << "Input Rect : " <<  rect << endl;
    
    viewController.refreshCache();
    viewController.drawRect(rect, COLOR_BLUE);
    viewController.showCache();
    waitKey();
    
    TLD tld(videoController.getCurrFrame(), rect);
    
    while(videoController.readNextFrame())
    {
        cerr << "Frame #" << videoController.frameNumber() << endl;
        tld.setNextFrame(videoController.getCurrFrame());
        
        Rect bbTrack;
        TYPE_DETECTOR_RET bbDetect;
        
        clock_t st = clock();
        
        tld.track();
        
        clock_t ed = clock();
        cerr << "Time : " << (double)(ed - st) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
        
        viewController.refreshCache();
        viewController.drawRect(tld.getBB(), COLOR_GREEN, 2);
        viewController.showCache();
        
        cerr << endl;
    }

}


void stabilize()
{
    string dir("/home/cyx/Developments/OpenTLD/_input/06_car/");
    //VideoController videoController(dir, ".jpg");
    VideoController videoController("/Users/Orthocenter/Developments/TLD/4.mov");
    ViewController viewController(&videoController);

    videoController.readNextFrame();

    Rect rect;
    bool drawBBox = true;
    if(drawBBox)
    {
        rect = viewController.getRect();
    }
    else
    {
        string initFilename(dir + "init.txt");
        FILE *fin = fopen(initFilename.c_str(), "r");
        int tlx, tly, brx, bry;
        fscanf(fin, "%d,%d,%d,%d", &tlx, &tly, &brx, &bry);

        rect = Rect(Point2d(tlx, tly), Point2d(brx, bry));
        fclose(fin);
    }

    cerr << "Input Rect : " <<  rect << endl;

    TLD tld(videoController.getCurrFrame(), rect);

    int width = videoController.frameSize().width;
    int height = videoController.frameSize().height;

    Point2i centerOut;
    centerOut.x = width / 2;
    centerOut.y = height / 2;

    while(videoController.readNextFrame())
    {
        tld.setNextFrame(videoController.getCurrFrame());
        int status = tld.track();

        if(status == TLD_TRACK_SUCCESS)
        {
            Point2i centerIn;
            centerIn.x = (tld.getBB().tl().x + tld.getBB().br().x) / 2;
            centerIn.y = (tld.getBB().tl().y + tld.getBB().br().y) / 2;

            Mat output(videoController.frameSize(), CV_8UC3, Scalar::all(0));

            int dx = centerOut.x - centerIn.x;
            int dy = centerOut.y - centerIn.y;

            Point2i inTl(max(0, -dx), max(0, -dy));
            Point2i inBr(min(width, width - dx), min(height, height - dy));
            Point2i outTl(max(0, dx), max(0, dy));
            Point2i outBr(min(width, width + dx), min(height, height + dy));
            Rect ROIIn(inTl, inBr);
            Rect ROIOut(outTl, outBr);

            videoController.getCurrFrame()(ROIIn).copyTo(output(ROIOut));
            imshow("Stabilize", output);
            waitKey(1);
        }
        else
        {
            Mat output(videoController.frameSize(), CV_8U, Scalar::all(0));

            imshow("Stabilize", output);
            waitKey(1);
        }

        viewController.refreshCache();
        viewController.drawRect(tld.getBB(), COLOR_GREEN, 2);
        viewController.showCache();
    }
}
/*
int main(int argc, char *argv[])
{
    testOnVideo("/var/www/html/imc/p1a1/color_video_1.avi");
    
    //stabilize();
    return 0;
}*/


