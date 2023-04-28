#pragma once
#include "ISequencerListener.h"
#include "AlsaSequencerOutputPort.h"

class ISLCCConverter: public ISequencerListener {
private:
    PAlsaSequencerOutputPort port;
    int cc;

public:
    ISLCCConverter(int cc, PAlsaSequencerOutputPort);
    ~ISLCCConverter();
    virtual void onNoteOn(int note, int velocity) override;
    virtual void onNoteOff(int note) override;
};