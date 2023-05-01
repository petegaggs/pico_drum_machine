# This script converts a mono 16-bit wav file to a C++ header file
# how to use: python wave_convert.py <wav file name>
import wave
import sys

wavefile_name = sys.argv[1]
print("converting {}".format(wavefile_name))
array_name = wavefile_name.split(".")[0].lower()
out_file_name = array_name + ".h"
print("writing file {}".format(out_file_name))

with wave.open(wavefile_name,'rb') as wavefile:
    assert wavefile.getnchannels() == 1, "must be a mono wav file"
    framerate = wavefile.getframerate()
    print("frame rate: {}".format(framerate))
    assert wavefile.getsampwidth() == 2, "wave file must be 16 bit"
    nframes = wavefile.getnframes()
    print("number of frames: {}".format(nframes))
    aud_data = wavefile.readframes(nframes)
    num_bytes = len(aud_data)
    sample_len = float(nframes) / float(framerate)
    print("sample is {} seconds long".format(sample_len))
    print("aud_data is {} bytes".format(num_bytes))
    out_file = open(out_file_name, "w")
    out_file.write("// header file created by wave_convert.py from {}\n".format(wavefile_name))
    out_file.write("const uint16_t {}_SAMPLES = {};\n".format(array_name.upper(), nframes))
    out_file.write("const uint16_t {}_raw[{}] = ".format(array_name, nframes))
    out_file.write("{\n")
    sample_count = 0
    for i in range(nframes):
        out_file.write("0x{:02x}".format(aud_data[(2 * i) + 1])) # high byte
        out_file.write("{:02x}".format(aud_data[2 * i]))         # low byte
        sample_count += 1
        if sample_count == nframes:
            out_file.write("\n};")
        elif sample_count % 8 == 0:
            out_file.write(",\n")
        else:
            out_file.write(", ")
    out_file.close()

