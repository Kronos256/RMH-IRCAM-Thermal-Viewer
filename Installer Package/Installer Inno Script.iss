
[Setup]
AppName=IRCAM Thermal Viewer
AppVersion=2.5.1
DefaultDirName={pf}\IRCAM Thermal Viewer
DefaultGroupName=IRCAM Thermal Viewer
OutputDir=C:\Users\Rune_\Desktop\RMH IRCAM Thermal Viewer\Installer Package
OutputBaseFilename=IRCAM Thermal Viewer Installer 3.0.0
Compression=lzma
SolidCompression=yes
PrivilegesRequired=admin  
ArchitecturesInstallIn64BitMode=x64

[Files]
Source:"C:\Users\Rune_\Desktop\RMH IRCAM Thermal Viewer\Compiled Program Files\glew32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source:"C:\Users\Rune_\Desktop\RMH IRCAM Thermal Viewer\Compiled Program Files\glfw3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source:"C:\Users\Rune_\Desktop\RMH IRCAM Thermal Viewer\Compiled Program Files\IRCAMDataLoggingCSVReadExample.m"; DestDir: "{app}"; Flags: ignoreversion
Source:"C:\Users\Rune_\Desktop\RMH IRCAM Thermal Viewer\Compiled Program Files\IRCAMFullFrameTempCSVReadExample.m"; DestDir: "{app}"; Flags: ignoreversion
Source:"C:\Users\Rune_\Desktop\RMH IRCAM Thermal Viewer\Compiled Program Files\IRCAM Thermal Viewer.exe"; DestDir: "{app}"; Flags: ignoreversion
Source:"C:\Users\Rune_\Desktop\RMH IRCAM Thermal Viewer\Compiled Program Files\IRCAMSoftwareManual.pdf"; DestDir: "{app}"; Flags: ignoreversion
Source:"C:\Users\Rune_\Desktop\RMH IRCAM Thermal Viewer\Compiled Program Files\opencv_videoio_ffmpeg490_64.dll"; DestDir: "{app}"; Flags: ignoreversion
Source:"C:\Users\Rune_\Desktop\RMH IRCAM Thermal Viewer\Compiled Program Files\opencv_world490.dll"; DestDir: "{app}"; Flags: ignoreversion

; Add both the 32-bit and 64-bit redistributable installers
Source: "C:\Users\Rune_\Desktop\RMH IRCAM Thermal Viewer\Compiled Program Files\vc_redist.x64.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall
Source: "C:\Users\Rune_\Desktop\RMH IRCAM Thermal Viewer\Compiled Program Files\vc_redist.x86.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall

[Icons]
Name: "{group}\IRCAM Thermal Viewer"; Filename: "{app}\IRCAM Thermal Viewer.exe"
Name: "{userdesktop}\IRCAM Thermal Viewer"; Filename: "{app}\IRCAM Thermal Viewer.exe"; Tasks: desktopicon

[Tasks]
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; Flags: unchecked

[Run]
; Install 64-bit redistributable on 64-bit systems
Filename: "{tmp}\vc_redist.x64.exe"; Parameters: "/install /quiet /norestart"; StatusMsg: "Installing Microsoft Visual C++ Redistributable 64-bit..."; Flags: waituntilterminated; Check: Is64BitInstallMode

; Install 32-bit redistributable on 32-bit systems
Filename: "{tmp}\vc_redist.x86.exe"; Parameters: "/install /quiet /norestart"; StatusMsg: "Installing Microsoft Visual C++ Redistributable 32-bit..."; Flags: waituntilterminated; Check: not Is64BitInstallMode

; Optionally, run your main application after installation
; Filename: "{app}\IRCAM Thermal Viewer.exe"; Description: "Launch IRCAM Thermal Viewer"; Flags: nowait postinstall