#ifndef INCLUDED_SERIAL_H_
#define INCLUDED_SERIAL_H_

namespace serial
{

void init_com1();
void write_com1(char output);
void write_com1(const char* output);

}

#endif // INCLUDED_SERIAL_H_
