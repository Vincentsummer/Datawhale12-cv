set(myCV_SRC
        interpolation.cpp
        )

add_library(myCV ${myCV_SRC})
target_link_libraries(myCV)

install(TARGETS myCV DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/CV/myCV)