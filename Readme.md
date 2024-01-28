# ESP32 Clock
This is a YAML config file + driver for a clock based on several LED segment displays driven
by SN74HC595 shift registers.


## Hardware
Connect the shift registers like this, or adapt the pin config as needed:

- Data input (DIO) to ESP:
  - GPIO23 (first display), 
  - GPIO19 (second display), 
  - GPIO22 (third display),
  - GPIO21 (fourth display)
- Shift clock input (SCK) to ESP GPIO18 (all displays)
- Latch / register clock input (RCK) to ESP GPIO5 (all display)

Keep in mind that the ESP32 is a 3.3V device when connecting to a 5V display. The shift registers should handle the 3.3V
signals from the ESP, annd in some cases, 3.3V can also be used to power the displays at a lower brightness.


## Setup

> Note: the QSPI driver in esphome is (as of 2024-01-28) not yet in the released package.
> Install a suitable version directly from github with:
> `pip install "esphome @ git+https://github.com/esphome/esphome@1fef769496ed89c0062d8e70f5964b8318ba4550"`

Set the board type in the YAML (default should also work on most ESP32 devices)
Adapt the config as needed for the fallback AP and if wanted, api key.
Create a `secrets.yaml` containing this:

```yaml
wifi_ssid: "ssidhere"
wifi_password: "keyhere"
```

Adapt the config flags `reverse`, `common_cathode`, and `segment_first` in the component configuration in the main YAML
for your display type.

Build and upload the config with esphome CLI, or the dashboard.
See [the ESPHome CLI Getting Started Guide](https://esphome.io/guides/getting_started_command_line.html) 
how to do that.

## License
The driver in `components/` is directly based on the existing MAX7219 driver in ESPHome and as such
subject to the GPLv3 and MIT licenses, as outlined in the LICENSE document (also copied from ESPHome).

## Open Issues

