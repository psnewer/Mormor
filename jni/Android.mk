LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
OPENCV_CAMERA_MODULES:=off
OPENCV_INSTALL_MODULES:=on
include ../../sdk/native/jni/OpenCV.mk

LOCAL_MODULE    := bwlabel1
LOCAL_SRC_FILES := \
line_label.cpp\
Linelabel.cpp\
Getline.cpp\
morphing.cpp\
_Morphing.cpp\
_Firewall.cpp
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_LDLIBS    += -lm -llog -landroid -ljnigraphics
LOCAL_LDFLAGS += -fuse-ld=bfd
LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

include $(BUILD_SHARED_LIBRARY)
