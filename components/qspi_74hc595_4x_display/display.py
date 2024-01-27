import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import display, spi
from esphome.const import CONF_ID, CONF_INTENSITY, CONF_LAMBDA, CONF_NUM_CHIPS

DEPENDENCIES = ["spi"]

qspi_74hc595_4x_display_ns = cg.esphome_ns.namespace("qspi_74hc595_4x_display")
QSPI_74HC595_4X_DISPLAYComponent = qspi_74hc595_4x_display_ns.class_(
    "QSPI_74HC595_4X_DISPLAYComponent", cg.PollingComponent, spi.SPIDevice
)
QSPI_74HC595_4X_DISPLAYComponentRef = QSPI_74HC595_4X_DISPLAYComponent.operator("ref")

CONFIG_SCHEMA = (
    display.BASIC_DISPLAY_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(QSPI_74HC595_4X_DISPLAYComponent),
        }
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(spi.spi_device_schema(quad=True))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await spi.register_spi_device(var, config)
    await display.register_display(var, config)

    if CONF_LAMBDA in config:
        lambda_ = await cg.process_lambda(
            config[CONF_LAMBDA], [(QSPI_74HC595_4X_DISPLAYComponentRef, "it")], return_type=cg.void
        )
        cg.add(var.set_writer(lambda_))