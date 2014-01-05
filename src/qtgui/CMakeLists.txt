find_package(Qt4 REQUIRED)

set(SOI_QTGUI_SOURCES main.cpp main_window.cpp thread.cpp)
set(SOI_QTGUI_HEADERS main_window.h thread.h)

QT4_WRAP_CPP(SOI_QTGUI_HEADERS_MOC ${SOI_QTGUI_HEADERS})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_executable(soi_qtgui ${SOI_QTGUI_SOURCES} ${SOI_QTGUI_HEADERS_MOC})
target_link_libraries(soi_qtgui ${QT_LIBRARIES} helpers)
