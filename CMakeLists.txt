cmake_minimum_required(VERSION 3.23)

project(Stocks)

set(CMAKE_MODULE_PATH "${Stocks_SOURCE_DIR}/CMakeModules")

include(UseHaiku)

set(CMAKE_CXX_STANDARD 11)
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
        model/Quote.h
        model/Quote.cpp
        )

include_directories(model
        gui/stocksPanel
        gui/chartView,
        gui/utils)

target_link_libraries(${PROJECT_NAME} "be")
