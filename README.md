This is only example code to use tinyusb library
https://github.com/hathach/tinyusb
with esp32s2 arduino as component, before official arduino library is being released. 

It is not finished and probably never be, because it was more like excercise to learn and understand library and native USB.

In repository you can find few simple examples:
https://github.com/chegewara/esp32s2-tinyusb-arduino-as-component/tree/master/components/EspTinyUSB/examples


To use it its required to pull arduino-esp32 repository branch esp32s2 to components folder and https://github.com/hathach/tinyusb repository t library folder:
https://github.com/chegewara/esp32s2-tinyusb-arduino-as-component/tree/master/components/EspTinyUSB


Because of some dependency i had to modify 1 file in tinyusb to make it works:
https://github.com/hathach/tinyusb/blob/master/src/osal/osal_freertos.h#L31-L34

// FreeRTOS Headers
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/task.h"
