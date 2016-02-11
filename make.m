% make.m
% Attempt to build DAC4_d2xxInterface for current platform.

switch computer
    case 'PCWIN64'
        mex -L".\d2xxWin\amd64" -I".\d2xxWin" -I".\dac4" -lFTD2XX DAC4_d2xxInterface.c .\dac4\DAC4Protocol.c .\dac4\FT245R.c .\dac4\TT2DAC4.c
    case 'PCWIN'
        mex -L".\d2xxWin\i386" -I".\d2xxWin" -I".\dac4" -lFTD2XX DAC4_d2xxInterface.c .\dac4\DAC4Protocol.c .\dac4\FT245R.c .\dac4\TT2DAC4.c
    case 'MACI64'
        mex -L"./d2xxMac/bin/10.5-10.7" -I"./d2xxMac/bin" -I"./dac4" -lFTD2XX DAC4_d2xxInterface.c ./dac4/DAC4Protocol.c ./dac4/FT245R.c ./dac4/TT2DAC4.c
    case 'GLNXA64'
        mex CFLAGS='-fPIC -Wall -Wextra -lpthread -ldl -lrt' -L"./d2xxLinux64/build/libftd2xx" -I"./d2xxLinux64/" -lftd2xx -I"./dac4" DAC4_d2xxInterface.c ./dac4/DAC4Protocol.c ./dac4/FT245R.c ./dac4/TT2DAC4.c
    otherwise
        error('Unknown System: %s',computer)
end