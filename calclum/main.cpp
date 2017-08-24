//
//  main.cpp
//  calclum
//
//  Created by David Kerr on 2017-08-22.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <numeric>
#include <exception>
#include <vector>
#include <opencv2/opencv.hpp>

#include "ParseArgs.h"

double calculateLuminance(const std::string path)
{
    const int LUMINANCE_PLANE = 1;
    
    cv::VideoCapture video(path);
    if(!video.isOpened())
        return -1;
    
    double frameLuminanceSum = 0;
    double frameCounter = 0;
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
            double avgLuminance = cv::sum( xyz )[LUMINANCE_PLANE] / (xyz.rows * xyz.cols);
            frameLuminanceSum += avgLuminance;
        
            imshow("video", frame);
        }
        else
        {
            break;
        }
        if(cv::waitKey(1) >= 0) break;
    }
    
    double videoLuminanceAverage = frameLuminanceSum / frameCounter;
    
    std::cout << "Video Average = " << videoLuminanceAverage << std::endl;
    
    return videoLuminanceAverage;
}


double getMedian(std::vector<double>& v)
{
    size_t size = v.size();
    
    std::sort(std::begin(v), std::end(v));
    
    double median;
    
    if (v.size() % 2 == 0)
    {
        median = ( v[size/2 - 1] + v[size/2] ) / 2;
    }
    else
    {
        median = v[size/2];
    }
    
    return median;
}

class NoVideosToProcess: public std::exception
{
    virtual const char* what() const throw()
    {
        return "No videos to process";
    }
} noVideosToProcess;

void outputData(std::vector<double>& v)
{
    std::cout << "---------" << std::endl << std::endl;
    
    auto min = std::min_element(std::begin(v), std::end(v));
    std::cout << "Minimum - " << *min << std::endl;
    
    auto max = std::max_element(std::begin(v), std::end(v));
    std::cout << "Max - " << *max << std::endl;
    
    double mean = std::accumulate( std::begin(v), std::end(v), 0.0) / v.size();
    std::cout << "Mean - " << mean << std::endl;
    
    
    double median = getMedian(v);
    std::cout << "Median - " << median << std::endl;
}



int main(int argc, const char * argv[])
{
    
    try
    {
        Arguments arguments = parseArgs(argc, argv);
        std::vector<std::string> filePaths = getFilePaths(arguments.path);
        
        std::vector<double> averageLuminance;
        
        for (std::vector<std::string>::iterator it = filePaths.begin();
             it != filePaths.end();
             ++it)
        {
            std::cout << *it << std::endl;
            double currentLuminance = calculateLuminance(*it);
            if (currentLuminance >= 0)
            {
                averageLuminance.push_back(currentLuminance);
            }
        }
        
        if(averageLuminance.size() == 0)
            throw noVideosToProcess;
        
        outputData(averageLuminance);
        
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
   
    
    return EXIT_SUCCESS;
}
