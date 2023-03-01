//
// Created by Thorsten Claus on 15.02.23.
//

#include "BListItemView.h"
#include <View.h>
#include <iostream>

BListItemView::BListItemView(BView *view)
        : _view{nullptr} {
    SetView(view);
}

void BListItemView::SetView(BView *view) {
    if (view == nullptr || _view == view)
        return;

    if (_view != nullptr) {
        _view->RemoveSelf();
        delete _view;
    }
    _view = view;
    _view->SetViewColor(255, 0, 0, 0);

}

void BListItemView::DrawItem(BView *owner, BRect frame, bool complete) {
    (void) complete;
    std::cout << "Owner:" << frame.LeftTop().x << ", " << frame.LeftTop().y;

    if (_view == nullptr)
        return;
    owner->SetLayout(_view->GetLayout());
    owner->Draw(frame);

    // Wenn das nicht geht, dann manuell die Texte bauen
    owner->MovePenTo(5, 15);
    owner->DrawString("Hallo, Halloo");
    std::cout << "Drawing view: " << _view->Name() << std::endl;
}

void BListItemView::Update(BView *owner, const BFont *font) {
    (void) owner;
    (void) font;
    BListItem::Update(owner, font);
}
