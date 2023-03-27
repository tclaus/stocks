//
// Created by Thorsten Claus on 27.03.23.
//

#include "ShareListItem.h"

ShareListItem::ShareListItem()
        :
        BListItem() {}

Quote *ShareListItem::GetQuote() {
    return fQuote;
}