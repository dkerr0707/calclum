//
//  App.cpp
//  calclum
//
//  Created by David Kerr on 2017-08-25.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#include <algorithm>
#include <numeric>

#include "App.hpp"
#include "LuminanceCalculator.hpp"

void App::run(std::vector<std::string>& filePaths, int numberOfThreads)
{
    std::vector<double> averageLuminance;
    
    for (std::vector<std::string>::iterator it = filePaths.begin();
         it != filePaths.end();
         ++it)
    {
        
        LuminanceCalculator l(*it, numberOfThreads);
        if(l.isValid())
        {
            averageLuminance.push_back(l.getLuminance());
        }
        
    }
    
    if(averageLuminance.size() == 0)
        throw noVideosToProcess;
    
    outputData(averageLuminance);
}

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
T getMedian(std::vector<T>& v)
{
    size_t size = v.size();
    
    std::sort(std::begin(v), std::end(v));
    
    T median;
    
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


void App::outputData(std::vector<double>& v)
{
    std::cout << std::endl << std::endl;
    
    auto min = std::min_element(std::begin(v), std::end(v));
    std::cout << "Minimum - " << *min << std::endl;
    
    auto max = std::max_element(std::begin(v), std::end(v));
    std::cout << "Max - " << *max << std::endl;
    
    double mean = std::accumulate( std::begin(v), std::end(v), 0.0) / v.size();
    std::cout << "Mean - " << mean << std::endl;
    
    double median = getMedian(v);
    std::cout << "Median - " << median << std::endl;
}


