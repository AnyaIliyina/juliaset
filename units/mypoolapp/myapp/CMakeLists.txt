# Ограничение на минимальную версию CMake
cmake_minimum_required(VERSION 2.8)

# Задание атрибутов приложения/проекта
set(PRJ_NAME myapp)
project(${PRJ_NAME})

# Настройка типа сборки
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_COLOR_MAKEFILE ON)
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
#
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
   set(BUILD_OPTIONS
#      -O2           # средняя оптимизация для проверки кода к оптимизациям
#      -Wall          # вывод сообщений о всех предупреждениях или ошибках, возникающих во время компиляции
      )
elseif()
   set(BUILD_OPTIONS
      -Ofast         # аналогично "-O3 -ffast-math", более высокий уровень оптимизаций и более агрессивные оптимизации для арифметических вычислений
      -funroll-loops # разворачивание циклов
      )
endif()
add_definitions(${BUILD_OPTIONS})

# Указание различных путей
set(GEODEV_PATH ${PROJECT_SOURCE_DIR}/../../../) 
set(GEODEV_INSTALL_PATH ${GEODEV_PATH}/bin/mypoolapp/myapp)
set(ITAIN_ROOT_PATH ${PROJECT_SOURCE_DIR}/../../../)        # Корневой каталог репозитория

# Определение типа платформы
message(STATUS "Cmake platform = ${CMAKE_SYSTEM_NAME}")
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
   add_definitions("-D_LINUX")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
   add_definitions("-D_WINDOWS" -W0)
endif()

# В DEBUG-режиме всё будет собираться сразу в инсталяционный каталог
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
   set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GEODEV_INSTALL_PATH})
   set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GEODEV_INSTALL_PATH})
   set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GEODEV_INSTALL_PATH})
endif()

set(LINK_TYPE "SHARED")          # как линковать библиотеки (STATIC или SHARED)


# Подключение и настройка всех необходимых подпроектов
include(../../GenerateSourceGroups.cmake)
include(cmake/deps.cmake)
