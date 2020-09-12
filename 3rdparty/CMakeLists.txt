include(ExternalProject)
ExternalProject_Add(opencv3_downloaded
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/opencv_install
    GIT_TAG 3.4.11
    CMAKE_ARGS -DBUILD_JAVA=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_PROTOBUF=OFF -DBUILD_opencv_apps=OFF -DBUILD_opencv_python3=OFF -DWITH_PROTOBUF=OFF
)

# add_library(opencv_core SHARED IMPORTED ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/lib/libopencv_core.so)
add_library(opencv_3rdparty INTERFACE)
target_link_libraries(opencv_3rdparty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/lib/libopencv_core.so)
target_link_libraries(opencv_3rdparty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/lib/libopencv_highgui.so)
target_link_libraries(opencv_3rdparty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/lib/libopencv_imgproc.so)
target_link_libraries(opencv_3rdparty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/lib/libopencv_videoio.so)
target_link_libraries(opencv_3rdparty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/lib/libopencv_imgcodecs.so)
target_include_directories(opencv_3rdparty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/include)
add_dependencies(opencv_3rdparty opencv3_downloaded)
