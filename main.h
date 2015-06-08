#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "TLD/ViewController.h"
#include "TLD/VideoController.h"
#include "TLD/RandomFernsClassifier.h"
#include "TLD/NNClassifier.h"
#include "TLD/Detector.h"
#include "TLD/TLD.h"
#include "TLD/TLDSystemStruct.h"

void testOnVideo(std::string filename);
void stabilize();

#endif // MAIN_H
