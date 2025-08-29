#ifndef _SENSE_AMP_H
#define _SENSE_AMP_H


#include <systemc.h>


SC_MODULE(SenseAmplifier) {

    sc_in<bool> read_pulse;
    sc_in<sc_uint<32>> d_out_core;
    sc_out<sc_uint<32>> d_out;


    void process(void) {

        if (read_pulse.read()) d_out.write(d_out_core.read());
    }

    SC_CTOR(SenseAmplifier) {
        SC_METHOD(process);
        sensitive << read_pulse << d_out_core;
    }
};


#endif
