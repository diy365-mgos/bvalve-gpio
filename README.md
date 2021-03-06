# bValves GPIO Library
## Overview
Mongoose-OS library that allows you to easily attach a [bValve](https://github.com/diy365-mgos/bvalve) to a GPIO.
## GET STARTED
You can start from one of these examples:
* [Control a solenoid valve using MQTT](/examples/solenoid_valve.md)
* [Control a bistable valve using MQTT](/examples/bistable_valve.md)
* [Control a motorized valve using MQTT (L293D version)](/examples/motorized_valve(L293D).md)
* [Control a motorized valve using MQTT (relays version)](/examples/motorized_valve(relays).md)
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
|active_high|`true` if the `pin` GPIO is `on` when output is high (1).|

**MGOS_BVALVE_TYPE_BISTABLE**
```c
bool mgos_bvalve_gpio_attach(mgos_bvalve_t valve,
                             int pin1, bool pin1_active_high,
                             int pin2, bool pin2_active_high,
                             int pulse_duration);
```
|Parameter||
|--|--|
|valve|A bValve of type `MGOS_BVALVE_TYPE_BISTABLE`.|
|pin1|The GPIO pin to use to open the valve.|
|pin1_active_high|`true` if the `pin1` GPIO is `on` when output is high (1).|
|pin2|The GPIO pin to use to close the valve.|
|pin2_active_high|`true` if the `pin2` GPIO is `on` when output is high (1).|
|pulse_duration|Milliseconds. The pulse duration for opening/closing the valve.|

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
|pin1|The GPIO pin to use to open/close/power the valve.|
|pin1_active_high|`true` if the `pin1` GPIO is `on` when output is high (1).|
|pin2|The GPIO pin to use to open/close/power the valve.|
|pin2_active_high|`true` if the `pin2` GPIO is `on` when output is high (1).|
|pulse_duration|Seconds. The pulse duration for opening/closing the valve.|
|gpio_power|The [power setting](#mgos_bvalve_gpio_power) to use for powering the valve.|

The value of the `gpio_power` parameter affects the use of pins according to the following schema:

|gpio_power / pin|pin1|pin2|
|--|--|--|
|MGOS_BVALVE_GPIO_POWER_NONE|**Open** the valve.|**Close** the valve.|
|MGOS_BVALVE_GPIO_POWER_PIN1|**Power** the valve.|**Open**/**Close** the valve.|
|MGOS_BVALVE_GPIO_POWER_PIN2|**Open**/**Close** the valve.|**Power** the valve.|
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).