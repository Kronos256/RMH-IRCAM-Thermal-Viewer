%% Example On How To Read The IRCAM Data Logging CSV File Using MATLAB

% Clear Command Window & Plots
clc, clf

% In the following example the Data in the data logging file is:
% (Temperature Unit: Celsius)

% Sample,Time(ms),Maximum Temp,Minimum Temp,Average Temp
% 1,40,48.89817,38.09403,41.85327
% 2,80,48.89817,38.09403,41.85327
% 3,120,48.89817,38.09403,41.85327
% 4,160,48.89817,38.09403,41.85327
% 5,200,48.88084,38.05575,41.90866
% 6,240,48.88084,38.07489,41.90866
% 7,280,48.86350,38.07489,41.87173
% 8,320,48.88084,38.07489,41.90866
% 9,360,48.88084,38.07489,41.87173
% ................

% -------------------- Data Logging File Path -------------------- %

% Select the Data Logging File With The Name "DataLogSession_XXXXXXXXXXXXXXXXX"

% Path for the Data Logging file
FileLocation = 'C:\Users\Rune_\Desktop\DataLogSession_11545929822082024.txt';

% The Format Of The File Time Stamp Is: hhmmssfffddmmyyyy
% For The Above File Name, The File Was Captured:
% Time: 11:54:59.298, Data: 22-08-2024

% ---------------------------------------------------------------- %

% Read the data from the file, separated by each header description
FileData = readtable(FileLocation);

% Plot Maximum, Minimum And Average Temperature Data
% "/ 1000" -> Conversion To Seconds
plot(FileData.Time_ms_ / 1000, FileData.MaximumTemp, ...
     FileData.Time_ms_ / 1000, FileData.MinimumTemp, ...
     FileData.Time_ms_ / 1000, FileData.AverageTemp);

% Change The Plots X/Y Tick Format
xtickformat('%,.0f');
ytickformat('%,.2f');

% Display Plot Grid
grid on
grid minor

% Add Plot X/Y and Title Labels
xlabel('Time [Sec]', 'FontSize', 14);
ylabel('Temperature [°C]', 'FontSize', 14);
title('IRCAM CSV Data Logging Temperature Plot', 'FontSize', 16);

% Add Plot Legende
legend('Maximum Temperature', 'Minimum Temperature', 'Average Temperature');



