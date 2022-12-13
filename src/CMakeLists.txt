add_executable (Tailor "Tailor.cpp" "Tailor.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tailor PROPERTY CXX_STANDARD 20)
endif()


find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)


target_include_directories(Tailor PUBLIC         
    ${GLFW3_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
)

target_link_libraries(Tailor PUBLIC        
    glfw
    OpenGL::GL    
    ${FREETYPE_LIBRARIES}
)