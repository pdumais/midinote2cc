#pragma once
#include "ISequencerListener.h"
#include "AlsaSequencerOutputPort.h"
#include <memory>

class ISLMirror: public ISequencerListener {
private:
    PAlsaSequencerOutputPort port;

public:
    ISLMirror(PAlsaSequencerOutputPort port);
    ~ISLMirror();
    virtual void onNoteOn(int note, int velocity) override;
    virtual void onNoteOff(int note) override;
};