//
// Created by Thorsten Claus on 15.04.23.
//

#ifndef STOCKS_REPOSITORYCONFIGPATH_H
#define STOCKS_REPOSITORYCONFIGPATH_H

#include <string>

class RepositoryConfig {
public:
    static std::string GetConfigFilePath();

    static std::string GetConfigfileFieleName();

private:
    static const std::string projectDirectoryName;
    static const std::string configFileName;
};


#endif //STOCKS_REPOSITORYCONFIGPATH_H
