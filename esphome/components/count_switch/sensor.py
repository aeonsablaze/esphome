import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor, sensor
from esphome.const import (
    CONF_SENSOR_ID,
)

CONF_TRIGGER_MIN = "trigger_min"
CONF_TRIGGER_MAX = "trigger_max"
CONF_BREAK_THRESHOLD = "break_threshold"

count_sensor_ns = cg.esphome_ns.namespace("count_sensor")

CountSensor = count_sensor_ns.class_(
    "CountSensor", binary_sensor.BinarySensor, cg.Component
)

CONFIG_SCHEMA = sensor.SENSOR_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(CountSensor),
        cv.Required(CONF_SENSOR_ID): cv.use_id(binary_sensor.BinarySensor),
        cv.Optional(CONF_TRIGGER_MIN, default="1ms"): cv.positive_time_period,
        cv.Optional(CONF_TRIGGER_MAX, default="1000ms"): cv.positive_time_period,
        cv.Optional(CONF_BREAK_THRESHOLD, default="1000ms"): cv.positive_time_period,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    cg.add(var.set_trigger_min(config[CONF_TRIGGER_MIN].total_milliseconds))
    cg.add(var.set_trigger_max(config[CONF_TRIGGER_MAX].total_milliseconds))
    cg.add(var.set_break_threshold(config[CONF_BREAK_THRESHOLD].total_milliseconds))

    sens = await cg.get_variable(config[CONF_SENSOR_ID])
    cg.add(var.set_sensor(sens))
    # cg.add(var.loop())
