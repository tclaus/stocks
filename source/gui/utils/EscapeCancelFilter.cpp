//
// Created by Thorsten Claus on 31.03.23.
//

#include "EscapeCancelFilter.h"
#include "SearchFieldControl.h"
#include <Messenger.h>
#include <Looper.h>

filter_result
EscapeCancelFilter::Filter(BMessage *msg, BHandler **target) {

    int32 rawchar;
    int32 mod;
    msg->FindInt32("raw_char", &rawchar);
    msg->FindInt32("modifiers", &mod);

    if (rawchar == B_ESCAPE && (mod & (B_SHIFT_KEY | B_COMMAND_KEY |
                                       B_OPTION_KEY | B_CONTROL_KEY)) == 0) {
        BLooper *loop = (*target)->Looper();
        if (loop) {
            BMessenger message(loop);
            message.SendMessage(M_DISMISS_SEARCH);
            return B_SKIP_MESSAGE;
        }
    }
    return B_DISPATCH_MESSAGE;

}