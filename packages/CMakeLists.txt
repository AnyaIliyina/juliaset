# Ограничение на минимальную версию CMake
cmake_minimum_required(VERSION 2.8)

# Задание атрибутов приложения/проекта
project(Packages)

# Настройка путей для приложений
set(APP_LIB_PATH ${GEODEV_INSTALL_LIB_PATH})
set(APP_INCLUDE_PATH ${GEODEV_INSTALL_API_PATH})


# Добавление подпроектов
#add_subdirectory(editor/scheduler)

