# ESP32-C6-LCD147-demos

This is sample code for ESP32 C6 board with 1.47in LCD screen. It is a cool, and inexpensive board available on Aliexpress etc. However the standard LCD display samples did not work

Here are a few samples that I made that are working.

ESP32-C6-LCD147-demos

Main problem is to ensure that Hardware SPI is used and the corrent LCD pins are used.

<code>
Arduino_DataBus *bus = new Arduino_HWSPI(15 /* DC */, 14 /* CS */, 7 /* SCK */, 6 /* MOSI */, GFX_NOT_DEFINED /* MISO */);
Arduino_GFX *gfx = new Arduino_ST7789(bus,21,0,true,210,320);
</code>

