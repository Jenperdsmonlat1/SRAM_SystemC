#ifndef _SRAM_CORE_H
#define _SRAM_CORE_H


#include <systemc.h>


SC_MODULE(SRAMCore) {

    sc_in<sc_bv<256>> wl;
    sc_in<bool> precharge, write_pulse;
    sc_in<sc_uint<32>> d_in;
    sc_out<sc_uint<32>> d_out;

    sc_uint<32> memory[256];


    void process(void) {

        int selected = -1;
        
        for (uint16_t i = 0; i < 256; i++) {
            if (wl.read()[i] == '1') {
                selected = i;
                break;
            }
        }

        if (selected == -1) return;
        if (write_pulse.read()) memory[selected] = d_in.read();
        if (!write_pulse.read() && !precharge.read()) d_out.write(memory[selected]);
    }

    SC_CTOR(SRAMCore) {
        SC_METHOD(process);
        sensitive << wl << precharge << write_pulse << d_in;
    }
};


#endif
