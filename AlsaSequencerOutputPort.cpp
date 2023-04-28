#include "AlsaSequencerOutputPort.h"

AlsaSequencerOutputPort::AlsaSequencerOutputPort(snd_seq_t *seq_handle, const std::string& name, int channel) {
    this->seq_handle = seq_handle;
    this->channel = channel;

    int err = snd_seq_create_simple_port(this->seq_handle, name.c_str(), SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ, SND_SEQ_PORT_TYPE_MIDI_GENERIC);
    if (err < 0) {
        this->output_port_id = 0;
    } else {
        this->output_port_id = err;
    }
}

AlsaSequencerOutputPort::~AlsaSequencerOutputPort() {
    printf("AlsaSequencerOutputPort (%i) deleted\n", this->output_port_id);
}


void AlsaSequencerOutputPort::sendControlChange(int cc, int value) {
    snd_seq_event_t ev;

    snd_seq_ev_clear(&ev);
    snd_seq_ev_set_source(&ev, this->output_port_id);
    snd_seq_ev_set_subs(&ev);
    snd_seq_ev_set_direct(&ev);
    snd_seq_ev_set_controller(&ev, this->channel, cc, value);

    snd_seq_event_output(this->seq_handle, &ev);
    snd_seq_drain_output(this->seq_handle);
    printf("CC %i %i\n", cc, value);
}

void AlsaSequencerOutputPort::sendNoteOff(int note) {
    snd_seq_event_t ev;

    snd_seq_ev_clear(&ev);
    snd_seq_ev_set_source(&ev, this->output_port_id);
    snd_seq_ev_set_subs(&ev);
    snd_seq_ev_set_direct(&ev);
    snd_seq_ev_set_noteoff(&ev, this->channel, note, 0);

    snd_seq_event_output(this->seq_handle, &ev);
    snd_seq_drain_output(this->seq_handle);
}

void AlsaSequencerOutputPort::sendNoteOn(int note, int velocity) {
    snd_seq_event_t ev;

    snd_seq_ev_clear(&ev);
    snd_seq_ev_set_source(&ev, this->output_port_id);
    snd_seq_ev_set_subs(&ev);
    snd_seq_ev_set_direct(&ev);
    snd_seq_ev_set_noteon(&ev, this->channel, note, velocity);

    snd_seq_event_output(this->seq_handle, &ev);
    snd_seq_drain_output(this->seq_handle);
}
