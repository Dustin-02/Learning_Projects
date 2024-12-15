pi = 3.1416;
Fs = 1200;
T = 1/Fs;
t1 = 0:T:(0.04);
t2 = 0:T:(0.12);
L1 = length(t1); L2 = length(t2);
x1 = 4 * cos(200 * pi * t1) - cos(800 * pi * t1);
x2 = 4 * cos(200 * pi * t2) - cos(800 * pi * t2);

subplot(3,2,1); plot(t1, x1);
title("Signal x1");
xlabel("Time (s)");
ylabel("x1(n)");

subplot(3,2,2); plot(t2, x2);
title("Signal x2");
xlabel("Time (s)");
ylabel("x2(n)");


X1 = fft(x1);
P2_abs1 = abs(X1/L1);
P2_ang1 = angle(X1/L1);
P1_abs1 = P2_abs1(1:L1/2+1);
P1_ang1 = P2_ang1(1:L1/2+1);
f1 = Fs/L1*(0:(L1/2));

X2 = fft(x2);
P2_abs2 = abs(X2/L2);
P2_ang2 = angle(X2/L2);
P1_abs2 = P2_abs2(1:L2/2+1);
P1_ang2 = P2_ang2(1:L2/2+1);
f2 = Fs/L2*(0:(L2/2));

subplot(3,2,3); plot(f1, P1_abs1, 'r'); title('abs of X1 within t1');
title("Single-Sided Amplitude Spectrum of X1(t)");
xlabel("f (Hz)");
ylabel("|P1_1(f)|");

subplot(3,2,4); plot(f1, P1_ang1/(2*pi)*180, 'r'); title('angle of X1 within t1');
title("Single-Sided Angle Spectrum of X1(t)");
xlabel("f (Hz)");
ylabel("Angle (P1_1(f))");

subplot(3,2,5); plot(f2, P1_abs2, 'b'); title('abs of X1 within t2');
title("Single-Sided Amplitude Spectrum of X2(t)");
xlabel("f (Hz)");
ylabel("|P1_2(f)|");

subplot(3,2,6); plot(f2, P1_ang2/(2*pi)*180, 'b'); title('angle of X2 within t2');
title("Single-Sided Angle Spectrum of X2(t)");
xlabel("f (Hz)");
ylabel("|P1_2(f)|");

f = figure;
x1n = x1 + rand();
x2n = x2 + rand();
subplot(3,2,1); plot(t1, x1n);
title("Signal x1 with noise");
xlabel("Time (s)");
ylabel("x1n (n)");

subplot(3,2,2); plot(t2, x2n);
title("Signal x2 with noise");
xlabel("Time (s)");
ylabel("x2n (n)");

X1n = fft(x1n);
P2_abs1n = abs(X1n/L1);
P2_ang1n = angle(X1n/L1);
P1_abs1n = P2_abs1n(1:L1/2+1);
P1_ang1n = P2_ang1n(1:L1/2+1);

X2n = fft(x2n);
P2_abs2n = abs(X2n/L2);
P2_ang2n = angle(X2n/L2);
P1_abs2n = P2_abs2n(1:L2/2+1);
P1_ang2n = P2_ang2n(1:L2/2+1);

subplot(3,2,3); plot(f1, P1_abs1n, 'r'); title('abs of X1 with noise within t1');
subplot(3,2,4); plot(f1, P1_ang1n/(2*pi)*180, 'r'); title('angle of X1 with noise within t1');
subplot(3,2,5); plot(f2, P1_abs2n, 'b'); title('abs of X2 with noise within t2');
subplot(3,2,6); plot(f2, P1_ang2n/(2*pi)*180, 'b'); title('angle of X2 with noise within t2');

