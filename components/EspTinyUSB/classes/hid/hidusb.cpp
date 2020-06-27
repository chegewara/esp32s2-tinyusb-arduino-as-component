#include "Arduino.h"
#include "tusb.h"
#include "soc/rtc_cntl_reg.h"

#include "hidusb.h"
#define EPNUM_HID   0x05

static HIDusb *_hidUSB = NULL;

HIDusb::HIDusb()
{
    enableHID = true;
    _hidUSB = this;
}

uint8_t const desc_hid_report[] = {TUD_HID_REPORT_DESC_GENERIC_INOUT(CFG_TUD_HID_BUFSIZE)};
bool HIDusb::begin()
{
    // Interface number, string index, protocol, report descriptor len, EP In address, size & polling interval
    // uint8_t hid[] = {TUD_HID_DESCRIPTOR(ifIdx++, 6, HID_PROTOCOL_NONE, sizeof(desc_hid_report), 0x83, 16, 10)};
    uint8_t hid[] = {TUD_HID_INOUT_DESCRIPTOR(ifIdx++, 0, HID_PROTOCOL_NONE, sizeof(desc_hid_report), EPNUM_HID, 0x80 | EPNUM_HID, CFG_TUD_HID_BUFSIZE, 10)};
    
    memcpy(&desc_configuration[total], hid, sizeof(hid));
    total += sizeof(hid);
    count++;
    if (!EspTinyUSB::begin()) return false;
    return true;
}

void HIDusb::onData(hid_on_data_t cb)
{
    _data_cb = cb;
}

// Invoked when received GET HID REPORT DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint8_t const * tud_hid_descriptor_report_cb(void)
{
    return desc_hid_report;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  // This example doesn't use multiple report and report ID
  (void) report_id;
  (void) report_type;

  // echo back anything we received from host
  // tud_hid_report(0, buffer, bufsize);
  if(_hidUSB->_data_cb) {
    _hidUSB->_data_cb(report_id, (uint8_t)report_type, buffer, bufsize);
  }
}
