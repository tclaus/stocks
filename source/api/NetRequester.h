//
// Created by Thorsten Claus on 09.03.23.
//

#ifndef STOCKS_NETREQUESTER_H
#define STOCKS_NETREQUESTER_H

#include <map>

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
     * @param request The prepared request to send
     * @param handler The handler to send status messages
     * @return The request Id
     */
    int AddRequest(BHttpRequest *request, BHandler *handler);

    /**
     * Returns the body from the request with the Id requestId if statuscode is 200 OK.
     * Returns an empty Json if not found or status code is not 200 Ok.
     * @param requestId The completed request with this Id.
     * @return The body or an empty json {}.
     */
    BString *Result(int requestId);

protected:

private:
    NetRequester();

private :
    static NetRequester instance;
    BHttpSession *fHttpSession;
    std::map<int32, BHttpResult> fHttpResultContainer;
};


#endif //STOCKS_NETREQUESTER_H
