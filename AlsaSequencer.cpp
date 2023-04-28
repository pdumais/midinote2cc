#include "AlsaSequencer.h"

AlsaSequencer::AlsaSequencer(const char* seq, const std::string& input, int channel) {
    this->seq_handle = 0;
    this->seq_name = seq;
    this->input_id = input;
    this->input_port_id = 0;
    this->channel = channel;
}

AlsaSequencer::~AlsaSequencer() {
    if (this->seq_handle) {
        snd_seq_close(this->seq_handle);
        this->seq_handle = 0;
    }
}

snd_seq_addr_t AlsaSequencer::parseAddress(const std::string& addr)
{
    snd_seq_addr_t a;

	std::string temp;
	std::stringstream ss { this->input_id };
	std::vector<std::string> result;

	std::getline(ss, temp, ':');
    a.client = std::stoi(temp);
	std::getline(ss, temp, ':');
    a.port = std::stoi(temp);

    return a;
}


void AlsaSequencer::processIncoming() {
    snd_seq_event_t *ev;

    while (snd_seq_event_input(this->seq_handle, &ev)) {
        if (ev->type == SND_SEQ_EVENT_NOTEOFF || ev->type == SND_SEQ_EVENT_NOTEON) {
            if (ev->data.note.channel == this->channel) {
                if (ev->type == SND_SEQ_EVENT_NOTEOFF || ev->data.note.velocity == 0) {
                    for (auto& it : this->listeners) {
                        it.second->onNoteOff(ev->data.note.note);
                    }
                } else {
                    for (auto& it : this->listeners) {
                        it.second->onNoteOn(ev->data.note.note, ev->data.note.velocity);
                    }
                }
            }
        }

        snd_seq_ev_clear(&ev);
    }

}

bool AlsaSequencer::open() {
    int err = snd_seq_open(&this->seq_handle, this->seq_name.c_str(), SND_SEQ_OPEN_DUPLEX, 0);
    if (err < 0) return false;

    snd_seq_set_client_name(this->seq_handle, "MidiNote2CC");

    err = snd_seq_create_simple_port(this->seq_handle, "input", SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, SND_SEQ_PORT_TYPE_MIDI_GENERIC);
    if (err < 0) return false;
    this->input_port_id = err;

    snd_seq_addr_t sender = this->parseAddress(this->input_id);
    err = snd_seq_connect_from(this->seq_handle, this->input_port_id, sender.client, sender.port);
    if (err < 0) return false;

    return true;
}

PAlsaSequencerOutputPort AlsaSequencer::createOutputPort(const std::string& name) {
    auto p = std::make_shared<AlsaSequencerOutputPort>(this->seq_handle, name, this->channel);
    this->output_ports.push_back(PAlsaSequencerOutputPort(p));
    return p;
}

void AlsaSequencer::addListener(ISequencerListener* l) {
    this->listeners[l] = l;
}

void AlsaSequencer::removeAndDeleteListener(ISequencerListener* l) {
    if (!this->listeners.count(l)) return;

    delete this->listeners[l];
    this->listeners.erase(l);
}
