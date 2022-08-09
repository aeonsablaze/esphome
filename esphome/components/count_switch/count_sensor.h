#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace count_sensor {

class CountSensor : public Component, public sensor::Sensor {
 public:
  void setup() override;
  void dump_config() override;

  float get_setup_priority() const override { return setup_priority::LATE; }

  void set_sensor(binary_sensor::BinarySensor *binary_sensor);

  void set_trigger_min(uint32_t trigger_min) { this->trigger_min_ = trigger_min; }
  void set_trigger_max(uint32_t trigger_max) { this->trigger_max_ = trigger_max; }
  void set_break_threshold(uint32_t break_threshold) { this->break_threshold_ = break_threshold; }
  
  //void loop(binary_sensor::BinarySensor *binary_sensor);
  void loop();


 protected:
  binary_sensor::BinarySensor *sensor_{nullptr};

  HighFrequencyLoopRequester high_freq_;

  uint32_t trigger_min_;
  uint32_t trigger_max_;
  uint32_t break_threshold_;
};

}  // namespace count_sensor
}  // namespace esphome
