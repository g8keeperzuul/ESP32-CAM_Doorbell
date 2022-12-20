#ifndef CAM_HELPER_H
#define CAM_HELPER_H

#include "esp_camera.h"
#include "log.h"

#define FLASH_LED_PIN 4

// *********************************************************************************************************************
// *** Data Types ***

// *********************************************************************************************************************
// *** Must Declare ***
//extern camera_fb_t *cam_frame_buf;
extern bool enable_flash;

// *********************************************************************************************************************
// *** Must Implement ***
bool initCamera();
//bool takePicture();
void initFlash(bool enable);
void sleepFlash();
void flashOn();
void flashOff();

#endif