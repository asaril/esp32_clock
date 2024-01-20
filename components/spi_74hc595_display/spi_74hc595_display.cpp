#include "spi_74hc595_display.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace spi_74hc595_display {

static const char *const TAG = "spi_74hc595_display";

static const uint8_t SPI_74HC595_DISPLAY_UNKNOWN_CHAR = 0b11111111;

const uint8_t SPI_74HC595_DISPLAY_ASCII_TO_RAW[95] PROGMEM = {
    //.GFEDCBA
    0b00000000,                        // ' ', ord 0x20
    0b10000110,                        // '!', ord 0x21
    0b00100010,                        // '"', ord 0x22
    0b00110110,                        // '#', ord 0x23
    0b00101101,                        // '$', ord 0x24
    0b01001001,                        // '%', ord 0x25
    0b00011011,                        // '&', ord 0x26
    0b00100000,                        // ''', ord 0x27
    0b00111001,                        // '(', ord 0x28
    0b00001111,                        // ')', ord 0x29
    0b00000001,                        // '*', ord 0x2A
    0b00010000,                        // '+', ord 0x2B
    0b00000100,                        // ',', ord 0x2C
    0b01000000,                        // '-', ord 0x2D
    0b10000000,                        // '.', ord 0x2E
    0b01010010,                        // '/', ord 0x2F
    0b00111111,                        // '0', ord 0x30
    0b00000110,                        // '1', ord 0x31
    0b01011011,                        // '2', ord 0x32
    0b01001111,                        // '3', ord 0x33
    0b01100110,                        // '4', ord 0x34
    0b01101101,                        // '5', ord 0x35
    0b01111101,                        // '6', ord 0x36
    0b00000111,                        // '7', ord 0x37
    0b01111111,                        // '8', ord 0x38
    0b01101111,                        // '9', ord 0x39
    0b00001001,                        // ':', ord 0x3A
    0b00001101,                        // ';', ord 0x3B
    0b00011000,                        // '<', ord 0x3C
    0b01001000,                        // '=', ord 0x3D
    0b00001100,                        // '>', ord 0x3E
    0b01010011,                        // '?', ord 0x3F
    0b01111011,                        // '@', ord 0x40
    0b01110111,                        // 'A', ord 0x41
    0b01111100,                        // 'B', ord 0x42
    0b00111001,                        // 'C', ord 0x43
    0b01011110,                        // 'D', ord 0x44
    0b01111001,                        // 'E', ord 0x45
    0b01110001,                        // 'F', ord 0x46
    0b00111101,                        // 'G', ord 0x47
    0b01110110,                        // 'H', ord 0x48
    0b00000110,                        // 'I', ord 0x49
    0b00011110,                        // 'J', ord 0x4A
    SPI_74HC595_DISPLAY_UNKNOWN_CHAR,  // 'K', ord 0x4B
    0b00111000,                        // 'L', ord 0x4C
    0b00110111,                        // 'M', ord 0x4D
    0b01010100,                        // 'N', ord 0x4E
    0b00111111,                        // 'O', ord 0x4F
    0b01110011,                        // 'P', ord 0x50
    0b10111111,                        // 'Q', ord 0x51
    0b01010000,                        // 'R', ord 0x52
    0b01101101,                        // 'S', ord 0x53
    0b01110000,                        // 'T', ord 0x54
    0b00111110,                        // 'U', ord 0x55
    0b00111110,                        // 'V', ord 0x56
    0b01111110,                        // 'W', ord 0x57
    SPI_74HC595_DISPLAY_UNKNOWN_CHAR,  // 'X', ord 0x58
    0b01110010,                        // 'Y', ord 0x59
    0b01011011,                        // 'Z', ord 0x5A
    0b00111001,                        // '[', ord 0x5B
    0b01100100,                        // '\', ord 0x5C
    0b00001111,                        // ']', ord 0x5D
    0b00100011,                        // '^', ord 0x5E
    0b00001000,                        // '_', ord 0x5F
    0b00000010,                        // '`', ord 0x60
    0b01110111,                        // 'a', ord 0x61
    0b01111100,                        // 'b', ord 0x62
    0b01011000,                        // 'c', ord 0x63
    0b01011110,                        // 'd', ord 0x64
    0b01111001,                        // 'e', ord 0x65
    0b01110001,                        // 'f', ord 0x66
    0b00111101,                        // 'g', ord 0x67
    0b01110100,                        // 'h', ord 0x68
    0b00000100,                        // 'i', ord 0x69
    0b00011110,                        // 'j', ord 0x6A
    SPI_74HC595_DISPLAY_UNKNOWN_CHAR,  // 'k', ord 0x6B
    0b00111000,                        // 'l', ord 0x6C
    0b00110111,                        // 'm', ord 0x6D
    0b01010100,                        // 'n', ord 0x6E
    0b01011100,                        // 'o', ord 0x6F
    0b01110011,                        // 'p', ord 0x70
    0b01100111,                        // 'q', ord 0x71
    0b01010000,                        // 'r', ord 0x72
    0b01101101,                        // 's', ord 0x73
    0b01110000,                        // 't', ord 0x74
    0b00011100,                        // 'u', ord 0x75
    0b00011100,                        // 'v', ord 0x76
    SPI_74HC595_DISPLAY_UNKNOWN_CHAR,  // 'w', ord 0x77
    SPI_74HC595_DISPLAY_UNKNOWN_CHAR,  // 'x', ord 0x78
    0b01110010,                        // 'y', ord 0x79
    SPI_74HC595_DISPLAY_UNKNOWN_CHAR,  // 'z', ord 0x7A
    0b01000110,                        // '{', ord 0x7B
    0b00110000,                        // '|', ord 0x7C
    0b01110000,                        // '}', ord 0x7D
    0b01100011,                        // '~', ord 0x7E (degree symbol)
};

