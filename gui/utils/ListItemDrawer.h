//
// Created by Thorsten Claus on 01.03.23.
//

#ifndef STOCKS_LISTITEMDRAWER_H
#define STOCKS_LISTITEMDRAWER_H


#include <SupportDefs.h>
#include <InterfaceDefs.h>
#include <View.h>
#include <Font.h>

struct DrawItemSettings {
    BRect frame;
    BFont *font;
    rgb_color *color;
    alignment align;
    vertical_alignment verticalAlignment;
};

class ListItemDrawer {
public:
    ListItemDrawer(BView *parent);

    ~ListItemDrawer();

    rgb_color BackgroundColor(bool IsSelected);

    rgb_color TextColor(bool isSelected);

    void SetInsets(BSize insets);

    float Height(DrawItemSettings settings);

    void DrawString(const char *text, DrawItemSettings settings);

private:

    void DrawString(const char *text, BRect frame, const BFont *font, alignment align, rgb_color *color = NULL);

    BView *fParent;
    BSize fInsets;
};

#endif //STOCKS_LISTITEMDRAWER_H
