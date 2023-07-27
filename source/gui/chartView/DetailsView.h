/*
 * Copyright 2023, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <SupportDefs.h>
#include <View.h>
#include "Quote.h"
#include "DetailsHeadline.h"
#include "DetailsDataList.h"
#include "DetailsChart.h"

class DetailsView : public BView {
public:
    DetailsView();

    void SetTimeRange(TimeRange timeRange);

private:
    DetailsHeadline *detailsHeadline;
    DetailsChart *detailsChart;
    DetailsDataList *detailsDataList;
};

#endif // CHARTVIEW_H
