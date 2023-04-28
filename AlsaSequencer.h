#pragma once

#include <alsa/asoundlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include "AlsaSequencerOutputPort.h"
#include "ISequencerListener.h"
#include <memory>

class AlsaSequencer {
private:
    snd_seq_t *seq_handle;
    std::string seq_name;
    std::string input_id;
    int input_port_id;
    int channel;
    std::map<ISequencerListener*, ISequencerListener*> listeners;

    snd_seq_addr_t parseAddress(const std::string& addr);
    std::vector<std::shared_ptr<AlsaSequencerOutputPort>> output_ports;

public:
    AlsaSequencer(const char* seq, const std::string& input, int channel);
    ~AlsaSequencer();

    bool open();
    void processIncoming();
    void addListener(ISequencerListener* l);
    void removeAndDeleteListener(ISequencerListener* l);
    PAlsaSequencerOutputPort createOutputPort(const std::string& name);
};
