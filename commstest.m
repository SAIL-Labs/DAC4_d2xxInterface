function commstest
    % comms test to wiggle mirror.
    freq=500;
    i=0.25;
    while 1
        i=i*-1;
        DAC4_d2xxInterface([0 0 0])
        delay(1/freq)
    end
end

function delay(seconds)
    % function pause the program
    % seconds = delay time in seconds
    tic;
    while toc < seconds
    end
end

