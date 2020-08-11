cmake_minimum_required(VERSION 3.6.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configuring project")

set(INCLUDE_DIR include)
set(LIB_DIR lib)
set(SRC_DIR src)
set(RES_DIR res)

# include目录和lib目录
message(STATUS "Configuring include and lib directory")
include_directories(${INCLUDE_DIR})
link_directories(${LIB_DIR})

# 拷贝资源
message(STATUS "Copying shader")
file(COPY ${SRC_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${RES_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(HEADER_FILES
    ${SRC_DIR}/camera.h
    ${SRC_DIR}/controller.h
    ${SRC_DIR}/globals.h
    ${SRC_DIR}/main.h
    ${SRC_DIR}/scene.h
    ${SRC_DIR}/scene_colorrect.h
    ${SRC_DIR}/scene_texturerect.h
    ${SRC_DIR}/scenecontroller.h
    ${SRC_DIR}/scenemgr.h
    ${SRC_DIR}/shader.h
    ${SRC_DIR}/stb_image.h
    ${SRC_DIR}/texture.h
    ${SRC_DIR}/utils.h
)

set(SOURCE_FILES
    ${SRC_DIR}/camera.cpp
    ${SRC_DIR}/controller.cpp
    ${SRC_DIR}/glad.c
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/scene.cpp
    ${SRC_DIR}/scene_colorrect.cpp
    ${SRC_DIR}/scene_texturerect.cpp
    ${SRC_DIR}/scenecontroller.cpp
    ${SRC_DIR}/scenemgr.cpp
    ${SRC_DIR}/shader.cpp
    ${SRC_DIR}/stb_image.cpp
    ${SRC_DIR}/texture.cpp
    ${SRC_DIR}/utils.cpp
)

message(STATUS "Configuring source files and header files")
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# 链接lib
set(LIB_FILES
    glfw3.lib
    assimp.lib
)
message(STATUS "Configuring target libs")
target_link_libraries(${PROJECT_NAME} ${LIB_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
include(CPack)
# 设置启动项目
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
