//
// Created by Thorsten Claus on 19.03.23.
//

#include "SearchResultList.h"
#include "SearchResultItem.h"
#include "nlohmann/json.hpp"
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

void SearchResultList::Clear() {
    fSearchResultList->clear();
}

void SearchResultList::ListFromJson(BString *jsonString) {
    json parsedJson = json::parse(jsonString->String());
    std::cout << "Show complete search results:  " << std::endl;
    fSearchResultList->clear();

    for (auto &item: parsedJson.items()) {
        auto innerJsonElement = item.value();
        auto *searchResultItem = new SearchResultItem();
        searchResultItem->symbol = new BString(innerJsonElement.value("symbol"sv, "opps").c_str());
        searchResultItem->name = new BString(innerJsonElement.value("name"sv, "opps").c_str());
        searchResultItem->stockExchange = new BString(innerJsonElement.value("stockExchange"sv, "opps").c_str());
        searchResultItem->currency = new BString(innerJsonElement.value("currency"sv, "opps").c_str());
        fSearchResultList->push_back(searchResultItem);
    }
}

std::list<SearchResultItem *> *
SearchResultList::List() {
    return fSearchResultList;
}