#pragma once

struct eeprom_data {
    const char *contents;
    const char *data;
    const char *label;
};

struct eeprom_data *eeprom_init(void);
