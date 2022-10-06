# Universal_WS_DMX
A variant of the Universal_WS project controlled by DMX.

Requires ATmega328 (Arduino) and a MAX485 Module

Configured for 100 WS2811 pixels.

Connections:

  Arduino:
    GND -> GND
    VIN -> VCC 

  WS2811:
    GND -> GND
    VCC -> VCC  
    DAT -> Digital 6
    
  MAX485 Module:
    DE/RE -> GND
    RO -> RX
    VCC -> 5V
    GND -> GND
  
  XLR/DMX Connections:
    1 - Signal   (A)
    2 - Inverted (B)
    3 - Ground   (GND)
