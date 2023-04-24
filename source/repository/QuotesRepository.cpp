//
// Created by Thorsten Claus on 15.04.23.
//

#include <Directory.h>
#include "QuotesRepository.h"
#include <string>
#include <Path.h>
#include <iostream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

QuotesRepository::QuotesRepository() {
    InitProjectFolder();
}

void QuotesRepository::StoreQuotes(const std::list<Quote *> &quotes) {

    json jsonOfSymbols = buildJsonArrayOfSymbols(quotes);

    // Get sone kind of "In template: no matching constructor for initialization of 'nlohmann::basic_json<>::serializer'" error
    const auto jsonString = jsonOfSymbols.dump();
    printf("Json as string: %s \n", jsonString.c_str());

    BString arrayOfSymbols = BString(jsonString.c_str());

    BPath configFilePath = BPath(RepositoryConfig::GetConfigFilePath().c_str());
    configFilePath.Append(RepositoryConfig::GetConfigfileFielName().c_str());

    status_t status = Repository::WriteFile(*configFilePath.Path(), arrayOfSymbols);
    if (status != B_OK) {
        std::cerr << "Could not write list of symbols" << std::endl;
    }

}

json QuotesRepository::buildJsonArrayOfSymbols(const std::list<Quote *> &quotes) const {
    json jsonOfSymbols;

    for (const auto &quote: quotes) {
        std::string strSymbol = quote->symbol->String();
        jsonOfSymbols.push_back(strSymbol);
    }
    return jsonOfSymbols;
}

void QuotesRepository::RestoreQuotes(const std::list<Quote *> &quotes) {
    char *content;
    (void) content;
    (void) quotes;

    BString *fileContent = new BString();


    Repository::ReadFile(GetConfigFilePath(), *fileContent);

    // convert content to quotes

}

void QuotesRepository::InitProjectFolder() {
    BPath configFilePath = BPath(RepositoryConfig::GetConfigFilePath().c_str());
    printf("Does config file path exist? %s\n", configFilePath.Path());

    BEntry fileEntry(configFilePath.Path());
    if (!fileEntry.Exists()) {
        BDirectory directory = BDirectory(configFilePath.Path());
        status_t status = directory.CreateDirectory(configFilePath.Path(), nullptr);
        if (status != B_OK) {
            std::cerr << "Path creation failed." << std::endl;
        }
    }
}


char QuotesRepository::GetConfigFilePath() const { return *RepositoryConfig::GetConfigFilePath().c_str(); }

