//
//  main.cpp
//  calclum
//
//  Created by David Kerr on 2017-08-22.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#include <iostream>
#include <exception>
#include <thread>
#include <vector>

#include <opencv2/opencv.hpp>


class InvalidArguments: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Invalid Arguments";
    }
} invalidArguments;

class InvalidNumberOfThreads: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Invalid number of threads";
    }
} invalidNumberOfThreads;


struct Arguments
{
    std::string path;
    unsigned int numberOfThreads;
};

Arguments parseArgs(int argc, const char* argv[])
{
    const int NUM_OF_ARGUMENTS = 3;
    const std::string USAGE = "Usage: calclum [directory of video files] [number of threads]";
    
    if (argc != NUM_OF_ARGUMENTS)
    {
        std::cout << USAGE << std::endl;
        throw invalidArguments;
    }
    
    Arguments args;
    args.path = argv[1];
    args.numberOfThreads = atoi(argv[2]);
    
    if (args.numberOfThreads == 0)
    {
        std::cout << USAGE << std::endl;
        throw invalidNumberOfThreads;
    }
    
    std::cout << args.path << std::endl;
    std::cout << args.numberOfThreads << std::endl;
    
    return args;
}


int calculateLuminance()
{
    cv::VideoCapture video(0);//"/Users/dkerr/dev/video/Ref_768x432_yuv420p.mpg");
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
        
        calculateLuminance();
        
        
        
        
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
        return EXIT_FAILURE;
    }
   
    
    return EXIT_SUCCESS;
}
