figure
t = linspace(0, 1, 200);
f1 = 1;
f2 = 0.5;
sin_1 = sin(2*pi*f1*t);
sin_2 = sin(2*pi*f2*t);
sin_sum = sin_1 + sin_2;
subplot(3, 2, 1); stem(t, sin_1, 'b','LineWidth', 0.2);
subplot(3, 2, 6); stem(t, sin_2, 'r','LineWidth', 0.15);
subplot(3, 2, 3); stem(t, sin_sum, 'k', 'LineWidth', 0.25);
%%%
load handel; % the signal is in y and sampling freq in Fs
sound(y,Fs); pause(10); % Play the original sound
alpha = 0.9; D = 4196; % Echo parameters
b = [1,zeros(1,D),alpha]; % Filter parameters
x = filter(b,1,y); % Generate sound plus its echo
sound(x,Fs); % Play sound with echo
%%%
[unit_seq, n] = impseq(50, 1, 100); stem (unit_seq);
%%%
[x, n] = sigope(-3, 2, -5, 5);
subplot(2, 2, 1); stem(n, x);
% Vd
[u1, u2, u3, t1] = vd(-8, 8);
subplot(3, 2, 1); stem(t1, u1);
subplot(3, 2, 2); stem(t1, u2);
subplot(3, 2, 3); stem(t1, u3);
% Cau 2
[x, t2] = bai2(0, 15);
subplot(3, 2, 4); stem(t2, x);
% Cau c
n = [0:50]; x = cos(0.04*pi*n) + 0.2*randn(size(n));
subplot(3, 2, 5); stem(n, x); title('Sequence c')
% Cau d
n = [-10:9]; x = [5, 4, 3, 2, 1];

x = [1 1 2 2];
nx = [-1:2];
h = [1 1 2];
nh = [-1:1];
[y,ny] = conv_m(x,nx,h,nh);
subplot(2,1,1); stem(nx, x);
subplot(2,1,2); stem(ny, y);

a_1 = 0.5;
a_2 = 1;
a_3 = 2;
[u, n] = stepseq(0, -100, 100);
subplot(2,2,1); [x_1, n] = sigmult(a_1.^n, n, u, n); stem(n, x_1);
subplot(2,2,2); [x_2, n] = sigmult(a_2.^n, n, u, n); stem(n, x_2);
subplot(2,2,3); [x_3, n] = sigmult(a_3.^n, n, u, n); stem(n, x_3);
m = 0:5;
subplot(2,2,4); x = m.^2; stem(m, x);

b = [1]; a = [1, -1, 0.9]; n = [-20:100];
h = impz(b, a, n);
subplot(2, 2, 1); stem(n, h); title('cau a');

[x_1, n] = stepseq(0, -20, 100);
s_1 = filter(b, a, x_1);
subplot(2, 2, 2); stem(n, s_1); title('cau b');

[u_n, n] = stepseq(0, -20, 100);
[x_2, n] = sigmult((0.6).^n, n, u_n, n)
subplot(2, 2, 3); stem(n, x_2); title('tich cua ham mu');
s_2 = filter(b, a, x_2)
subplot(2, 2, 4); stem(n, s_2); title(' cau c');


