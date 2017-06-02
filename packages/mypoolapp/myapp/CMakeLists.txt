

# Задание атрибутов приложения
set(PRJ_NAME myapp)
project(${PRJ_NAME})
cmake_policy(SET CMP0028 OLD)
cmake_policy(SET CMP0020 NEW)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)



# Формирование списка заголовочных файлов
file(GLOB_RECURSE SRC_H *.h)

# Формирование списка файлов с исходным кодом
file(GLOB_RECURSE SRC_C *.cpp)

# Формирование списка файлов с исходным кодом
file(GLOB_RECURSE SRC_UI *.ui)

include_directories (
	.
	${Qt5Core_INCLUDE_DIRS}
	${Qt5Gui_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5Xml_INCLUDE_DIRS}
	${Qt5OpenGL_INCLUDE_DIRS}
	#${GLUT_INCLUDE_DIRS}
)

set (SRS_RCC src/rsc.qrc)


set(GUI_TYPE WIN32)
qt5_add_resources(GL_RES ${SRC_RCC})
qt5_wrap_ui(_UI ${SRC_UI})

add_definitions(-D_USE_MATH_DEFINES)
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
add_definitions(-DLINUXAPI -std=c++11 )
else()
add_definitions(-DWIN32API )
#add_definitions(${GLUT_DEFINITIONS})
endif()
#
add_executable(${PRJ_NAME}  ${SRC_H} ${SRC_UI} ${SRC_C} ${GL_RES})


set(LIBS  )
if(MSVC)
target_link_libraries(
	${PRJ_NAME}
	Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml Qt5::OpenGL 
	${LIBS}
)

else()
target_link_libraries(
	${PRJ_NAME}
	Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml Qt5::OpenGL 
	${LIBS}
)
endif()
