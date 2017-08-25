//
//  LuminanceCalculator.cpp
//  calclum
//
//  Created by David Kerr on 2017-08-24.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#include "LuminanceCalculator.hpp"

LuminanceCalculator::LuminanceCalculator(const std::string path)
{
    const int LUMINANCE_PLANE = 1;
    
    m_video.open(path);
    
    m_isValidVideo = m_video.isOpened() ? true : false;
    if (m_isValidVideo)
    {
    
        m_frameLuminanceSum = 0;
        m_frameCounter = 0;
        
        cv::Mat xyz;
        cv::namedWindow("video",1);
        
        cv::Mat frame;
        while(m_video.read(frame))
        {
            
            m_frameCounter++;
            
            cv::cvtColor(frame, xyz, cv::COLOR_BGR2XYZ);
            double avgLuminance = cv::sum( xyz )[LUMINANCE_PLANE] / (xyz.rows * xyz.cols);
            m_frameLuminanceSum += avgLuminance;
            
            imshow("video", frame);
            
            if(cv::waitKey(1) >= 0) break;
        }
        
        m_videoLuminanceAverage = m_frameLuminanceSum / m_frameCounter;
        std::cout << "Video Luminance Average = " << m_videoLuminanceAverage << std::endl;
        
    }
    
   
}
