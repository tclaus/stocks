//
// Created by Thorsten Claus on 01.03.23.
//

#include "ListItemDrawer.h"
#include <Screen.h>

ListItemDrawer::ListItemDrawer(BView *parent)
        : fParent(parent), fInsets(BSize(5, 5)) {

}

ListItemDrawer::~ListItemDrawer() {

}

void
ListItemDrawer::SetInsets(BSize insets) {
    fInsets = insets;
}

rgb_color
ListItemDrawer::BackgroundColor(bool isSelected) {
    if (isSelected) {
        rgb_color selectedColor;
        selectedColor.set_to(210, 206, 205);
        return selectedColor;
    }

    rgb_color selectedColor;
    selectedColor.set_to(232, 228, 225);
    return selectedColor;

}

rgb_color
ListItemDrawer::TextColor(bool isSelected) {
    return ui_color(isSelected ? B_LIST_SELECTED_ITEM_TEXT_COLOR : B_LIST_ITEM_TEXT_COLOR);
}

void
ListItemDrawer::DrawString(const char *text, DrawItemSettings settings) {
    const BFont *font = settings.font == NULL ? be_plain_font : settings.font;

    BRect drawingFrame = settings.frame;
    if (settings.verticalAlignment == B_ALIGN_BOTTOM) {
        drawingFrame.OffsetBySelf(0, Height(settings));
    }

    DrawString(text, drawingFrame, font, settings.align, settings.color);
}

float ListItemDrawer::Height(DrawItemSettings settings) {
    if (settings.font == NULL) {
        return settings.frame.Height();
    }

    font_height fh{};
    settings.font->GetHeight(&fh);
    return fh.ascent + fh.descent + fh.leading + 2.0;
}

void
ListItemDrawer::DrawString(const char *text, BRect frame, const BFont *font, alignment align, rgb_color *color) {

    fParent->SetFont(font);

    font_height fh{};
    font->GetHeight(&fh);

    const float fontHeight = fh.ascent + fh.descent + fh.leading;
    const float horizontalCenter = ((frame.Height() - fontHeight) / 2) + fh.descent;

    switch (align) {
        case B_ALIGN_LEFT: {
            fParent->MovePenTo(fInsets.width, frame.LeftBottom().y - horizontalCenter);
            break;
        }
        case B_ALIGN_RIGHT: {
            const float width = font->StringWidth(text);
            fParent->MovePenTo(frame.RightBottom().x - width - fInsets.width, frame.RightBottom().y - horizontalCenter);
            break;
        }
        case B_ALIGN_CENTER: {
            const float width = font->StringWidth(text);
            const float center = (frame.Width() - width) / 2.0f;
            fParent->MovePenTo(center, frame.RightBottom().y - horizontalCenter);
            break;
        }
        default: {
            // Assume "Left"
            fParent->MovePenTo(fInsets.width, frame.LeftBottom().y - horizontalCenter);
            break;
        }
    }

    if (color == NULL) {
        fParent->SetHighColor(TextColor(false));
    } else {
        fParent->SetHighColor(*color);
    }
    fParent->DrawString(text);
}