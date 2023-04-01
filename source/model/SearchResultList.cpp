//
// Created by Thorsten Claus on 19.03.23.
//

#include "SearchResultList.h"
#include "SearchResultItem.h"
#include <iostream>
#include <string_view>
#include <String.h>
#include <chrono>

using namespace std::string_view_literals;
using json = nlohmann::json;
using namespace nlohmann::literals;

SearchResultList::SearchResultList()
        :
        fSearchResultList(new std::list<SearchResultItem *>()) {}

void SearchResultList::ListFromJson(BString *jsonString) {
    json parsedJson = json::parse(jsonString->String());
    // std::cout << "Show complete search results:  " << jsonString->String() << std::endl;
    fSearchResultList->clear();

    for (auto &item: parsedJson.items()) {
        auto innerJsonElement = item.value();
        if (!IsValid(innerJsonElement)) {
            continue;
        }

        auto *searchResultItem = new SearchResultItem();
        searchResultItem->symbol = new BString(innerJsonElement.value("symbol"sv, "opps").c_str());
        searchResultItem->name = new BString(innerJsonElement.value("name"sv, "opps").c_str());
        searchResultItem->stockExchange = new BString(innerJsonElement.value("stockExchange"sv, "opps").c_str());
        searchResultItem->currency = new BString(innerJsonElement.value("currency"sv, "opps").c_str());
        fSearchResultList->push_back(searchResultItem);
    }
}

bool
SearchResultList::IsValid(nlohmann::basic_json<> &jsonElement) {
    if (jsonElement.is_null()) {
        return false;
    }

    if (jsonElement.at("symbol") == nullptr) {
        return false;
    }

    if (jsonElement.at("name") == nullptr) {
        return false;
    }

    if (jsonElement.at("stockExchange") == nullptr) {
        return false;
    }

    if (jsonElement.at("currency") == nullptr) {
        return false;
    }
    return true;
}

void SearchResultList::Clear() {
    fSearchResultList->clear();
}

std::list<SearchResultItem *> *
SearchResultList::List() {
    return fSearchResultList;
}