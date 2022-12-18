#include "usb_names.h"

#define MIDI_NAME {'P', 'h', 'o', 'e', 'n', 'i,', 'g', 's', '_', 'U', 'S', 'B', '_', 'V', '1', '.', '0'}
#define MIDI_NAME_LEN 17

struct usb_string_descriptor_struct usb_string_product_name = {
    2 + MIDI_NAME_LEN * 2,
    3,
    MIDI_NAME
};