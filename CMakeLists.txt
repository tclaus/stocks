cmake_minimum_required(VERSION 3.23)

project(
        Stocks
        VERSION 0.1
        DESCRIPTION "A stocks application to set up a portfolio and see updated data"
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


include(UseHaiku)


option(STRICT_WARNINGS "Compile with extra warnings and errors" ON)
if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 2.96 AND STRICT_WARNINGS)
    add_compile_options(-Wall -Wextra -Wshadow -Werror)
    if (USE_CLANG)
        # clang finds a lot more problems than gcc, disable some of the warnings
        # set these here instead of earlier, they must come after -Wall, -Werror, etc...
        add_compile_options(-Wno-overloaded-virtual -Wno-unused-private-field
                -Wno-return-type-c-linkage -Wno-unused-const-variable
                -Wno-deprecated-register)
    endif ()
endif ()

include_directories(AFTER
        /boot/system/develop/headers/private/netservices2
        source/model
        source/gui/stocksPanel
        source/gui/stocksPanel/listView
        source/gui/chartView
        source/gui/utils
        source/api)

# JSON Parser
include(FetchContent)
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP true)

FetchContent_MakeAvailable(json)

find_library(network NAMES network PATHS /boot/system/develop/lib/ REQUIRED)
find_library(bnetapi NAMES bnetapi PATHS /boot/system/develop/lib/ REQUIRED)
find_library(netservices2 NAMES netservices2 PATHS /boot/system/develop/lib REQUIRED)

link_directories(/boot/system/develop/lib/)

haiku_add_executable(${PROJECT_NAME}
        source/App.cpp
        source/App.h
        source/gui/MainWindow.h
        source/gui/MainWindow.cpp
        source/gui/chartView/ChartView.h
        source/gui/chartView/ChartView.cpp
        source/gui/stocksPanel/StocksPanelView.h
        source/gui/stocksPanel/StocksPanelView.cpp
        source/gui/stocksPanel/SearchFieldControl.h
        source/gui/stocksPanel/SearchFieldControl.cpp
        source/gui/stocksPanel/StockListItemBuilder.h
        source/gui/stocksPanel/StockListItemBuilder.cpp
        source/gui/stocksPanel/ListItemConstants.h
        source/gui/stocksPanel/listView/QuoteListItem.h
        source/gui/stocksPanel/listView/QuoteListItem.cpp
        source/gui/stocksPanel/listView/FoundShareListItem.h
        source/gui/stocksPanel/listView/FoundShareListItem.cpp
        source/gui/stocksPanel/listView/ShareListItem.h
        source/gui/stocksPanel/listView/ShareListItem.cpp
        source/gui/utils/ListItemDrawer.h
        source/gui/utils/ListItemDrawer.cpp
        source/gui/utils/QuoteFormatter.h
        source/gui/utils/QuoteFormatter.cpp
        source/gui/utils/DelayedQueryTimer.h
        source/gui/utils/DelayedQueryTimer.cpp
        source/gui/utils/EscapeCancelFilter.h
        source/gui/utils/EscapeCancelFilter.cpp
        source/api/StockConnector.h
        source/api/Financialmodelingprep.h
        source/api/Financialmodelingprep.cpp
        source/api/NetRequester.h
        source/api/NetRequester.cpp
        source/api/ApiBuilder.h
        source/api/ApiBuilder.cpp
        source/model/Quote.cpp
        source/model/Quote.h
        source/model/Portfolio.h
        source/model/Portfolio.cpp
        source/model/SearchResultItem.h
        source/model/SearchResultItem.cpp
        source/model/SearchResultList.h
        source/model/SearchResultList.cpp
        )

target_link_directories(${PROJECT_NAME} PRIVATE /boot/system/develop/lib)
target_link_libraries(${PROJECT_NAME} be ${STDCPPLIBS} network netservices2 bnetapi nlohmann_json::nlohmann_json)

