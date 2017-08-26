//
//  main.cpp
//  calclum
//
//  Created by David Kerr on 2017-08-22.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#include <iostream>
#include <exception>
#include <vector>

#include "ParseArgs.h"
#include "App.hpp"


int main(int argc, const char * argv[])
{
    
    try
    {
        
        Arguments arguments = parse(argc, argv);
        std::vector<std::string> filePaths = getFilePaths(arguments.path);
        
        App app;
        app.run(filePaths, arguments.numberOfThreads);
        
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
   
    
    return EXIT_SUCCESS;
}
