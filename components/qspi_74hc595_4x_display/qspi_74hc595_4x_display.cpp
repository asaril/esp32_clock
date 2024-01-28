#include "qspi_74hc595_4x_display.h"
#include "esphome/core/hal.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome
{
namespace qspi_74hc595_4x_display
{

static const char *const TAG = "qspi_74hc595_4x_display";

static const uint32_t QSPI_74HC595_4X_DISPLAY_UNKNOWN_CHAR = 0x11111111;

static const uint32_t QSPI_74HC595_4X_DISPLAY_ASCII_TO_RAW[95] = {
    // BADCFE.G
    //  0xBADCFE.G
    0x00000000,                           // ' ', ord 0x20
    0x10010010,                           // '!', ord 0x21
    0x10001000,                           // '"', ord 0x22
    0x10011100,                           // '#', ord 0x23
    0x01111000,                           // '$', ord 0x24
    0x01100001,                           // '%', ord 0x25
    0x11100100,                           // '&', ord 0x26
    0x00001000,                           // ''', ord 0x27
    0x01101100,                           // '(', ord 0x28
    0x11110000,                           // ')', ord 0x29
    0x01000000,                           // '*', ord 0x2A
    0x00000100,                           // '+', ord 0x2B
    0x00010000,                           // ',', ord 0x2C
    0x00000001,                           // '-', ord 0x2D
    0x00000010,                           // '.', ord 0x2E
    0x10000101,                           // '/', ord 0x2F
    0x11111100,                           // '0', ord 0x30
    0x10010000,                           // '1', ord 0x31
    0x11100101,                           // '2', ord 0x32
    0x11110001,                           // '3', ord 0x33
    0x10011001,                           // '4', ord 0x34
    0x01111001,                           // '5', ord 0x35
    0x01111101,                           // '6', ord 0x36
    0x11010000,                           // '7', ord 0x37
    0x11111101,                           // '8', ord 0x38
    0x11111001,                           // '9', ord 0x39
    0x01100000,                           // ':', ord 0x3A
    0x01110000,                           // ';', ord 0x3B
    0x00100100,                           // '<', ord 0x3C
    0x00100001,                           // '=', ord 0x3D
    0x00110000,                           // '>', ord 0x3E
    0x11000101,                           // '?', ord 0x3F
    0x11101101,                           // '@', ord 0x40
    0x11011101,                           // 'A', ord 0x41
    0x00111101,                           // 'B', ord 0x42
    0x01101100,                           // 'C', ord 0x43
    0x10110101,                           // 'D', ord 0x44
    0x01101101,                           // 'E', ord 0x45
    0x01001101,                           // 'F', ord 0x46
    0x01111100,                           // 'G', ord 0x47
    0x10011101,                           // 'H', ord 0x48
    0x10010000,                           // 'I', ord 0x49
    0x10110100,                           // 'J', ord 0x4A
    QSPI_74HC595_4X_DISPLAY_UNKNOWN_CHAR, // 'K', ord 0x4B
    0x00101100,                           // 'L', ord 0x4C
    0x11011100,                           // 'M', ord 0x4D
    0x00010101,                           // 'N', ord 0x4E
    0x11111100,                           // 'O', ord 0x4F
    0x11001101,                           // 'P', ord 0x50
    0x11111110,                           // 'Q', ord 0x51
    0x00000101,                           // 'R', ord 0x52
    0x01111001,                           // 'S', ord 0x53
    0x00001101,                           // 'T', ord 0x54
    0x10111100,                           // 'U', ord 0x55
    0x10111100,                           // 'V', ord 0x56
    0x10111101,                           // 'W', ord 0x57
    QSPI_74HC595_4X_DISPLAY_UNKNOWN_CHAR, // 'X', ord 0x58
    0x10001101,                           // 'Y', ord 0x59
    0x11100101,                           // 'Z', ord 0x5A
    0x01101100,                           // '[', ord 0x5B
    0x00011001,                           // '\', ord 0x5C
    0x11110000,                           // ']', ord 0x5D
    0x11001000,                           // '^', ord 0x5E
    0x00100000,                           // '_', ord 0x5F
    0x10000000,                           // '`', ord 0x60
    0x11011101,                           // 'a', ord 0x61
    0x00111101,                           // 'b', ord 0x62
    0x00100101,                           // 'c', ord 0x63
    0x10110101,                           // 'd', ord 0x64
    0x01101101,                           // 'e', ord 0x65
    0x01001101,                           // 'f', ord 0x66
    0x01111100,                           // 'g', ord 0x67
    0x00011101,                           // 'h', ord 0x68
    0x00010000,                           // 'i', ord 0x69
    0x10110100,                           // 'j', ord 0x6A
    QSPI_74HC595_4X_DISPLAY_UNKNOWN_CHAR, // 'k', ord 0x6B
    0x00101100,                           // 'l', ord 0x6C
    0x11011100,                           // 'm', ord 0x6D
    0x00010101,                           // 'n', ord 0x6E
    0x00110101,                           // 'o', ord 0x6F
    0x11001101,                           // 'p', ord 0x70
    0x11011001,                           // 'q', ord 0x71
    0x00000101,                           // 'r', ord 0x72
    0x01111001,                           // 's', ord 0x73
    0x00001101,                           // 't', ord 0x74
    0x00110100,                           // 'u', ord 0x75
    0x00110100,                           // 'v', ord 0x76
    QSPI_74HC595_4X_DISPLAY_UNKNOWN_CHAR, // 'w', ord 0x77
    QSPI_74HC595_4X_DISPLAY_UNKNOWN_CHAR, // 'x', ord 0x78
    0x10001101,                           // 'y', ord 0x79
    QSPI_74HC595_4X_DISPLAY_UNKNOWN_CHAR, // 'z', ord 0x7A
    0x10010001,                           // '{', ord 0x7B
    0x00001100,                           // '|', ord 0x7C
    0x00001101,                           // '}', ord 0x7D
    0x11001001,                           // '~', ord 0x7E (degree symbol)
};

static constexpr uint8_t QSPI_74HC595_4X_DISPLAY_DIGIT_MAP[8] = {2, 3, 0, 1, 6, 7, 4, 5};

static constexpr uint8_t QSPI_74HC595_4X_DISPLAY_ZEROS[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

float QSPI_74HC595_4X_DISPLAYComponent::get_setup_priority() const
{
    return setup_priority::PROCESSOR;
}

void QSPI_74HC595_4X_DISPLAYComponent::setup()
{
    ESP_LOGCONFIG(TAG, "Setting up QSPI_74HC595_4X_DISPLAY...");
    this->spi_setup();
    memset(this->buffer_, 0xff, sizeof(this->buffer_));
    // this->buffer_[0*2] = ~QSPI_74HC595_4X_DISPLAY_ASCII_TO_RAW['.'-' '];
    // this->buffer_[1*2] = ~QSPI_74HC595_4X_DISPLAY_ASCII_TO_RAW['*'-' '];
    // this->buffer_[2*2] = ~QSPI_74HC595_4X_DISPLAY_ASCII_TO_RAW['`'-' '];
    // this->buffer_[3*2] = ~QSPI_74HC595_4X_DISPLAY_ASCII_TO_RAW[','-' '];
    // this->buffer_[4*2] = ~QSPI_74HC595_4X_DISPLAY_ASCII_TO_RAW['_'-' '];
    // this->buffer_[5*2] = ~QSPI_74HC595_4X_DISPLAY_ASCII_TO_RAW['+'-' '];
    // this->buffer_[6*2] = ~QSPI_74HC595_4X_DISPLAY_ASCII_TO_RAW['\''-' '];
    // this->buffer_[7*2] = ~QSPI_74HC595_4X_DISPLAY_ASCII_TO_RAW['-'-' '];
    for (uint8_t i = 0; i < 8; i++)
    {
        this->buffer_[(i * 2) + 1] = 0xF << (QSPI_74HC595_4X_DISPLAY_DIGIT_MAP[i] * 4);
    }
}

void QSPI_74HC595_4X_DISPLAYComponent::dump_config()
{
    ESP_LOGCONFIG(TAG, "QSPI_74HC595_4X_DISPLAY:");
    LOG_PIN("  CS Pin: ", this->cs_);
    LOG_UPDATE_INTERVAL(this);
}

void QSPI_74HC595_4X_DISPLAYComponent::display()
{
    uint32_t delay = static_cast<uint64_t>(this->get_update_interval()) * 1000 / 8;
    const uint8_t *buf_ptr = reinterpret_cast<const uint8_t *>(this->buffer_);
    for (uint8_t i = 0; i < 8; i++)
    {
        uint32_t start = micros();
        this->enable();
        this->write_cmd_addr_data(0, 0, 0, 0, buf_ptr, 8, 4);
        buf_ptr += 8;
        this->disable();
        delay_microseconds_safe(delay - (micros() - start));
    }
    // zero out everything to have a somewhat uniform duty cycle for all digits
    this->enable();
    this->write_cmd_addr_data(0, 0, 0, 0, QSPI_74HC595_4X_DISPLAY_ZEROS, 32, 4);
    this->disable();
}

void QSPI_74HC595_4X_DISPLAYComponent::update()
{
    for (uint8_t i = 0; i < 8; i++)
        this->buffer_[i * 2] = 0xFFFFFFFF;
    if (this->writer_.has_value())
        (*this->writer_)(*this);
    this->display();
}

uint8_t QSPI_74HC595_4X_DISPLAYComponent::print(uint8_t start_pos, const char *str)
{
    uint8_t pos = start_pos;

    for (; *str != '\0'; str++)
    {
        uint32_t data = QSPI_74HC595_4X_DISPLAY_UNKNOWN_CHAR;
        if (*str >= ' ' && *str <= '~')
            data = QSPI_74HC595_4X_DISPLAY_ASCII_TO_RAW[*str - ' '];

        if (data == QSPI_74HC595_4X_DISPLAY_UNKNOWN_CHAR)
        {
            ESP_LOGW(
                TAG,
                "Encountered character '%c' with no QSPI_74HC595_4X_DISPLAY representation while translating string!",
                *str);
        }
        if (*str == '.')
        {
            if (pos != start_pos)
                pos--;
            this->buffer_[(pos % 8) * 2] &= ~(0x00000010 << (pos / 8));
        }
        else
        {
            if (pos >= 32)
            {
                ESP_LOGE(TAG, "QSPI_74HC595_4X_DISPLAY String is too long for the display!");
                break;
            }
            this->buffer_[(pos % 8) * 2] &= ~(data << (pos / 8));
        }
        pos++;
    }

    return pos - start_pos;
}

uint8_t QSPI_74HC595_4X_DISPLAYComponent::print(const char *str)
{
    return this->print(0, str);
}

uint8_t QSPI_74HC595_4X_DISPLAYComponent::printf(uint8_t pos, const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    char buffer[64];
    int ret = vsnprintf(buffer, sizeof(buffer), format, arg);
    va_end(arg);
    if (ret > 0)
        return this->print(pos, buffer);
    return 0;
}

uint8_t QSPI_74HC595_4X_DISPLAYComponent::printf(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    char buffer[64];
    int ret = vsnprintf(buffer, sizeof(buffer), format, arg);
    va_end(arg);
    if (ret > 0)
        return this->print(buffer);
    return 0;
}

void QSPI_74HC595_4X_DISPLAYComponent::set_writer(qspi_74hc595_4x_display_writer_t &&writer)
{
    this->writer_ = writer;
}

uint8_t QSPI_74HC595_4X_DISPLAYComponent::strftime(uint8_t pos, const char *format, ESPTime time)
{
    char buffer[64];
    size_t ret = time.strftime(buffer, sizeof(buffer), format);
    if (ret > 0)
        return this->print(pos, buffer);
    return 0;
}
uint8_t QSPI_74HC595_4X_DISPLAYComponent::strftime(const char *format, ESPTime time)
{
    return this->strftime(0, format, time);
}

} // namespace qspi_74hc595_4x_display
} // namespace esphome