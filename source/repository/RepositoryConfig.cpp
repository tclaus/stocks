//
// Created by Thorsten Claus on 15.04.23.
//


#include "RepositoryConfig.h"
#include <FindDirectory.h>

#include <string>
#include <Path.h>

const std::string RepositoryConfig::configFileName = "config";

std::string RepositoryConfig::GetConfigFilePath() {
    BPath bPath;
    find_directory(B_USER_CONFIG_DIRECTORY, &bPath);
    bPath.Append("settings");
    bPath.Append(projectDirectoryName.c_str());
    return bPath.Path();
}

std::string RepositoryConfig::GetConfigfileFieleName() {
    return RepositoryConfig::configFileName;
}
