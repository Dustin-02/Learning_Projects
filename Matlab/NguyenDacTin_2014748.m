% Nguyen Dac Tin - 2014748

load handel; 

T = 1/Fs;
t = 0:T:(73112/8192);
L = length(t);
plot(t, y);
title("Signal y in Time Domain")
xlabel("Time (s)")
ylabel("y(t)")
yF = fft(y);
P2 = abs(yF/L);
P1 = P2(1:L/2+1);
f = Fs/L*(0:(L/2));

figure; plot(f, P1, "LineWidth", 3); 
title("Single-Sided Amplitude Spectrum of X(t)");
xlabel("f (Hz)");
ylabel("|P1(f)|");