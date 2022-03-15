/*
 * Copyright (c) 2021 DIY356
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MGOS_BVALVE_GPIO_H_
#define MGOS_BVALVE_GPIO_H_

#include <stdbool.h>
#include <stdarg.h>
#include "mgos_bvalve.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mgos_bvalve_gpio_power {
  MGOS_BVALVE_GPIO_POWER_NONE = 0,
  MGOS_BVALVE_GPIO_POWER_PIN1 = 1,
  MGOS_BVALVE_GPIO_POWER_PIN2 = 2,
};

bool mgos_bvalve_gpio_attach(mgos_bvalve_t valve, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MGOS_BVALVE_GPIO_H_ */