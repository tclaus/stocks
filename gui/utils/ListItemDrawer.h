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
    rgb_color *rounded_rec_background_color;
};

class ListItemDrawer {
public:
    explicit ListItemDrawer(BView *parent);

    ~ListItemDrawer();

    rgb_color BackgroundColor(bool IsSelected);

    rgb_color TextColor(bool isSelected);

    void SetInsets(const BSize insets);

    float Height(const DrawItemSettings &settings);

    void DrawString(const char *text, const DrawItemSettings &settings);

private:

    void DrawString(const char *text, BRect frame, const BFont *font, alignment align, rgb_color *color,
                    rgb_color *rounded_rec_background_color);

    void DrawRoundedRec(const BRect &frame, const rgb_color &rounded_rec_background_color);

    BView *fParent;
    BSize fInsets;

    BRect calculateRect(float stringWidth) const;
};

#endif //STOCKS_LISTITEMDRAWER_H
