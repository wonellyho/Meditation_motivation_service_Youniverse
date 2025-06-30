cmake_minimum_required(VERSION 3.16)

project(mainwindow VERSION 0.1 LANGUAGES CXX)

# 자동 UI/MOC/RCC 처리
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++17 사용
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 사용
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mainwindow
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        gpt_image_creator.py
        gpt_script_creator.py
        gpt_tts_creator.py
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET mainwindow APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(mainwindow SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(mainwindow
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(mainwindow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.mainwindow)
endif()
set_target_properties(mainwindow PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS mainwindow
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(mainwindow)
endif()



cmake_minimum_required(VERSION 3.16)
project(qt_test)

set(CMAKE_CXX_STANDARD 20)

# Qt 설치 경로 설정 (당신 환경에 맞게 수정됨)
set(Qt6_DIR "C:/Qt/6.9.0/mingw_64/lib/cmake/Qt6")

# Qt 필수 컴포넌트
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

# 자동 처리
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 실행 파일
add_executable(qt_test
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    # gpt_image_creator.py
    # gpt_script_creator.py
    # gpt_tts_creator.py

)

# 링크 Qt 라이브러리
target_link_libraries(qt_test PRIVATE Qt6::Widgets Qt6::Multimedia)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/image_prompt)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output_image)
