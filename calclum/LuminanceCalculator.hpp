//
//  LuminanceCalculator.hpp
//  calclum
//
//  Created by David Kerr on 2017-08-24.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#ifndef LuminanceCalculator_hpp
#define LuminanceCalculator_hpp

#include <boost/thread/thread.hpp>


class LuminanceCalculator
{
public:
    
    static void run(const std::string path, std::vector<double>& averageLuminance, boost::mutex& outputMutex);
    
};

#endif /* LuminanceCalculator_hpp */
