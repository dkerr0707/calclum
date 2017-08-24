//
//  main.cpp
//  calclum
//
//  Created by David Kerr on 2017-08-22.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#include <iostream>
#include <exception>
#include <vector>
#include <opencv2/opencv.hpp>

#include "ParseArgs.h"

int calculateLuminance()
{
    cv::VideoCapture video("/Users/dkerr/dev/video/Ref_768x432_yuv420p.mpg");
    if(!video.isOpened())
        return -1;
    
    float frameLuminanceSum = 0;
    float frameCounter = 0;
    cv::Mat xyz;
    cv::namedWindow("video",1);
    
    while(true)
    {
        cv::Mat frame;
        video >> frame;
        if(!frame.empty())
        {
            frameCounter++;
            
            cv::cvtColor(frame, xyz, cv::COLOR_BGR2XYZ);
            float avgLuminance = cv::sum( xyz )[1] / (xyz.rows * xyz.cols);
            frameLuminanceSum += avgLuminance;
            std::cout << avgLuminance << std::endl;;

        
            imshow("video", frame);
        }
        else
        {
            break;
        }
        if(cv::waitKey(1) >= 0) break;
    }
    
    float videoLuminanceAverage = frameLuminanceSum / frameCounter;
    
    std::cout << "Video Average = " << videoLuminanceAverage << std::endl;
    
    return EXIT_SUCCESS;
}


int main(int argc, const char * argv[])
{
    Arguments arguments;
    
    try
    {
        arguments = parseArgs(argc, argv);
        
        for (boost::filesystem::directory_iterator itr(arguments.path);
             itr != boost::filesystem::directory_iterator();
             ++itr)
        {
            std::cout << itr->path().filename() << ' '; // display filename only
            if (is_regular_file(itr->status()))
            {
                std::cout << " [" << file_size(itr->path()) << ']';
            }
            std::cout << "\n";
        }
        
        calculateLuminance();
        
        
        
        
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
        return EXIT_FAILURE;
    }
   
    
    return EXIT_SUCCESS;
}
