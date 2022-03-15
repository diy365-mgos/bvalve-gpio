#include "mgos.h"
#include "mgos_bvalve_gpio.h"
#include "mgos_bvalve.h"

#ifdef MGOS_HAVE_MJS
#include "mjs.h"
#endif

struct mg_bvalve_gpio_cfg {
  mgos_bvalve_t valve;
  int pin1;
  bool pin1_active_high;
  int pin2;
  bool pin2_active_high;
  enum mgos_bvalve_gpio_power gpio_power;
  int pulse_duration;
};

// bool mg_bvalve_gpio_get_state_cb(mgos_bthing_t thing, mgos_bvar_t state, void *userdata) {
//   struct mg_bvalve_gpio_cfg *cfg = (struct mg_bvalve_gpio_cfg *)userdata;
//   if (thing && state && cfg) {
//     //mgos_bvar_set_integer(state);
//     return true;
//   }
//   return false;
// }

bool mg_bvalve_gpio_set_closed_solenoid(struct mg_bvalve_gpio_cfg *cfg, enum mgos_bvalve_state state) {
  enum mgos_bvalve_type valve_type = mgos_bvalve_get_type(cfg->valve);
  // I must CLOSE the solenoid valve...
  if ((valve_type & MGOS_BVALVE_TYPE_NO) == MGOS_BVALVE_TYPE_NO) {
    // The valve is NO, so pin1 must be activated to close it
    mgos_gpio_write(cfg->pin1, (cfg->pin1_active_high ? true : false));
    return (mgos_gpio_read(cfg->pin1) == (cfg->pin1_active_high ? true : false));
  } else if ((valve_type & MGOS_BVALVE_TYPE_NC) == MGOS_BVALVE_TYPE_NC) {
    // The valve is NC, so pin1 must be deactivated to close it
    mgos_gpio_write(cfg->pin1, (cfg->pin1_active_high ? false : true));
    return (mgos_gpio_read(cfg->pin1) == (cfg->pin1_active_high ? false : true));
  }
  return false;
}

bool mg_bvalve_gpio_set_open_solenoid(struct mg_bvalve_gpio_cfg *cfg, enum mgos_bvalve_state state) {
  enum mgos_bvalve_type valve_type = mgos_bvalve_get_type(cfg->valve);
  // I must OPEN the solenoid valve...
  if ((valve_type & MGOS_BVALVE_TYPE_NC) == MGOS_BVALVE_TYPE_NC) {
    // The valve is NC, so pin1 must be activated to open it
    mgos_gpio_write(cfg->pin1, (cfg->pin1_active_high ? true : false));
    return (mgos_gpio_read(cfg->pin1) == (cfg->pin1_active_high ? true : false));
  } else if ((valve_type & MGOS_BVALVE_TYPE_NO) == MGOS_BVALVE_TYPE_NO) {
    // The valve is NO, so pin1 must be deactivated to open it
    mgos_gpio_write(cfg->pin1, (cfg->pin1_active_high ? false : true));
    return (mgos_gpio_read(cfg->pin1) == (cfg->pin1_active_high ? false : true));
  }
  return false;
}

bool mg_bvalve_gpio_set_state_solenoid(struct mg_bvalve_gpio_cfg *cfg, enum mgos_bvalve_state state) {
  if (state == MGOS_BVALVE_STATE_CLOSED) {
    return mg_bvalve_gpio_set_closed_solenoid(cfg, state);
  } else if (state == MGOS_BVALVE_STATE_CLOSED) {
    return mg_bvalve_gpio_set_open_solenoid(cfg, state);
  }
  return false;
}

bool mg_bvalve_gpio_set_closed_bistable(struct mg_bvalve_gpio_cfg *cfg, enum mgos_bvalve_state state) {
  enum mgos_bvalve_type valve_type = mgos_bvalve_get_type(cfg->valve);
  // I must CLOSE the bistable valve...
}

bool mg_bvalve_gpio_set_open_bistable(struct mg_bvalve_gpio_cfg *cfg, enum mgos_bvalve_state state) {
  enum mgos_bvalve_type valve_type = mgos_bvalve_get_type(cfg->valve);
  // I must OPEN the bistable valve...
}

bool mg_bvalve_gpio_set_state_bistable(struct mg_bvalve_gpio_cfg *cfg, enum mgos_bvalve_state state) {
 if (state == MGOS_BVALVE_STATE_CLOSED) {
    return mg_bvalve_gpio_set_closed_bistable(cfg, state);
  } else if (state == MGOS_BVALVE_STATE_CLOSED) {
    return mg_bvalve_gpio_set_open_bistable(cfg, state);
  }
  return false;
}

bool mg_bvalve_gpio_set_state_motorized(struct mg_bvalve_gpio_cfg *cfg, enum mgos_bvalve_state state) {

}

bool mg_bvalve_gpio_set_state(struct mg_bvalve_gpio_cfg *cfg, enum mgos_bvalve_state state) {
  enum mgos_bvalve_type valve_type = mgos_bvalve_get_type(cfg->valve);

  if ((valve_type & MGOS_BVALVE_TYPE_SOLENOID) == MGOS_BVALVE_TYPE_SOLENOID) {
    return mg_bvalve_gpio_set_state_solenoid(cfg, state);
  } else if ((valve_type & MGOS_BVALVE_TYPE_BISTABLE) == MGOS_BVALVE_TYPE_BISTABLE) {
    return mg_bvalve_gpio_set_state_bistable(cfg, state);
  } else if ((valve_type & MGOS_BVALVE_TYPE_MOTORIZED) == MGOS_BVALVE_TYPE_MOTORIZED) {
    return mg_bvalve_gpio_set_state_motorized(cfg, state);
  }
  return false;
}

