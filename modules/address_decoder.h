#ifndef _ADDR_DECODER
#define _ADDR_DECODER


#include <systemc.h>


SC_MODULE(ADDRDecoder) {

    sc_in<sc_uint<8>> addr_in;
    sc_in<bool> EnWL;
    sc_out<sc_bv<256>> addr_out;
    
    void process(void) {

        sc_bv<256> wl = 0;
        
        if (EnWL.read()) wl[addr_in.read()] = '1';
        addr_out.write(wl);
    }

    SC_CTOR(ADDRDecoder) {
        SC_METHOD(process);
        sensitive << addr_in << EnWL;
    }
};

#endif
