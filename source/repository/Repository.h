//
// Created by Thorsten Claus on 16.04.23.
//

#ifndef STOCKS_REPOSITORY_H
#define STOCKS_REPOSITORY_H


#include <String.h>
#include <SupportDefs.h>

class Repository {
public:
    /**
     * Reads plain file contents from the given path
     * @param path Filepath to read
     * @param content Content will be set
     * @return B_OK or B_ERROR. Ok can also mean that the file was empty, but could be read.
     */
    static status_t ReadFile(const char &path, BString &content);

    /**
     * Writes the content char array to the file specified by the path.
     * If the file does not exists, it will be created.
     * @param path Filepath to write for. The path must exists.
     * @param content The content to write.
     * @return B_OK if everything was OK, an Error otherwise.
     */
    static status_t WriteFile(const char &path, const BString &content);
};


#endif //STOCKS_REPOSITORY_H
