//
// Created by Thorsten Claus on 19.03.23.
//

#ifndef STOCKS_SEARCHRESULTLIST_H
#define STOCKS_SEARCHRESULTLIST_H


#include <List.h>
#include <list>
#include <String.h>
#include "SearchResultItem.h"

class SearchResultList {
public:

    SearchResultList();

    /**
     * Creates a list of items from a json string. The json was created by the search endpoint of an API.
     * @param json
     */
    void
    ListFromJson(BString *jsonString);

    void
    Clear();

    /**
     * Returns the list of items.
     * @return
     */
    std::list<SearchResultItem *> *List();

private:
    std::list<SearchResultItem *> *fSearchResultList;
};


#endif //STOCKS_SEARCHRESULTLIST_H
