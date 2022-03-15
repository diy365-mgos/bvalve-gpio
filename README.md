# bValves GPIO Library
## Overview
Mongoose-OS library that allows you to easily attach a [bValve](https://github.com/diy365-mgos/bvalve) to a GPIO for measuring signal frequency and calculating the flow volume.
## C/C++ APIs Reference
### mgos_bvalve_gpio_power
```c
enum mgos_bvalve_gpio_power {
  MGOS_BVALVE_GPIO_POWER_NONE = 0,
  MGOS_BVALVE_GPIO_POWER_PIN1 = 1,
  MGOS_BVALVE_GPIO_POWER_PIN2 = 2,
};
```
Power settings for bValves of [type](https://github.com/diy365-mgos/bvalve#mgos_bvalve_type) `MGOS_BVALVE_TYPE_BISTABLE`. Used by `mgos_bvalve_gpio_attach()`.

|Value||
|--|--|
|MGOS_BVALVE_GPIO_POWER_NONE|The valve's power supply is not managed using GPIOs.|
|MGOS_BVALVE_GPIO_POWER_PIN1|The valve's power supply is controlled by the `pin1` GPIO.|
|MGOS_BVALVE_GPIO_POWER_PIN2|The valve's power supply is controlled by the `pin2` GPIO.|
### mgos_bvalve_gpio_attach
```c
bool mgos_bvalve_gpio_attach(mgos_bvalve_t valve, ...);
```
Initializes GPIOs and attaches them to a bValve. Returns `true` on success, or `false` otherwise. Dynamic parameters depend on the [bValve type](https://github.com/diy365-mgos/bvalve#mgos_bvalve_type):

**MGOS_BVALVE_TYPE_SOLENOID**
```c
bool mgos_bvalve_gpio_attach(mgos_bvalve_t valve, int pin, bool active_high);
```
|Parameter||
|--|--|
|valve|A bValve of type `MGOS_BVALVE_TYPE_SOLENOID`.|
|pin|The GPIO pin.|
|active_high|`true` if the `pin` GPIO is on when output is high (1).|
**MGOS_BVALVE_TYPE_BISTABLE**
```c
bool mgos_bvalve_gpio_attach(mgos_bvalve_t valve,
                             int vcc_pin, bool vcc_active_high,
                             int gnd_pin, bool gnd_active_high,
                             int pulse_duration);
```
|Parameter||
|--|--|
|valve|A bValve of type `MGOS_BVALVE_TYPE_BISTABLE`.|
|vcc_pin|The valve's `VCC` GPIO pin.|
|vcc_active_high|`true` if the `vcc_pin` GPIO is on when output is high (1).|
|gnd_pin|The valve's `GND` GPIO pin.|
|gnd_active_high|`true` if the `gnd_pin` GPIO is on when output is high (1).|
|pulse_duration|The pulse duration in milliseconds for opening/closing the valve.|
**MGOS_BVALVE_TYPE_MOTORIZED**
```c
bool mgos_bvalve_gpio_attach(mgos_bvalve_t valve,
                             int pin1, bool pin1_active_high,
                             int pin2, bool pin2_active_high,
                             int pulse_duration,
                             enum mgos_bvalve_gpio_power gpio_power);
```
|Parameter||
|--|--|
|valve|A bValve of type `MGOS_BVALVE_TYPE_MOTORIZED`.|
|pin1|The `pin1` GPIO pin.|
|pin1_active_high|`true` if the `pin1` GPIO is on when output is high (1).|
|pin2|The `pin2` GPIO pin.|
|pin2_active_high|`true` if the `pin2` GPIO is on when output is high (1).|
|pulse_duration|The pulse duration in seconds for opening/closing the valve.|
|gpio_power|The power setting to use for powering the valve.|

The 
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).