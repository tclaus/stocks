//
// Created by Thorsten Claus on 15.02.23.
//

#include "BListItemView.h"
#include <View.h>

BListItemView::BListItemView(BView *view)
{
    SetView(view);
}

void BListItemView::SetView(BView *view) {
    if(view == NULL || _view == view)
        return;

    if (_view != NULL) {
        _view->RemoveSelf();
        delete _view;
    }
    _view = view;

}

void BListItemView::DrawItem(BView *owner, BRect frame, bool complete) {
    if (_view == NULL)
        return;
    _view->Draw(frame);
}

const BView *BListItemView::View() const {
    return this->_view;
}

void BListItemView::Update(BView *owner, const BFont *font) {

}
