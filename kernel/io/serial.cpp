#include "serial.h"

#include "io.h"

#include <stdint.h>

namespace serial
{

namespace
{

template <uint16_t PortAddress>
class SerialPort
{
public:
    static constexpr uint16_t data_register()
    {
        return PortAddress;
    }

    static constexpr uint16_t interrupt_enable_register()
    {
        return PortAddress + 1;
    }

    static constexpr uint16_t interrupt_identification_register()
    {
        return PortAddress + 2;
    }

    static constexpr uint16_t fifo_control_register()
    {
        return PortAddress + 2;
    }

    static constexpr uint16_t line_control_register()
    {
        return PortAddress + 3;
    }

    static constexpr uint16_t modem_control_register()
    {
        return PortAddress + 4;
    }

    static constexpr uint16_t line_status_register()
    {
        return PortAddress + 5;
    }

    static constexpr uint16_t modem_status_register()
    {
        return PortAddress + 6;
    }

    static constexpr uint16_t scratch_register()
    {
        return PortAddress + 7;
    }

    static bool is_transmit_register_empty()
    {
        constexpr uint8_t empty_transmit_register_bit = 0x20;
        return (inb(line_status_register()) & empty_transmit_register_bit) != 0;
    }
};

using COM1 = SerialPort<0x3F8>;

void disable_interrupts()
{
    outb(COM1::interrupt_enable_register(), 0x00);
}

void set_baud_rate_divisor()
{
    outb(COM1::line_control_register(), 0x80);
    outb(COM1::data_register(), 0x03);
    outb(COM1::interrupt_enable_register(), 0x00);
}

void set_8N1_data_format()
{
    outb(COM1::line_control_register(), 0x03);
}

void init_fifo_with_14_bytes_threshold()
{
    outb(COM1::fifo_control_register(), 0xC7);
}

void enable_irq_and_set_ready()
{
    outb(COM1::modem_control_register(), 0x0B);
}

} // end namespace

void init_com1()
{
    disable_interrupts();
    set_baud_rate_divisor();
    set_8N1_data_format();
    init_fifo_with_14_bytes_threshold();
    enable_irq_and_set_ready();

    write_com1("COM1 Init Complete");
}

void write_com1(char output)
{
    while (!COM1::is_transmit_register_empty())
    {

    }

    outb(COM1::data_register(), output);
}

void write_com1(const char* output)
{
    while (*output != 0)
    {
        write_com1(*output++);
    }
}

} // end namespace serial
