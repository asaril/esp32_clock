#pragma once

#include "esphome/core/component.h"
#include "esphome/core/time.h"

#include "esphome/components/spi/spi.h"

namespace esphome {
namespace spi_74hc595_display {

class SPI_74HC595_DISPLAYComponent;

using spi_74hc595_display_writer_t = std::function<void(SPI_74HC595_DISPLAYComponent &)>;

class SPI_74HC595_DISPLAYComponent : public PollingComponent,
                         public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW,
                                               spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_10MHZ> {
 public:
  void set_writer(spi_74hc595_display_writer_t &&writer);

  void setup() override;

  void dump_config() override;

  void update() override;

  float get_setup_priority() const override;

  void display();

  void set_num_chips(uint8_t num_chips);
  void set_reverse(bool reverse) { this->reverse_ = reverse; };
  void set_segment_first(bool segment_first) { this->segment_first_ = segment_first; };
  void set_common_cathode(bool common_cathode) { this->common_cathode_ = common_cathode; };

  /// Evaluate the printf-format and print the result at the given position.
  uint8_t printf(uint8_t pos, const char *format, ...) __attribute__((format(printf, 3, 4)));
  /// Evaluate the printf-format and print the result at position 0.
  uint8_t printf(const char *format, ...) __attribute__((format(printf, 2, 3)));

  /// Print `str` at the given position.
  uint8_t print(uint8_t pos, const char *str);
  /// Print `str` at position 0.
  uint8_t print(const char *str);

  /// Evaluate the strftime-format and print the result at the given position.
  uint8_t strftime(uint8_t pos, const char *format, ESPTime time) __attribute__((format(strftime, 3, 0)));

  /// Evaluate the strftime-format and print the result at position 0.
  uint8_t strftime(const char *format, ESPTime time) __attribute__((format(strftime, 2, 0)));

 protected:
  void send_byte_(uint8_t a_register, uint8_t data);
  void send_to_all_(uint8_t a_register, uint8_t data);

  uint8_t num_chips_{1};
  uint8_t *buffer_;
  bool reverse_{false};
  bool reverse_chain_{false};
  bool segment_first_{true};
  bool common_cathode_{false};
  optional<spi_74hc595_display_writer_t> writer_{};

  uint8_t flip_digit_{0};
  uint8_t flip_segment_{0xFF};
  uint8_t digit_mask[8]{0x08,0x04,0x02,0x01,0x80,0x40,0x20,0x10};

};

}  // namespace spi_74hc595_display
}  // namespace esphome