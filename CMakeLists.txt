cmake_minimum_required(VERSION 3.10)
project(flappy VERSION 1.0)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем для MOC, UIC, RCC (обязательно для Qt)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Указываем CMake искать заголовки и исходники в подпапках
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Находим пакеты Qt
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Указываем все ваши исходные файлы
set(PROJECT_SOURCES
    main.cpp
    src/Core/MainWindow.cpp
    src/Game/GameWidget.cpp
)

# Указываем все ваши заголовочные файлы (для IDE)
set(PROJECT_HEADERS
    src/Core/MainWindow.h
    src/Game/GameWidget.h
    src/Game/Constants.h

)

# Создаем исполняемый файл
add_executable(FlappyBirdQt
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
)

# Указываем папки с заголовочными файлами
target_include_directories(FlappyBirdQt PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Game
)

# Линкуем (подключаем) библиотеки Qt к нашему приложению
target_link_libraries(FlappyBirdQt PUBLIC Qt::Widgets)
