/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef STOCK_LIST_ITEM_H
#define STOCK_LIST_ITEM_H


#include <SupportDefs.h>


class StockListItem : BView(BRect(), "stocksView", B_FOLLOW_ALL, B_WILL_DRAW){
public:
	StockListItem(String* stockName);
	
private:
	String* stockName;
};

// TODO: StockItem bekommt ein Objekt StockData, das alle FundamentalDaten einer Aktie enthält
// Tickersymbol, Name Börsenplatz, Kurs, und Gewinn/Verlust 


#endif // STOCK_LIST_ITEM_H
