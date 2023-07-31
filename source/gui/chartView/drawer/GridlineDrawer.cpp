//
// Created by Thorsten Claus on 17.07.23.
//

#include "GridlineDrawer.h"
#include "../Colors.h"

GridlineDrawer::GridlineDrawer(BView *view) :
        fView(view) {
}

void
GridlineDrawer::DrawGridLines([[maybe_unused]] BRect &updateRect) {
    DrawOuterFrame();
    DrawVerticalLines();
    DrawHorizontalLines();
}

void
GridlineDrawer::DrawOuterFrame() { fView->StrokeRect(fView->Bounds()); }

void
GridlineDrawer::DrawVerticalLines() {
    fView->PushState();
    fView->SetHighColor(Colors::Gridline());
    for (int lineNumber = 0; lineNumber < numberOfVerticalLines; lineNumber++) {
        float startX = fView->Bounds().Width() / (float) numberOfVerticalLines * (1 + (float) lineNumber);
        float startY = 0.0;
        BPoint startPoint(startX, startY);

        float endX = startX;
        float endY = fView->Bounds().Height();
        BPoint endPoint(endX, endY);
        fView->StrokeLine(startPoint, endPoint);
    }
    fView->PopState();
}

void
GridlineDrawer::DrawHorizontalLines() {
    fView->PushState();
    fView->SetHighColor(Colors::Gridline());
    for (int lineNumber = 0; lineNumber < numberOfHorizontalLines; lineNumber++) {
        float startX = 0.0;
        float startY = fView->Bounds().Height() / (float) numberOfHorizontalLines * (1 + (float) lineNumber);
        BPoint startPoint(startX, startY);

        float endX = fView->Bounds().Width();
        float endY = fView->Bounds().Height() / (float) numberOfHorizontalLines * (1 + (float) lineNumber);
        BPoint endPoint(endX, endY);
        fView->StrokeLine(startPoint, endPoint);
    }
    fView->PopState();
}