float SPI_74HC595_DISPLAYComponent::get_setup_priority() const { return setup_priority::PROCESSOR; }

void SPI_74HC595_DISPLAYComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up SPI_74HC595_DISPLAY...");
  this->spi_setup();
  this->buffer_ = new uint8_t[this->num_chips_ * 8];  // NOLINT
  for (uint8_t i = 0; i < this->num_chips_ * 8; i++)
    this->buffer_[i] = 0;
}

void SPI_74HC595_DISPLAYComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "SPI_74HC595_DISPLAY:");
  ESP_LOGCONFIG(TAG, "  Number of Chips: %u", this->num_chips_);
  LOG_PIN("  CS Pin: ", this->cs_);
  LOG_UPDATE_INTERVAL(this);
}

void SPI_74HC595_DISPLAYComponent::display() {
  uint32_t delay = static_cast<uint64_t>(this->get_update_interval())*1000 / 9;
  for (uint8_t i = 0; i < 8; i++) {
    this->enable();
    for (uint8_t j = 0; j < this->num_chips_; j++) {
      if (reverse_) {
        this->send_byte_(~(1U << i), buffer_[(num_chips_ - j - 1) * 8 + i]);
      } else {
        this->send_byte_(~(1U << i), buffer_[j * 8 + i]);
      }
    }
    this->disable();
    delay_microseconds_safe(delay);
  }
  delay_microseconds_safe(delay);
 // zero out everything to have a somewhat uniform duty cycle for all digits
  this->enable();
  for (uint8_t j = 0; j < this->num_chips_; j++) {
    if (reverse_) {
      this->send_byte_(0, 0);
    } else {
      this->send_byte_(0, 0);
    }
  }
  delay_microseconds_safe(delay);
  this->disable();
}

void SPI_74HC595_DISPLAYComponent::send_byte_(uint8_t a_register, uint8_t data) {
  this->write_byte(a_register);
  this->write_byte(data);
}

void SPI_74HC595_DISPLAYComponent::update() {
  for (uint8_t i = 0; i < this->num_chips_ * 8; i++)
    this->buffer_[i] = 0;
  if (this->writer_.has_value())
    (*this->writer_)(*this);
  this->display();
}

uint8_t SPI_74HC595_DISPLAYComponent::print(uint8_t start_pos, const char *str) {
  uint8_t pos = start_pos;
  for (; *str != '\0'; str++) {
    uint8_t data = SPI_74HC595_DISPLAY_UNKNOWN_CHAR;
    if (*str >= ' ' && *str <= '~')
      data = progmem_read_byte(&SPI_74HC595_DISPLAY_ASCII_TO_RAW[*str - ' ']);

    if (data == SPI_74HC595_DISPLAY_UNKNOWN_CHAR) {
      ESP_LOGW(TAG, "Encountered character '%c' with no SPI_74HC595_DISPLAY representation while translating string!", *str);
    }
    if (*str == '.') {
      if (pos != start_pos)
        pos--;
      this->buffer_[pos] |= 0b10000000;
    } else {
      if (pos >= this->num_chips_ * 8) {
        ESP_LOGE(TAG, "SPI_74HC595_DISPLAY String is too long for the display!");
        break;
      }
      this->buffer_[pos] = data;
    }
    pos++;
  }
  return pos - start_pos;
}

uint8_t SPI_74HC595_DISPLAYComponent::print(const char *str) { return this->print(0, str); }

uint8_t SPI_74HC595_DISPLAYComponent::printf(uint8_t pos, const char *format, ...) {
  va_list arg;
  va_start(arg, format);
  char buffer[64];
  int ret = vsnprintf(buffer, sizeof(buffer), format, arg);
  va_end(arg);
  if (ret > 0)
    return this->print(pos, buffer);
  return 0;
}

uint8_t SPI_74HC595_DISPLAYComponent::printf(const char *format, ...) {
  va_list arg;
  va_start(arg, format);
  char buffer[64];
  int ret = vsnprintf(buffer, sizeof(buffer), format, arg);
  va_end(arg);
  if (ret > 0)
    return this->print(buffer);
  return 0;
}

void SPI_74HC595_DISPLAYComponent::set_writer(spi_74hc595_display_writer_t &&writer) { this->writer_ = writer; }

void SPI_74HC595_DISPLAYComponent::set_num_chips(uint8_t num_chips) { this->num_chips_ = num_chips; }

uint8_t SPI_74HC595_DISPLAYComponent::strftime(uint8_t pos, const char *format, ESPTime time) {
  char buffer[64];
  size_t ret = time.strftime(buffer, sizeof(buffer), format);
  if (ret > 0)
    return this->print(pos, buffer);
  return 0;
}
uint8_t SPI_74HC595_DISPLAYComponent::strftime(const char *format, ESPTime time) { return this->strftime(0, format, time); }

}  // namespace spi_74hc595_display
}  // namespace esphome