if($ENV{WITH_QT})
    find_package(Qt4 REQUIRED)

    set(SOI_QTGUI_SOURCES main.cpp main_window.cpp thread.cpp graphic_widget.cpp)
    set(SOI_QTGUI_HEADERS main_window.h thread.h graphic_widget.h)

    QT4_WRAP_CPP(SOI_QTGUI_HEADERS_MOC ${SOI_QTGUI_HEADERS})

    include(${QT_USE_FILE})
    add_definitions(${QT_DEFINITIONS})

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g -Wall -Werror -Wextra -pedantic -Wno-long-long")

    add_executable(soi_qtgui ${SOI_QTGUI_SOURCES} ${SOI_QTGUI_HEADERS_MOC})
    target_link_libraries(soi_qtgui ${QT_LIBRARIES} helpers)
endif($ENV{WITH_QT})
