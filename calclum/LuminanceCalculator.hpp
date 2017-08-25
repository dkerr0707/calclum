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

class LuminanceCalculator
{
public:
    LuminanceCalculator(const std::string path);
    ~LuminanceCalculator(){};
    
    bool isValid() { return m_isValidVideo; };
    double getLuminance() { return m_videoLuminanceAverage; };
private:
    cv::VideoCapture m_video;
    bool m_isValidVideo;
    
    double m_frameLuminanceSum;
    double m_frameCounter;
    double m_videoLuminanceAverage;
};

#endif /* LuminanceCalculator_hpp */
