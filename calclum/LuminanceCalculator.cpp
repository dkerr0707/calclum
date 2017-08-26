//
//  LuminanceCalculator.cpp
//  calclum
//
//  Created by David Kerr on 2017-08-24.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <opencv2/opencv.hpp>

#include "LuminanceCalculator.hpp"


void LuminanceCalculator::run(const std::string path, std::vector<double>& averageLuminance, boost::mutex& mutex)
{
    cv::VideoCapture video(path);
    
    if (video.isOpened())
    {
        double luminanceSum = 0;
        double frameCount = 0;
        
        cv::Mat frame;
        while(video.read(frame))
        {
            const int LUMINANCE_PLANE = 1;
            
            cv::Mat xyz;
            cv::cvtColor(frame, xyz, cv::COLOR_BGR2XYZ);
            
            double avgLuminance = cv::sum( xyz )[LUMINANCE_PLANE] / (xyz.rows * xyz.cols);
            
            frameCount++;
            luminanceSum += avgLuminance;
        }
        
        double videoLuminanceAverage = luminanceSum / frameCount;
        
        boost::lock_guard<boost::mutex> guard(mutex);
        
        averageLuminance.push_back(videoLuminanceAverage);
        std::cout << path << std::endl;
        std::cout << "Luminance Average = " << videoLuminanceAverage << std::endl;
        
    }
}






