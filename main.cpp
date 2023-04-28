#include <tclap/CmdLine.h>
#include "AlsaSequencer.h"
#include "ISLCCConverter.h"
#include "ISLMirror.h"



struct AppConfig {
    std::string inputDev;
    int channel;
    int cc;
};

int setupArgParsing(AppConfig& config, int argc, char** argv)
{
    try {
        TCLAP::CmdLine cmd("Midi Notes to CC messages", ' ', "0.1");
        TCLAP::ValueArg<std::string> inputArg("i","input","Input device",true,"20:0","string");
        TCLAP::ValueArg<int> channelArg("C","channel","Channel to listen to",true,0,"int");
        TCLAP::ValueArg<int> ccArg("c","cc","CC number to convert to",true,33,"int");
        cmd.add(inputArg);
        cmd.add(channelArg);
        cmd.add(ccArg);
        cmd.parse( argc, argv );
    
        config.inputDev = inputArg.getValue();
        config.channel = channelArg.getValue();
        config.cc = ccArg.getValue();
    } catch (TCLAP::ArgException &e) { 
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
        return 1;
    }

    return 0;
}

int main(int argc, char** argv) {
    AppConfig config;

    // We could alternatively configure the app config from a file or from env variables
    if (setupArgParsing(config, argc, argv)) return 1;

    AlsaSequencer seq("default", config.inputDev, config.channel);

    if (!seq.open()) 
    {
        printf("ERROR: Can't open sequencer\n");
        return 1;
    }



    auto p1 = seq.createOutputPort("cc");
    auto p2 = seq.createOutputPort("mirror");

    ISLCCConverter* ccConverter = new ISLCCConverter(config.cc, p1);
    ISLMirror* mirror = new ISLMirror(p2);
    seq.addListener(ccConverter);
    seq.addListener(mirror);

    seq.processIncoming();

    seq.removeAndDeleteListener(ccConverter);
    seq.removeAndDeleteListener(mirror);

}
