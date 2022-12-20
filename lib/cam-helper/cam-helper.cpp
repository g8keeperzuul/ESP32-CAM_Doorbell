#include "cam-helper.h"

// Camera buffer, URL and picture name
//camera_fb_t *cam_frame_buf = NULL;
bool enable_flash;

void initFlash(bool enable)
{
  enable_flash = enable;
  if(enable_flash){
    pinMode(FLASH_LED_PIN, OUTPUT);  
  }
}
void sleepFlash()
{
  // if left in OUTPUT mode, the flash led draws power so that it is faintly lit.
  // switching to INPUT mode before deep sleep doesn't fix the problem
  //pinMode(FLASH_LED_PIN, INPUT); 
}
void flashOn()
{
  if(enable_flash){
    digitalWrite(FLASH_LED_PIN, HIGH);
    //delay(1000);
  }
}
void flashOff()
{
  if(enable_flash){
    digitalWrite(FLASH_LED_PIN, LOW);
  }
}

bool initCamera()
{  
  // IF USING A DIFFERENT BOARD, NEED DIFFERENT PINs
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = 5;
  config.pin_d1       = 18;
  config.pin_d2       = 19;
  config.pin_d3       = 21;
  config.pin_d4       = 36;
  config.pin_d5       = 39;
  config.pin_d6       = 34;
  config.pin_d7       = 35;
  config.pin_xclk     = 0;
  config.pin_pclk     = 22;
  config.pin_vsync    = 25;
  config.pin_href     = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_pwdn     = 32;
  config.pin_reset    = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG; // https://github.com/espressif/esp32-camera/blob/master/driver/include/sensor.h#L72

  // if(psramFound()){
  //   config.frame_size = FRAMESIZE_UXGA; // set picture size; https://github.com/espressif/esp32-camera/blob/master/driver/include/sensor.h#L84
  //   config.jpeg_quality = 10;           // quality of JPEG output. 0-63 lower means higher quality
  //   config.fb_count = 2;
  // } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 10;
    config.fb_count = 3;
  // }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK)
  {
    Sprint("Camera init failed with error 0x");
    Sprintln(err);
    return false;
  }

  // Change extra settings if required
  //sensor_t * s = esp_camera_sensor_get();
  //s->set_vflip(s, 0);       //flip it back
  //s->set_brightness(s, 1);  //up the blightness just a bit
  //s->set_saturation(s, -2); //lower the saturation

  else
  {
    return true;
  }  
}

/*
bool takePicture()
{
  Sprintln("Taking picture now");

  cam_frame_buf = esp_camera_fb_get();  
  if(!cam_frame_buf)
  {
    Sprintln("Camera capture failed");
    return false;
  }
  
  Sprintln("Camera capture success");

  return true;
}
*/