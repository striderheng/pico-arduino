## Project Status

- Basic Arduino API (e.g. String, Serial...) - completed
- digital input/output API - completed
- analog input/output API (PWM) - completed
- Multiprocessor support: queue, semaphore - completed
- tone - completed
- Arduino SPI API - completed
- PIO API class - completed
- Arduino I2C API - completed
- Software Serial using PIO - completed
- I2S API using PIO - open

## Change History

- __v0.1__ Initial Version with Baisic Functionality
- __v0.2__ SPI Support & error corrections
- __v0.3__ I2C Support & error corrections
- __v0.4__ Software Serial & error corrections
- __v0.5__ Error corrections, cleanup and more examples
     - HardwareSerial: Corrected slow print and println
     - analogWrite correction provided by Duke Dylan
     - Moved examples documentation into examples folder
     - Examples for HC-05 and ESP01
     - This release contains the following __Breaking Changes__
        - Changed signature of SoftwareSerial.begin() by switching the tx and rx sequence to be consistent with HardwareSerial
        - Removed unnecessary subfolders in ArduinoCore-Pico 
