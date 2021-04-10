include(ExternalProject)
ExternalProject_Add(opencv3_downloaded
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/opencv_install
    GIT_TAG 3.4.11
    CMAKE_ARGS -DBUILD_JAVA=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_PROTOBUF=OFF -DBUILD_opencv_apps=OFF -DBUILD_opencv_python3=OFF -DWITH_PROTOBUF=OFF
)


add_library(opencv_3rdparty INTERFACE)
target_link_libraries(opencv_3rdparty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/lib/libopencv_core.so)
target_link_libraries(opencv_3rdparty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/lib/libopencv_highgui.so)
target_link_libraries(opencv_3rdparty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/lib/libopencv_imgproc.so)
target_link_libraries(opencv_3rdparty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/lib/libopencv_videoio.so)
target_link_libraries(opencv_3rdparty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/lib/libopencv_imgcodecs.so)
target_include_directories(opencv_3rdparty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/opencv_install/include)
add_dependencies(opencv_3rdparty opencv3_downloaded)


ExternalProject_Add(raspicam_downloaded
    GIT_REPOSITORY https://github.com/cedricve/raspicam.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/raspicam_install -DOpenCV_DIR=${CMAKE_CURRENT_BINARY_DIR}/opencv_install/share/OpenCV
)

add_library(raspicam_3rdParty INTERFACE)
target_link_libraries(raspicam_3rdParty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/raspicam_install/lib/libraspicam_cv.so)
target_include_directories(raspicam_3rdParty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/raspicam_install/include)
add_dependencies(raspicam_3rdParty raspicam_downloaded)

add_dependencies(raspicam_3rdParty opencv_3rdparty)




ExternalProject_Add(rapidjson_downloaded
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/install
)
add_library(rapidjson_3rdParty INTERFACE)
target_include_directories(rapidjson_3rdParty INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/rapidjson_3rdParty/include)

