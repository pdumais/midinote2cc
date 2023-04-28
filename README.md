This is a midi note to CC converter.
It takes a midi device as input and creates two midi output devices. 
For example: `./midinote2cc -c 33 -C 0 -i 14:0`
This would create the following client (as seen by `acconect -l`)
client 128: 'MidiNote2CC' 
    0 'input           '
        Connected From: 14:0
    1 'cc              '
    2 'mirror  

The first device, 128:1, will output CC messages with values that match midi notes. For example, a NoteOn message with value 64 will generate a CC message for control #33 with value 64.
The 2nd device "mirror", is just a copy of the received input.