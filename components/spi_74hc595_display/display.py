import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import display, spi
from esphome.const import CONF_ID, CONF_INTENSITY, CONF_LAMBDA, CONF_NUM_CHIPS

DEPENDENCIES = ["spi"]

spi_74hc595_display_ns = cg.esphome_ns.namespace("spi_74hc595_display")
SPI_74HC595_DISPLAYComponent = spi_74hc595_display_ns.class_(
    "SPI_74HC595_DISPLAYComponent", cg.PollingComponent, spi.SPIDevice
)
SPI_74HC595_DISPLAYComponentRef = SPI_74HC595_DISPLAYComponent.operator("ref")

CONF_REVERSE = "reverse"

CONFIG_SCHEMA = (
    display.BASIC_DISPLAY_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(SPI_74HC595_DISPLAYComponent),
            cv.Optional(CONF_NUM_CHIPS, default=1): cv.int_range(min=1, max=255),
            cv.Optional(CONF_REVERSE, default=False): cv.boolean,
        }
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(spi.spi_device_schema())
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await spi.register_spi_device(var, config)
    await display.register_display(var, config)

    cg.add(var.set_num_chips(config[CONF_NUM_CHIPS]))
    cg.add(var.set_reverse(config[CONF_REVERSE]))

    if CONF_LAMBDA in config:
        lambda_ = await cg.process_lambda(
            config[CONF_LAMBDA], [(SPI_74HC595_DISPLAYComponentRef, "it")], return_type=cg.void
        )
        cg.add(var.set_writer(lambda_))