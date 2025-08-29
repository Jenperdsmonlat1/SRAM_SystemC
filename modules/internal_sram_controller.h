#ifndef _INTERNAL_SRAM_CTRL
#define _INTERNAL_SRAM_CTRL


#include <systemc.h>


SC_MODULE(InternalSRAMCtrl) {

    sc_in<bool> en, we;
    sc_out<bool> enwl, precharge, writepulse, readpulse;


    void process(void) {

        if (!en.read()) {
            precharge.write(false);
            enwl.write(false);
            readpulse.write(false);
            writepulse.write(false);
        } else {
            if (!we.read()) {
                precharge.write(true);
                enwl.write(true);
                readpulse.write(true);
                writepulse.write(false);
            } else {
                precharge.write(false);
                enwl.write(true);
                readpulse.write(false);
                writepulse.write(true);
            }
        } 
    }

    SC_CTOR(InternalSRAMCtrl) {
        SC_METHOD(process);
        sensitive << en << we;
    }
};


#endif
