%% Example On How To Read The IRCAM Full Frame Temperature Data CSV File Using MATLAB

% Clear Command Window & Plots
clc, clf

% Read the Full Frame Temperature CSV Data File From IRCAM
CSVTempFrameData = readtable('C:\Users\Rune_\Desktop\FrameTempData_13565268609092024.txt');

% Allocate the Temperatur data
TemperatureData = CSVTempFrameData.Variables;

% Apply ColorMap For Diaplayed Data
colormap turbo;

% ----------------- Display Data As Normal Image ----------------- %

% First Subplot (Top Left)
subplot(2, 2, 1); % 2 Rows, 2 Columns, 1st Subplot
MaxDataRange = max(max(TemperatureData));
MinDataRange = min(min(TemperatureData));
imagesc(TemperatureData, [MinDataRange, MaxDataRange]);
title('Temperature Data As Image (Auto Range):');
c = colorbar;
c.TickLabels = arrayfun(@(x) sprintf('%.1f °C', x), c.Ticks, 'UniformOutput', false);

% ------ Display Data As Normal Image (Temp Range Adjusted) ------ %

% Second Subplot (Top Right)
subplot(2, 2, 2); % 2 Rows, 2 Columns, 2nd Subplot
MaxDataRange = 85; % In Celsius
MinDataRange = min(min(TemperatureData));
imagesc(TemperatureData, [MinDataRange, MaxDataRange]);
title(['Temperature Data As Image (Manual Range): Max: ' num2str(MaxDataRange) '°C']);
c = colorbar;
c.TickLabels = arrayfun(@(x) sprintf('%.1f °C', x), c.Ticks, 'UniformOutput', false);

% ---------------- Display Data As 3D Surface Plot --------------- %

% Third Subplot (Bottom left)
subplot(2, 2, 3); % 2 Rows, 2 Columns, 3rd Subplot
surf(TemperatureData,'LineStyle','none');
xlabel('Width');
ylabel('Height');
zlabel('Temperature [°C]');
title('3D Surface Plot:');
c = colorbar;
c.TickLabels = arrayfun(@(x) sprintf('%.1f °C', x), c.Ticks, 'UniformOutput', false);

% -------------------- Display Data Histogram -------------------- %

% Fourth Subplot (Bottom Right)
subplot(2, 2, 4); % 2 Rows, 2 Columns, 4th Subplot
histogram(TemperatureData, 64);
xlabel('Temperature [°C]');
ylabel('Accumulation [Samples]');
title('Temperature Data Distribution Histogram:');
grid on, grid minor

% ---------------------------------------------------------------- %