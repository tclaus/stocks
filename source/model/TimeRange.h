//
// Created by Thorsten Claus on 13.07.23.
//

#ifndef STOCKS_TIMERANGE_H
#define STOCKS_TIMERANGE_H

enum TimeRange {
    M_DAY = 'ADAY',
    M_WEEK = 'WEEK',
    M_MONTH = 'MONT',
    M_THREE_MONTH = 'QUAT',
    M_SIX_MONTH = 'HYEA',
    M_YEAR = 'YEAR',
    M_TWO_YEARS = '2YEA',
    M_FIVE_YEARS = '5YEA'
};

#endif //STOCKS_TIMERANGE_H
