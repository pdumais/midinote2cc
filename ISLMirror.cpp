#include "ISLMirror.h"

ISLMirror::ISLMirror(PAlsaSequencerOutputPort port) {
    this->port = port;
}

ISLMirror::~ISLMirror() {
}


void ISLMirror::onNoteOn(int note, int velocity) {
    this->port->sendNoteOn(note, velocity);
}

void ISLMirror::onNoteOff(int note) {
    this->port->sendNoteOff(note);
}
