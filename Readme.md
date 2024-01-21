# ESP32 Clock
This is a YAML config file + driver for a clock based on several LED segment displays driven
by SN74HC595 shift registers.


## Hardware
Connect the shift registers like this, or adapt the pin config as needed:

- Data input (DIO) to ESP GPIO19
- Shift clock input (SCK) to ESP GPIO18
- Latch / register clock input (RCK) to ESP GPIO5

Keep in mind that the ESP32 is a 3.3V device when connecting to a 5V display.


## Setup
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
The actual segment mapping is not tested well, due to missing hardware.
