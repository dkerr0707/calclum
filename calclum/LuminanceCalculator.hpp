//
//  LuminanceCalculator.hpp
//  calclum
//
//  Created by David Kerr on 2017-08-24.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#ifndef LuminanceCalculator_hpp
#define LuminanceCalculator_hpp

#include <iostream>
#include <opencv2/opencv.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

class Counter
{
public:
    boost::mutex m;
    int frameCount;
    double luminanceSum;
    
};


class LuminanceCalculator
{
public:
    LuminanceCalculator(const std::string path, int numberOfThreads);
    ~LuminanceCalculator(){};
    
    bool isValid() { return m_isValidVideo; };
    double getLuminance() { return m_videoLuminanceAverage; };
    
private:
    static void getFrameLuminance(cv::Mat& frame, Counter& counter);
    
    bool m_isValidVideo;
    
    double m_frameLuminanceSum;
    double m_frameCounter;
    double m_videoLuminanceAverage;
    
};

#endif /* LuminanceCalculator_hpp */
