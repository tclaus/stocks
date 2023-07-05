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
    std::string jsonString = "{ \"symbols\": " + jsonOfSymbols.dump() + "}";

    BPath configFilePath = createConfigFilePath();
    BString arrayOfSymbols = BString(jsonString.c_str());

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

void QuotesRepository::RestoreQuotes(std::list<Quote *> &quotes) {

    BString *fileContentString = new BString();
    BPath configFilePath = createConfigFilePath();

    status_t readStatus = Repository::ReadFile(*configFilePath.Path(), *fileContentString);
    if (readStatus != B_OK) {
        std::cerr << "Could not read symbols file." << std::endl;
        return;
    }
    checkFileContents(fileContentString);

    ReadOutFileContent(quotes, fileContentString);
}

void QuotesRepository::ReadOutFileContent(std::list<Quote *> &quotes, BString *fileContentString) const {
    if (fileContentString->Length() > 1) {
        json readJsonString = json::parse(fileContentString->String());
        json symbols = readJsonString["symbols"];
        if (symbols.is_array()) {
            quotes.clear();
            for (auto &element: symbols) {
                printf("Adding symbol %s \n", element.dump().c_str());
                BString symbol = element.dump().c_str();
                symbol.RemoveAll("\"");
                quotes.emplace_back(new Quote(new std::string(symbol)));
            }
            printf("Now we have %zu quotes\n", quotes.size());
        }
    }
}

void QuotesRepository::checkFileContents(const BString *fileContentString) const {
    printf("Read from file: %s \n", fileContentString->String());
    if (fileContentString->Length() == 0) {
        printf(" File is empty.");
    }
}

BPath QuotesRepository::createConfigFilePath() const {
    BPath configFilePath = BPath(RepositoryConfig::GetConfigFilePath().c_str());
    configFilePath.Append(RepositoryConfig::GetConfigfileFielName().c_str());
    return configFilePath;
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
