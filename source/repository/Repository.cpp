//
// Created by Thorsten Claus on 16.04.23.
//

#include <File.h>
#include <string>
#include "Repository.h"

status_t Repository::ReadFile(const char &path, BString &content) {
    if (!path) {
        return B_BAD_VALUE;
    }
    BFile file(&path, B_READ_ONLY);

    if (file.InitCheck() != B_OK) {
        return B_ERROR;
    }

    off_t fileSize = 0;
    file.GetSize(&fileSize);
    if (fileSize < 1) {
        return B_OK;
    }

    char *buffer = content.LockBuffer((int) fileSize);
    file.Read(buffer, fileSize);
    content.UnlockBuffer();
    return B_OK;
}

status_t Repository::WriteFile(const char &path, const BString &content) {
    if (!path) {
        return B_BAD_VALUE;
    }

    BFile file(&path, B_READ_WRITE | B_CREATE_FILE);
    if (file.InitCheck() != B_OK) {
        return B_ERROR;
    }
    const char *contentBuffer = content.String();

    size_t contentSize = std::char_traits<char>::length(contentBuffer);

    file.Write(contentBuffer, contentSize);
    file.SetSize(contentSize);
    // File close is implicit handled by BFile
    return B_OK;
}
