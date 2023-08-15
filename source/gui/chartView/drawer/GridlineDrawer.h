//
// Created by Thorsten Claus on 17.07.23.
//

#ifndef STOCKS_GRIDLINEDRAWER_H
#define STOCKS_GRIDLINEDRAWER_H


#include <View.h>

/**
 * Draws the background of the chart. Makes use of the full size of the provided view
 */
class GridlineDrawer {
public:
    /**
     * Initializes the gridline drawer with the provided view.
     * It draws the frame as well as the horizontal and vertical background lines.
     * @param view
     */
    explicit GridlineDrawer(BView *view);

    void DrawGridLines(BRect &updateRect);

private:
    void DrawOuterFrame();

    void DrawVerticalLines();

    BView *fView;
    const int numberOfVerticalLines = 4;
    const int numberOfHorizontalLines = 4;

    void DrawHorizontalLines();
};


#endif //STOCKS_GRIDLINEDRAWER_H
