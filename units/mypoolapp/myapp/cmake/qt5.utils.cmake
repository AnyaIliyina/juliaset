#========================================================================================
#=== Генерация *.схх из ts-файла для последующего включения в ресурсы ===================
#========================================================================================
function(qt5_ts2qrc pathTS)
   get_filename_component(filenameTS ${pathTS} NAME_WE)
   set(pathQM ${PROJECT_BINARY_DIR}/${filenameTS}.qm)
   set(pathQRC ${PROJECT_BINARY_DIR}/${filenameTS}.qrc)

   # генерация qm-файла
   exec_program(${QT_LRELEASE_EXECUTABLE} ${PROJECT_SOURCE_DIR} ARGS ${pathTS} -qm ${pathQM})

   # формирование qrc-файла
   file(WRITE ${pathQRC} "<RCC>\n\t<qresource prefix=\"/translate\">")
   file(APPEND ${pathQRC} "\n\t\t<file alias=\"${filenameTS}\">${filenameTS}.qm</file>")
   file(APPEND ${pathQRC} "\n\t</qresource>\n</RCC>")
endfunction()
