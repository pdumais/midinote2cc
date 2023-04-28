#pragma once

class ISequencerListener {
public:
    virtual ~ISequencerListener() {};
    virtual void onNoteOn(int note, int velocity) = 0;
    virtual void onNoteOff(int note) = 0;
};