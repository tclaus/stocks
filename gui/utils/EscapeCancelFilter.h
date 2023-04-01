//
// Created by Thorsten Claus on 31.03.23.
//

#ifndef STOCKS_ESCAPECANCELFILTER_H
#define STOCKS_ESCAPECANCELFILTER_H

#include <MessageFilter.h>
#include <Handler.h>
#include <InterfaceDefs.h>

/**
*   EscapeCancelFilter.h: An easy way to quit with the Escape key
*	Written by DarkWyrm <darkwyrm@earthlink.net>, Copyright 2007
*	Released under the MIT license.
*
*   This filter is most often useful in dialog windows where you would
*	like to allow the user to effectively hit the Cancel button just by
*	hitting the Escape key. Pass one of these to BWindow::AddCommonFilter
'*	and that is all that is necessary.
*/

class EscapeCancelFilter : public BMessageFilter {
public:
    EscapeCancelFilter(void)
            : BMessageFilter(B_PROGRAMMED_DELIVERY,
                             B_ANY_SOURCE, B_KEY_DOWN) {
    }

    ~EscapeCancelFilter(void) {}

    filter_result Filter(BMessage *msg, BHandler **target);
};


#endif //STOCKS_ESCAPECANCELFILTER_H
