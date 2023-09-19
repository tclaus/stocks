cmake_minimum_required(VERSION 3.23)

project(
        Stocks
        VERSION 0.2
        DESCRIPTION "A stocks application to set up a portfolio and check stock price changes over time"
)

set(CMAKE_MODULE_PATH "${Stocks_SOURCE_DIR}/CMakeModules")

if (CMAKE_PROJECT_NAME STREQUAL ${PROJECT_NAME})
    set(CMAKE_EXPORT_COMPILE_COMMANDS On)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED)

    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(HAIKU_ENABLE_I18N ON)

include(UseHaiku)

# Needed dependencies because FinancialmodelingApiKey and RepositoryConfig should be copied to the right place
add_dependencies("catkeys" ${PROJECT_NAME})
add_dependencies("catalogs" ${PROJECT_NAME})
add_dependencies("bindcatalogs" ${PROJECT_NAME})

option(STRICT_WARNINGS "Compile with extra warnings and errors" ON)

if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 2.96 AND STRICT_WARNINGS)
    add_compile_options(-Wall -Wextra -Wshadow -Werror)
    if (USE_CLANG)
        # clang finds a lot more problems than gcc, disable some of the warnings
        # set these here instead of earlier, they must come after -Wall, -Werror, etc...
        add_compile_options(
                -Wno-overloaded-virtual
                -Wno-unused-private-field
                -Wno-return-type-c-linkage
                -Wno-unused-const-variable
                -Wno-deprecated-register
        )
    endif ()
endif ()

include_directories(AFTER
        /boot/system/develop/headers/private/netservices2
        /boot/system/develop/headers/os
        source/utils
        source/model
        source/model/linkedRequestQuoteStore
        source/gui/stocksPanel
        source/gui/stocksPanel/listView
        source/gui/chartView
        source/gui/utils
        source/repository
        source/api
        ${CMAKE_BINARY_DIR}/source/repository
        ${CMAKE_BINARY_DIR}/source/api)

# Set project name
configure_file(
        "source/repository/RepositoryConfig.h.in"
        "source/repository/RepositoryConfig.h"
)

# Set the api key from an environment variable
set(FINANCIAL_API_KEY $ENV{STOCKS_APP_API_KEY})
configure_file(
        "source/api/FinancialmodelingApiKey.h.in"
        "source/api/FinancialmodelingApiKey.h"
)

# JSON Parser
include(FetchContent)
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
        URL_HASH SHA256=8c4b26bf4b422252e13f332bc5e388ec0ab5c3443d24399acb675e68278d341f
        DOWNLOAD_EXTRACT_TIMESTAMP true)

FetchContent_MakeAvailable(json)

# Testing with Catch/2
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests
        tests/test.cpp
        tests/repository/TestRepositoryConfig.cpp
        tests/repository/TestRepository.cpp
        tests/gui/utils/TestQuoteFormatter.cpp
        tests/gui/chartview/drawer/TestDateTimeCalculator.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
include(Catch)
catch_discover_tests(tests)

haiku_add_executable(${PROJECT_NAME}
        source/Stocks.rdef
        source/App.cpp
        source/gui/MainWindow.cpp
        source/gui/Colors.cpp
        source/gui/chartView/DetailsView.cpp
        source/gui/chartView/DetailsChart.cpp
        source/gui/chartView/DetailsDataList.cpp
        source/gui/chartView/DetailsHeadline.cpp
        source/gui/chartView/ChartTimeRangeBar.cpp
        source/gui/chartView/ChartView.cpp
        source/gui/chartView/drawer/GridlineDrawer.cpp
        source/gui/chartView/drawer/SeriesDrawer.cpp
        source/gui/chartView/drawer/DataSeriesLimiter.cpp
        source/gui/chartView/drawer/DateTimeCalculator.cpp
        source/gui/chartView/drawer/VerticalAxisDrawer.cpp
        source/gui/stocksPanel/StocksPanelView.cpp
        source/gui/stocksPanel/SearchFieldControl.cpp
        source/gui/stocksPanel/listView/QuoteListItem.cpp
        source/gui/stocksPanel/listView/FoundShareListItem.cpp
        source/gui/stocksPanel/listView/ShareListItem.cpp
        source/gui/utils/ListItemDrawer.cpp
        source/gui/utils/QuoteFormatter.cpp
        source/gui/utils/DelayedQueryTimer.cpp
        source/gui/utils/EscapeCancelFilter.cpp
        source/api/Financialmodelingprep.cpp
        source/api/FinancialmodelingApiKey.cpp
        source/api/NetRequester.cpp
        source/api/ApiBuilder.cpp
        source/model/Quote.cpp
        source/model/Portfolio.cpp
        source/model/SearchResultItem.cpp
        source/model/SearchResultList.cpp
        source/model/SelectionOfSymbols.cpp
        source/model/HistoricalPrice.cpp
        source/model/HistoricalPriceList.cpp
        source/repository/QuotesRepository.cpp
        source/repository/RepositoryConfig.cpp
        source/repository/Repository.cpp
        source/model/linkedRequestQuoteStore/BaseLinkedRequestToQuoteStore.cpp
        source/model/linkedRequestQuoteStore/QuoteRequestStore.cpp
        source/handler/QuoteResultHandler.cpp
        source/handler/HistoricalPriceResultHandler.cpp
        source/utils/BaseThreadedJob.cpp
        source/utils/ObservableSubject.cpp
        source/quoteUpdateJob/QuoteUpdateJob.cpp
)

target_link_directories(${PROJECT_NAME} PUBLIC /boot/system/develop/lib)
target_link_libraries(${PROJECT_NAME} be ${STDCPPLIBS} localestub network netservices2 bnetapi nlohmann_json::nlohmann_json)

if (HAIKU_ENABLE_I18N)
    set("${PROJECT_NAME}-APP_MIME_SIG" "application/x-vnd.tclaus-StocksApp")
    set("${PROJECT_NAME}-LOCALES" "en")
    haiku_add_i18n(${PROJECT_NAME})
endif ()