bool mg_bvalve_gpio_set_state_cb(mgos_bthing_t thing, mgos_bvarc_t state, void *userdata) {
  struct mg_bvalve_gpio_cfg *cfg = (struct mg_bvalve_gpio_cfg *)userdata;
  if (thing && cfg && (mgos_bvar_get_type(state) == MGOS_BVAR_TYPE_INTEGER)) {
    enum mgos_bvalve_state valve_state = (enum mgos_bvalve_state)mgos_bvar_get_integer(state);
    if (valve_state == MGOS_BVALVE_STATE_OPEN || valve_state == MGOS_BVALVE_STATE_CLOSED) {
      return mg_bvalve_gpio_set_state(cfg, valve_state);
    }
  }
  return false;
}

bool mg_bvalve_gpio_attach_solenoid(mgos_bvalve_t valve, struct mg_bvalve_gpio_cfg *cfg, va_list args) {
  cfg->pin1 = va_arg(args, int);
  cfg->pin1_active_high = va_arg(args, bool);
  return true;
}

bool mg_bvalve_gpio_attach_bistable(mgos_bvalve_t valve, struct mg_bvalve_gpio_cfg *cfg, va_list args) {
  cfg->pin1 = va_arg(args, int);
  cfg->pin1_active_high = va_arg(args, bool);
  cfg->pin2 = va_arg(args, int);
  cfg->pin2_active_high = va_arg(args, bool);
  cfg->pulse_duration =  = va_arg(args, int);
  return true;
}

bool mg_bvalve_gpio_attach_motorized(mgos_bvalve_t valve, struct mg_bvalve_gpio_cfg *cfg, va_list args) {
  cfg->pin1 = va_arg(args, int);
  cfg->pin1_active_high = va_arg(args, bool);
  cfg->pin2 = va_arg(args, int);
  cfg->pin2_active_high = va_arg(args, bool);
  cfg->pulse_duration =  = va_arg(args, int);
  cfg->gpio_power = va_arg(args, enum mgos_bvalve_gpio_power);
  return true;
}

bool mg_bvalve_gpio_attach(mgos_bvalve_t valve, struct mg_bvalve_gpio_cfg *cfg, va_list args) {
  enum mgos_bvalve_type valve_type = mgos_bvalve_get_type(valve);

  bool success = false;
  if ((valve_type & MGOS_BVALVE_TYPE_SOLENOID) == MGOS_BVALVE_TYPE_SOLENOID) {
    success = mg_bvalve_gpio_attach_solenoid(valve, cfg, args);
  } else if ((valve_type & MGOS_BVALVE_TYPE_BISTABLE) == MGOS_BVALVE_TYPE_BISTABLE) {
    success = mg_bvalve_gpio_attach_bistable(valve, cfg, args);
  } else if ((valve_type & MGOS_BVALVE_TYPE_MOTORIZED) == MGOS_BVALVE_TYPE_MOTORIZED) {
    success = mg_bvalve_gpio_attach_motorized(valve, cfg, args);
  }

  if (success && (cfg->pin1 != -1)) {
    if (!mgos_gpio_setup_output(cfg->pin1, (cfg->pin1_active_high ? false : true))) {
      success = false;
      LOG(LL_ERROR, ("Error initializing the GPIO pin %d as output for bValve '%s'",
        cfg->pin1, mgos_bthing_get_uid(MGOS_BVALVE_THINGCAST(valve))));
    }
  }

  if (success && (cfg->pin2 != -1)) {
    if (!mgos_gpio_setup_output(cfg->pin2, (cfg->pin2_active_high ? false : true))) {
      success = false;
      LOG(LL_ERROR, ("Error initializing the GPIO pin %d as output for bValve '%s'",
        cfg->pin2, mgos_bthing_get_uid(MGOS_BVALVE_THINGCAST(valve))));
    }
  }

  return success;
}

bool mgos_bvalve_gpio_attach(mgos_bvalve_t valve, ...) {
  va_list ap;
  va_start(ap, valve);

  struct mg_bvalve_gpio_cfg *cfg = calloc(1, sizeof(struct mg_bvalve_gpio_cfg));
  cfg->valve = valve;
  cfg->pin1 = -1;
  cfg->pin2 = -1;
  bool ret = mg_bvalve_gpio_attach(valve, cfg, ap);
  if (ret) {
    ret = !mgos_bthing_on_set_state(MGOS_BVALVE_THINGCAST(valve), mg_bvalve_gpio_set_state_cb, cfg);
    if (!ret) {
      LOG(LL_ERROR, ("Error setting the set-state handler of bValve '%s'",
        mgos_bthing_get_uid(MGOS_BVALVE_THINGCAST(valve))));
    }
  }

  if (ret) {
    if (cfg->pin1 != -1) {
      LOG(LL_INFO, ("bValve '%s' successfully attached to pin %d",
        mgos_bthing_get_uid(MGOS_BVALVE_THINGCAST(valve)), cfg->pin1));
    }
    if (cfg->pin2 != -1) {
      LOG(LL_INFO, ("bValve '%s' successfully attached to pin %d",
        mgos_bthing_get_uid(MGOS_BVALVE_THINGCAST(valve)), cfg->pin2));
    }
  } else {
    free(cfg);
  }

  va_end(ap);
  return ret;
}

bool mgos_bvalve_gpio_init() {
  return true;
}