//
//  Util.h
//  calclum
//
//  Created by David Kerr on 2017-08-26.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#ifndef Util_h
#define Util_h

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

#endif /* Util_h */
