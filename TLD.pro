CONFIG += c++11

HEADERS += \
    TLD/Detector.h \
    TLD/Learner.h \
    TLD/NNClassifier.h \
    TLD/RandomFernsClassifier.h \
    TLD/TLD.h \
    TLD/TLDSystemStruct.h \
    TLD/VarClassifier.h \
    TLD/VideoController.h \
    TLD/ViewController.h \
    MedianFlow/MedianFlow/OpticalFlow.h \
    MedianFlow/MedianFlow/MedianFlow.h \
    main.h

SOURCES += \
    TLD/Detector.cpp \
    TLD/Learner.cpp \
    TLD/main.cpp \
    TLD/NNClassifier.cpp \
    TLD/RandomFernsClassifier.cpp \
    TLD/TLD.cpp \
    TLD/VarClassifier.cpp \
    TLD/VideoController.cpp \
    TLD/ViewController.cpp \
    MedianFlow/MedianFlow/OpticalFlow.cpp \
    MedianFlow/MedianFlow/MedianFlow.cpp

LIBS += /usr/local/lib/libopencv*.so
