function commstest
    % comms test to wiggle mirror.
    freq=200;
    i=0.1;
    while 1
        i=-0.2*rand(1);
        DAC4_d2xxInterface([i i 0 0])
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

