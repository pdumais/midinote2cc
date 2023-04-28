#pragma once
#include <alsa/asoundlib.h>
#include <string>
#include <memory>

class AlsaSequencerOutputPort {
private:
    snd_seq_t *seq_handle;
    int output_port_id;
    std::string name;
    int channel;

public:
    AlsaSequencerOutputPort(snd_seq_t *seq_handle, const std::string& name, int channel);
    ~AlsaSequencerOutputPort();
    void sendControlChange(int cc, int value);
    void sendNoteOff(int note);
    void sendNoteOn(int note, int velocity);

};

typedef std::shared_ptr<AlsaSequencerOutputPort> PAlsaSequencerOutputPort;
