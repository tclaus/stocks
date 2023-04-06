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

    /**
     * Adds a request to the pipeline and returns the request id.
     * @param request
     * @param handler
     * @return
     */
    int AddRequest(BHttpRequest *request, BHandler *handler);

    BString *Result(int resultId);

protected:

private:
    NetRequester();

private :
    static NetRequester instance;
    BHttpSession *fHttpSession;
    std::list<BHttpResult> fHttpResultContainer;
};


#endif //STOCKS_NETREQUESTER_H
