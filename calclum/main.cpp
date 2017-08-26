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

#include "ParseArgs.h"
#include "LuminanceCalculator.hpp"

class NoVideosToProcess: public std::exception
{
    virtual const char* what() const throw()
    {
        return "No videos to process";
    }
} noVideosToProcess;

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
        
        Args::Arguments arguments = Args::parse(argc, argv);
        std::vector<std::string> filePaths = Args::getFilePaths(arguments.path);
        
        std::vector<double> averageLuminance;
        
        for (std::vector<std::string>::iterator it = filePaths.begin();
             it != filePaths.end();
             ++it)
        {
            
            LuminanceCalculator l(*it, arguments.numberOfThreads);
            if(l.isValid())
            {
                averageLuminance.push_back(l.getLuminance());
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
