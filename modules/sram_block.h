#ifndef _SRAM_BLOCK_H
#define _SRAM_BLOCK_H


#include <systemc.h>
#include "sense_amp.h"
#include "address_decoder.h"
#include "internal_sram_controller.h"
#include "sram_core.h"


SC_MODULE(SRAM) {

    sc_in<bool> we, en;
    sc_in<sc_uint<8>> addr_in;
    sc_in<sc_uint<32>> w_data;
    sc_out<sc_uint<32>> r_data;

    ADDRDecoder *demux;
    InternalSRAMCtrl *ctrlr;
    SenseAmplifier *amplifier;
    SRAMCore *core;

    sc_signal<bool> sig_precharge, sig_write_pulse, sig_read_pulse, sig_enwl;
    sc_signal<sc_bv<256>> sig_addr_out;
    sc_signal<sc_uint<32>> sig_d_out_core;


    SC_CTOR(SRAM) {

        demux = new ADDRDecoder("Address_decoder");
        ctrlr = new InternalSRAMCtrl("Internal_SRAM_Controller");
        amplifier = new SenseAmplifier("Sense_Amplifier");
        core = new SRAMCore("SRAM_Core");

        ctrlr->en(en);
        ctrlr->we(we);
        ctrlr->enwl(sig_enwl);
        ctrlr->precharge(sig_precharge);
        ctrlr->writepulse(sig_write_pulse);
        ctrlr->readpulse(sig_read_pulse);
        
        demux->addr_in(addr_in);
        demux->EnWL(sig_enwl);
        demux->addr_out(sig_addr_out);
        
        core->wl(sig_addr_out);
        core->precharge(sig_precharge);
        core->write_pulse(sig_write_pulse);
        core->d_out(sig_d_out_core);
        core->d_in(w_data);

        amplifier->d_out_core(sig_d_out_core);
        amplifier->read_pulse(sig_read_pulse);
        amplifier->d_out(r_data);
    }
};

#endif
