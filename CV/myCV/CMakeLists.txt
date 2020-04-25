set(myCV_SRC
        interpolation.cpp
        translation.cpp
        tColor.cpp
        )

#add_executable(myCV ${myCV_SRC})
add_library(myCV ${myCV_SRC})
#target_link_libraries(myCV ${OpenCV_LIBS})
#
install(TARGETS myCV DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/CV/myCV)