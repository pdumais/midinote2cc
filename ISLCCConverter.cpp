#include "ISLCCConverter.h"

ISLCCConverter::ISLCCConverter(int cc, PAlsaSequencerOutputPort port) {
    this->port = port;
    this->cc = cc;
}

ISLCCConverter::~ISLCCConverter() {
}

void ISLCCConverter::onNoteOn(int note, int velocity) {
    this->port->sendControlChange(this->cc, note);
}

void ISLCCConverter::onNoteOff(int note) {
}
