# Формирование переменных для подключения ГИС-компонентов из репозитория 
set(DEPS_INSTALL_PATH ${ITAIN_ROOT_PATH})
set(DEPS_INCLUDE_PATH ${ITAIN_ROOT_PATH})
set(DEPS_BIN_PATH ${ITAIN_ROOT_PATH})
set(DEPS_LIB_PATH ${ITAIN_ROOT_PATH})

set(MODULE_INCLUDE_PATH ${ITAIN_ROOT_PATH})    # Каталог для размещения заголовочных файлов
set(MODULE_LIB_PATH ${ITAIN_ROOT_PATH})            # Каталог для размещения библиотек
set(MODULE_QM_PATH ${ITAIN_ROOT_PATH})              # Каталог для размещения файлов переводов
set(MODULE_DATA_PATH ${ITAIN_ROOT_PATH})          # Каталог для размещения файлов данных


find_package(Qt5Gui  REQUIRED)
find_package(Qt5Core  REQUIRED)
find_package(Qt5Widgets  REQUIRED)
find_package(Qt5Xml  REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Network REQUIRED)
