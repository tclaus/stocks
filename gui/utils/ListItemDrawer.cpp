//
// Created by Thorsten Claus on 01.03.23.
//

#include "ListItemDrawer.h"
#include <Screen.h>

ListItemDrawer::ListItemDrawer(BView *parent)
        : fParent(parent), fInsets(BSize(5, 5)) {
}

ListItemDrawer::~ListItemDrawer() {}

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
    const BFont *font = settings.font == nullptr ? be_plain_font : settings.font;

    BRect drawingFrame = settings.frame;
    if (settings.verticalAlignment == B_ALIGN_BOTTOM) {
        drawingFrame.OffsetBySelf(0, Height(settings));
    }

    DrawString(text, drawingFrame, font, settings.align, settings.color, settings.rounded_rec_background_color);
}


float ListItemDrawer::Height(DrawItemSettings settings) {
    if (settings.font == nullptr) {
        return settings.frame.Height();
    }

    font_height fh{};
    settings.font->GetHeight(&fh);
    return fh.ascent + fh.descent + fh.leading + 2.0f;
}

void
ListItemDrawer::DrawString(const char *text, BRect frame, const BFont *font, alignment align, rgb_color *color,
                           rgb_color *rounded_rec_background_color) {

    fParent->SetFont(font);

    font_height fh{};
    font->GetHeight(&fh);

    const float fontHeight = fh.ascent + fh.descent + fh.leading;
    const float horizontalCenter = ((frame.Height() - fontHeight) / 2) + fh.descent;
    const float stringWidth = font->StringWidth(text);

    switch (align) {
        case B_ALIGN_LEFT: {
            fParent->MovePenTo(fInsets.width, frame.LeftBottom().y - horizontalCenter);
            break;
        }
        case B_ALIGN_RIGHT: {
            fParent->MovePenTo(frame.RightBottom().x - stringWidth - fInsets.width,
                               frame.RightBottom().y - horizontalCenter);
            break;
        }
        case B_ALIGN_CENTER: {
            const float center = (frame.Width() - stringWidth) / 2.0f;
            fParent->MovePenTo(center, frame.RightBottom().y - horizontalCenter);
            break;
        }
        default: {
            // Assume "Left"
            fParent->MovePenTo(fInsets.width, frame.LeftBottom().y - horizontalCenter);
            break;
        }
    }

    if (rounded_rec_background_color) {
        BRect backgroundFrame = calculateRect(stringWidth);
        DrawRoundedRec(backgroundFrame, *rounded_rec_background_color);
    }

    if (color == nullptr) {
        fParent->SetHighColor(TextColor(false));
    } else {
        fParent->SetHighColor(*color);
    }
    fParent->DrawString(text);
}

BRect ListItemDrawer::calculateRect(const float stringWidth) const {
    font_height fh{};
    auto *font = new BFont();
    fParent->GetFont(font);
    font->GetHeight(&fh);
    const float standardChangeLength = font->StringWidth("W99.99%");

    BPoint penLocation = fParent->PenLocation();
    float rectLeft = (penLocation.x + stringWidth) - standardChangeLength;
    float rectTop = penLocation.y - fh.ascent + 2;
    float rectRight = penLocation.x + stringWidth;
    float rectBottom = penLocation.y + 2;
    BRect backgroundFrame = {rectLeft, rectTop, rectRight, rectBottom};
    return backgroundFrame;
}

void
ListItemDrawer::DrawRoundedRec(const BRect &frame, const rgb_color &rounded_rec_background_color) {

    fParent->SetHighColor(rounded_rec_background_color);

    fParent->FillRoundRect(frame,
                           5.0f,
                           5.0f);
}
