#ifndef INCLUDED_IO_H_
#define INCLUDED_IO_H_

#include <stdint.h>

/** outb: sends data to provided I/O port. Defined as assembly in io.asm
 * 
 * @param port The I/O port address to send data to
 * @param data Data to send to port
 */
extern "C" void outb(uint16_t port, uint8_t data);

/** inb: reads data from provided I/O port. Defined as assembly in io.asm
 * 
 * @param port The I/O port address to send data to
 * 
 * @returns Byte read from I/O port
 */
extern "C" uint8_t inb(uint16_t port);

#endif // INCLUDED_IO_H_
