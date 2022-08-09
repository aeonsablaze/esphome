#include "count_sensor.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "esphome/core/application.h"

namespace esphome {
namespace count_sensor {

static const char *const TAG = "count_sensor.sensor";

void CountSensor::setup() {
  float sensor_value = this->sensor_->state;
  this->publish_state(0);
  this->high_freq_.start();
}

//void CountSensor::loop(binary_sensor::BinarySensor *input_sensor) {
void CountSensor::loop() {
  //if (this->sensor_->state == 1){
  //  ESP_LOGW(TAG,"DEBUG: %i",this->sensor_->state);
  //}
}

void CountSensor::set_sensor(binary_sensor::BinarySensor *input_sensor) {
  this->sensor_ = input_sensor;
  int count = 0;
  uint32_t tlen = 0;
  uint32_t timer = millis();
  unsigned int arrsize = 10;
  unsigned int timing_index = 0;
  uint32_t timings[arrsize];
  //std::fill(timings,timings+arrsize,0);
  //for ( uint8_t i = 0; i < arrsize; i++) { timings[i]=0; }
  this->sensor_->add_on_state_callback([this,timer,count,tlen,&timings,timing_index,arrsize](float sensor_value) mutable {
    // if there is an invalid sensor reading, ignore the change and keep the current state
    if (sensor_value == 1) {
      timer = millis();
      //ESP_LOGW(TAG,"DEBUG: %i",this->sensor_->state);
    } else if (sensor_value == 0) {
      uint32_t now = millis();
      uint32_t elapsed = now-timer;
      ESP_LOGW(TAG,"Elapsed: %i",elapsed);
      timings[timing_index]=elapsed;
      timing_index++;
      if (timing_index > 20) { timing_index = 0; };
      //delay_microseconds_safe(1000000*30);
      if (elapsed > trigger_min_ and elapsed < trigger_max_) {
        count++;
      }
      tlen = elapsed;
      ESP_LOGW(TAG,"Timings:");
      for ( unsigned int i = 0; i < arrsize; i++) {
        ESP_LOGW(TAG,"   %i",timings[i]);
      }
      ESP_LOGW(TAG,"Count: %i",count);
    }
    this->publish_state(tlen);
  });
}

void CountSensor::dump_config() {
  LOG_SENSOR("", "Count Sensor", this);
  LOG_BINARY_SENSOR("  ", "Input Sensor", this->sensor_);
}

}  // namespace count_sensor
}  // namespace esphome
