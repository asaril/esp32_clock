#pragma once

#include "esphome/core/component.h"
#include "esphome/core/time.h"

#include "esphome/components/spi/spi.h"

namespace esphome {
namespace qspi_74hc595_4x_display {

class QSPI_74HC595_4X_DISPLAYComponent;

using qspi_74hc595_4x_display_writer_t = std::function<void(QSPI_74HC595_4X_DISPLAYComponent &)>;

class QSPI_74HC595_4X_DISPLAYComponent : public PollingComponent,
                         public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW,
                                               spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_10MHZ> {
 public:
  void set_writer(qspi_74hc595_4x_display_writer_t &&writer);

  void setup() override;

  void dump_config() override;

  void update() override;

  float get_setup_priority() const override;

  void display();

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

  uint32_t buffer_[16]; // 8* segment+digit words
  optional<qspi_74hc595_4x_display_writer_t> writer_{};
};

}  // namespace qspi_74hc595_4x_display
}  // namespace esphome