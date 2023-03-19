//
// Created by Thorsten Claus on 09.03.23.
//

#ifndef STOCKS_NETREQUESTER_H
#define STOCKS_NETREQUESTER_H

#include <vector>
#include <list>

#include <String.h>
#include <HttpSession.h>
#include <HttpResult.h>
#include <Handler.h>

#include <HttpRequest.h>

using BPrivate::Network::BHttpSession;
using BPrivate::Network::BHttpResult;
using BPrivate::Network::BHttpRequest;

class NetRequester {

public:
    NetRequester(const NetRequester &) = delete;

    static NetRequester &Instance();

    void AddRequest(BHttpRequest *request, BHandler *handler);

    // Return result (by id?)

    BString *Result();

protected:

private:
    NetRequester();

private :
    BHttpSession *fHttpSession;
    std::list<BHttpResult> fHttpResultContainer; // Es gibt auch ne Map!
    static NetRequester instance;
};


#endif //STOCKS_NETREQUESTER_H