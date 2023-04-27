//
// Created by Thorsten Claus on 26.04.23.
//

#ifndef STOCKS_FINANCIALMODELINGAPIKEY_H
#define STOCKS_FINANCIALMODELINGAPIKEY_H

#include <string>

/**
 * Contributors can easy generate a free developer license.
 * Visit https://site.financialmodelingprep.com/developer create a free account and get a free developer key.
 * Add this key to your local STOCKS_APP_API_KEY environment variable.
 */
class FinancialmodelingApiKey {
public:

    /**
     * Returns the api key to use the Financial Modelling service.
     *
     * @return Api key
     */
    static std::string GetApiKey();

private:
    static const std::string fApiKey;
};


#endif //STOCKS_FINANCIALMODELINGAPIKEY_H
