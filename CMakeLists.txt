cmake_minimum_required(VERSION 3.23)

project(Stocks)

set(CMAKE_MODULE_PATH "${Stocks_SOURCE_DIR}/CMakeModules")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

include(UseHaiku)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED False) # Set to true once we know better what to do

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

include_directories(AFTER SYSTEM
        /boot/system/develop/headers/private/netservices2
        model
        gui/stocksPanel
        gui/chartView
        gui/utils
        api)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP true)

FetchContent_MakeAvailable(json)

find_library(network NAMES network PATHS /boot/system/develop/lib/ REQUIRED)
find_library(bnetapi NAMES bnetapi PATHS /boot/system/develop/lib/ REQUIRED)
find_library(netservices2 NAMES netservices2 PATHS /boot/system/develop/lib REQUIRED)

link_directories(/boot/system/develop/lib/)

haiku_add_executable(${PROJECT_NAME}
        App.cpp
        App.h
        gui/MainWindow.h
        gui/MainWindow.cpp
        gui/chartView/ChartView.h
        gui/chartView/ChartView.cpp
        gui/stocksPanel/StocksPanelView.h
        gui/stocksPanel/StocksPanelView.cpp
        gui/stocksPanel/SearchFieldControl.h
        gui/stocksPanel/SearchFieldControl.cpp
        gui/stocksPanel/QuoteListItem.h
        gui/stocksPanel/QuoteListItem.cpp
        gui/stocksPanel/StockListItemBuilder.h
        gui/stocksPanel/StockListItemBuilder.cpp
        gui/utils/ListItemDrawer.h
        gui/utils/ListItemDrawer.cpp
        gui/utils/QuoteFormatter.h
        gui/utils/QuoteFormatter.cpp
        api/StockConnector.h
        api/StockConnector.cpp
        api/Financialmodelingprep.h
        api/Financialmodelingprep.cpp
        api/NetRequester.h
        api/NetRequester.cpp
        api/ApiBuilder.h
        api/ApiBuilder.cpp
        model/Quote.cpp
        model/Quote.h
        model/Portfolio.h
        model/Portfolio.cpp
        model/SearchResultItem.h
        model/SearchResultItem.cpp
        model/SearchResultList.h
        model/SearchResultList.cpp
        )

target_link_directories(${PROJECT_NAME} PRIVATE /boot/system/develop/lib)
target_link_libraries(${PROJECT_NAME} be ${STDCPPLIBS} network netservices2 bnetapi nlohmann_json::nlohmann_json)

