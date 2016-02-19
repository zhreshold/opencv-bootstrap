CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#-------------------- WHAT TO CONFIG ------------------------#
SET(PROJECT_NAME "opencv-bootstrap")	# The project name 工程名
SET(LINK_OPENCV_STATIC ON)	# Use static library or not 是否链接静态运行库
SET(CUSTOM_OPENCV_DIR "D:\\Dev\\tmp\\opencv\\build") # where OpenCV reside in OpenCV实际路径
SET(USE_CUSTOM_OPENCV_DIR_IN_NIX OFF) # Most likely you don't need to specify it in *nix 
#------------------------------------------------------------#







#-------------------- NO MIDIFICATION ------------------------#
PROJECT(${PROJECT_NAME})
IF(${LINK_OPENCV_STATIC})
	SET(OpenCV_STATIC ON)
	IF ( MSVC )
		SET ( CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd" )
		SET ( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT" )
		SET ( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd" )
		SET ( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT" )
	ENDIF ( MSVC )
ELSE()
	SET(OpenCV_STATIC OFF)
ENDIF(${LINK_OPENCV_STATIC})

IF(WIN32)
	SET(OpenCV_DIR ${CUSTOM_OPENCV_DIR})
ELSE()
	IF(${USE_CUSTOM_OPENCV_DIR_IN_NIX})
		SET(OpenCV_DIR ${CUSTOM_OPENCV_DIR}) # set dir in unix only if you required
	ENDIF(${USE_CUSTOM_OPENCV_DIR_IN_NIX})
ENDIF(WIN32)

FIND_PACKAGE(OpenCV REQUIRED)
FILE(GLOB ALL_HEADERS "../src/*.h*")
FILE(GLOB ALL_SOURCES "../src/*.c*")
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS} "../include")

ADD_EXECUTABLE(${PROJECT_NAME} ${ALL_HEADERS} ${ALL_SOURCES})
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${OpenCV_LIBS} )
