//
//  LuminanceCalculator.cpp
//  calclum
//
//  Created by David Kerr on 2017-08-24.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>

#include "LuminanceCalculator.hpp"


LuminanceCalculator::LuminanceCalculator(const std::string path, int numberOfThreads)
{
    cv::VideoCapture video(path);
    
    m_isValidVideo = video.isOpened() ? true : false;
    if (m_isValidVideo)
    {
    
        boost::asio::io_service ioService;
        boost::thread_group threadpool;
        boost::asio::io_service::work work(ioService);
        
        for(int i = 0; i < numberOfThreads; i++)
        {
            threadpool.create_thread( boost::bind(&boost::asio::io_service::run, &ioService) );
        }
        
        Counter c;
        
        cv::Mat frame;
        while(video.read(frame))
        {
            ioService.post(boost::bind(LuminanceCalculator::getFrameLuminance, frame.clone(), boost::ref(c)));
        }
        
        ioService.stop();
        threadpool.join_all();
        
        m_videoLuminanceAverage = c.luminanceSum / c.frameCount;
        
        std::cout << path << std::endl;
        std::cout << "Luminance Average = " << m_videoLuminanceAverage << std::endl;
        
    }
}

void LuminanceCalculator::getFrameLuminance(cv::Mat& frame, Counter& counter)
{
    const int LUMINANCE_PLANE = 1;
    
    cv::Mat xyz;
    cv::cvtColor(frame, xyz, cv::COLOR_BGR2XYZ);
    
    double avgLuminance = cv::sum( xyz )[LUMINANCE_PLANE] / (xyz.rows * xyz.cols);
    
    boost::lock_guard<boost::mutex> guard(counter.mutex);
    counter.frameCount++;
    counter.luminanceSum += avgLuminance;
}







