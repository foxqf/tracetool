SET(TRACE2XML_SOURCES
        main.cpp
        ../server/database.cpp)

IF(MSVC)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
ENDIF(MSVC)

ADD_EXECUTABLE(trace2xml MACOSX_BUNDLE ${TRACE2XML_SOURCES})
TARGET_LINK_LIBRARIES(trace2xml Qt5::Sql)

INSTALL(TARGETS trace2xml RUNTIME DESTINATION bin COMPONENT applications
                          LIBRARY DESTINATION lib COMPONENT applications
                          BUNDLE  DESTINATION bin COMPONENT applications
                          ARCHIVE DESTINATION lib COMPONENT applications)
