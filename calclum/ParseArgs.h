//
//  ParseArgs.h
//  calclum
//
//  Created by David Kerr on 2017-08-23.
//  Copyright © 2017 David Kerr. All rights reserved.
//

#ifndef ParseArgs_h
#define ParseArgs_h

#include <boost/filesystem.hpp>

namespace
{

    class InvalidArguments: public std::exception
    {
        virtual const char* what() const throw()
        {
            return "Invalid Arguments";
        }
    } invalidArguments;

    class InvalidNumberOfThreads: public std::exception
    {
        virtual const char* what() const throw()
        {
            return "Invalid number of threads";
        }
    } invalidNumberOfThreads;

    class InvalidDirectory: public std::exception
    {
        virtual const char* what() const throw()
        {
            return "Invalid Directory";
        }
    } invalidDirectory;


    struct Arguments
    {
        std::string path;
        unsigned int numberOfThreads;
    };

    Arguments parseArgs(int argc, const char* argv[])
    {
        const int NUM_OF_ARGUMENTS = 3;
        const int PATH_INDEX = 1;
        const int NUM_OF_THREADS_INDEX = 2;
        
        const std::string USAGE = "Usage: calclum [directory of video files] [number of threads]";
        
        if (argc != NUM_OF_ARGUMENTS)
        {
            std::cout << USAGE << std::endl;
            throw invalidArguments;
        }
        
        Arguments args;
        args.path = argv[PATH_INDEX];
        
        if ( !boost::filesystem::exists( args.path ) )
        {
            std::cout << USAGE << std::endl;
            throw invalidDirectory;
        }
        
        args.numberOfThreads = atoi(argv[NUM_OF_THREADS_INDEX]);
        
        if (args.numberOfThreads <= 0)
        {
            std::cout << USAGE << std::endl;
            throw invalidNumberOfThreads;
        }
        
        return args;
    }
    
    std::vector<std::string> getFilePaths(std::string directoryPath)
    {
        std::vector<std::string> filePaths;
        
        for (boost::filesystem::directory_iterator itr(directoryPath);
             itr != boost::filesystem::directory_iterator();
             ++itr)
        {
            
            if (is_regular_file(itr->status()))
            {
                filePaths.push_back(itr->path().string());
            }
        }
        
        return filePaths;
    }

}

#endif /* ParseArgs_h */
