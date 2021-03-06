//
//  App.hpp
//  calclum
//
//  Created by David Kerr on 2017-08-25.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#ifndef App_hpp
#define App_hpp

#include <vector>

class App
{
public:
    
    App(){};
    ~App(){};
    
    void run(std::vector<std::string>& filePaths, const int numberOfThreads);
    
    class NoVideosToProcess: public std::exception
    {
        virtual const char* what() const throw()
        {
            return "No videos to process";
        }
    } noVideosToProcess;
    
private:
    
    void outputData(std::vector<double>& v);

};



#endif /* App_hpp */
