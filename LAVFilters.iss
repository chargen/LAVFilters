; LAV Filters Inno Setup script

; Include version info
#define ISPP_INCLUDED
#include "common\includes\version.h"

[Setup]
AllowCancelDuringInstall  = no
AllowNoIcons              = yes
AllowUNCPath              = no
AppId                     = libde265filters
AppName                   = libde265 Filters
AppPublisher              = struktur AG
AppPublisherURL           = https://github.com/strukturag/LAVFilters
AppVerName                = libde265 Filters {#=LAV_VERSION_MAJOR}.{#=LAV_VERSION_MINOR}.{#=LAV_VERSION_REVISION}
AppVersion                = {#=LAV_VERSION_MAJOR}.{#=LAV_VERSION_MINOR}.{#=LAV_VERSION_REVISION}
VersionInfoVersion        = {#=LAV_VERSION_MAJOR}.{#=LAV_VERSION_MINOR}.{#=LAV_VERSION_REVISION}.0
VersionInfoCompany        = struktur AG
VersionInfoCopyright      = GPLv2
OutputBaseFilename        = libde265-filters-{#=LAV_VERSION_MAJOR}.{#=LAV_VERSION_MINOR}.{#=LAV_VERSION_REVISION}
OutputDir                 = .
Compression               = lzma2/ultra
SolidCompression          = yes
MinVersion                = 0,5.01SP2
PrivilegesRequired        = admin
CreateAppDir              = yes
DefaultDirName            = {pf}\libde265 Filters
DefaultGroupName          = libde265 Filters
DisableStartupPrompt      = yes
Uninstallable             = yes
DisableDirPage            = auto
DisableProgramGroupPage   = auto
UsePreviousTasks          = yes

[Messages]
WelcomeLabel1=[name/ver]
WelcomeLabel2=This will install [name] on your computer.%n%nIt is recommended that you close all other applications before continuing.
WinVersionTooLowError=This software only works on Windows XP SP2 and newer.

[Types]
Name: Normal; Description: Normal; Flags: iscustom

[Components]
Name: lavsplitter32; Description: libde265 Splitter (x86); Types: Normal;
Name: lavsplitter64; Description: libde265 Splitter (x64); Types: Normal; Check: IsWin64;
Name: lavaudio32;    Description: libde265 Audio (x86);    Types: Normal;
Name: lavaudio64;    Description: libde265 Audio (x64);    Types: Normal; Check: IsWin64;
Name: lavvideo32;    Description: libde265 Video (x86);    Types: Normal;
Name: lavvideo64;    Description: libde265 Video (x64);    Types: Normal; Check: IsWin64;

[Tasks]
Name: icons;          Description: "Create Start Menu Shortcuts";
Name: reset_settings; Description: "Reset Settings"; Flags: checkedonce unchecked; Check: SettingsExistCheck()
Name: associate_wmp;  Description: "Associate file extensions with Windows Media Player";

[Files]
Source: bin_Win32\avcodec-lav-55.dll;  DestDir: {app}\x86; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavsplitter32 lavaudio32 lavvideo32
Source: bin_Win32\avfilter-lav-4.dll;  DestDir: {app}\x86; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavvideo32
Source: bin_Win32\avformat-lav-55.dll; DestDir: {app}\x86; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavsplitter32 lavaudio32
Source: bin_Win32\avresample-lav-1.dll;DestDir: {app}\x86; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavaudio32
Source: bin_Win32\avutil-lav-52.dll;   DestDir: {app}\x86; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavsplitter32 lavaudio32 lavvideo32
Source: bin_Win32\swscale-lav-2.dll;   DestDir: {app}\x86; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavvideo32
Source: bin_Win32\libbluray.dll;       DestDir: {app}\x86; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavsplitter32
Source: bin_Win32\LAVAudio.ax;         DestDir: {app}\x86; Flags: regserver ignoreversion restartreplace uninsrestartdelete; Components: lavaudio32
Source: bin_Win32\LAVSplitter.ax;      DestDir: {app}\x86; Flags: regserver ignoreversion restartreplace uninsrestartdelete; Components: lavsplitter32
Source: bin_Win32\LAVVideo.ax;         DestDir: {app}\x86; Flags: regserver ignoreversion restartreplace uninsrestartdelete; Components: lavvideo32
Source: bin_Win32\LAVFilters.Dependencies.manifest; DestDir: {app}\x86; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavsplitter32 lavaudio32 lavvideo32
Source: bin_Win32\IntelQuickSyncDecoder.dll; DestDir: {app}\x86; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavvideo32
Source: bin_Win32\libde265.dll;        DestDir: {app}\x86; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavvideo32

Source: bin_x64\avcodec-lav-55.dll;    DestDir: {app}\x64; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavsplitter64 lavaudio64 lavvideo64
Source: bin_x64\avfilter-lav-4.dll;    DestDir: {app}\x64; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavvideo64
Source: bin_x64\avformat-lav-55.dll;   DestDir: {app}\x64; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavsplitter64 lavaudio64
Source: bin_x64\avresample-lav-1.dll;  DestDir: {app}\x64; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavaudio64
Source: bin_x64\avutil-lav-52.dll;     DestDir: {app}\x64; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavsplitter64 lavaudio64 lavvideo64
Source: bin_x64\swscale-lav-2.dll;     DestDir: {app}\x64; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavvideo64
Source: bin_x64\libbluray.dll;         DestDir: {app}\x64; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavsplitter64
Source: bin_x64\LAVAudio.ax;           DestDir: {app}\x64; Flags: regserver ignoreversion restartreplace uninsrestartdelete; Components: lavaudio64
Source: bin_x64\LAVSplitter.ax;        DestDir: {app}\x64; Flags: regserver ignoreversion restartreplace uninsrestartdelete; Components: lavsplitter64
Source: bin_x64\LAVVideo.ax;           DestDir: {app}\x64; Flags: regserver ignoreversion restartreplace uninsrestartdelete; Components: lavvideo64
Source: bin_x64\LAVFilters.Dependencies.manifest; DestDir: {app}\x64; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavsplitter64 lavaudio64 lavvideo64
Source: bin_x64\IntelQuickSyncDecoder.dll; DestDir: {app}\x64; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavvideo64
Source: bin_x64\libde265.dll;          DestDir: {app}\x64; Flags: ignoreversion restartreplace uninsrestartdelete; Components: lavvideo64

Source: COPYING;                       DestDir: {app};     Flags: ignoreversion restartreplace uninsrestartdelete
Source: README.txt;                    DestDir: {app};     Flags: ignoreversion restartreplace uninsrestartdelete
Source: CHANGELOG.txt;                 DestDir: {app};     Flags: ignoreversion restartreplace uninsrestartdelete

[Icons]
Name: {group}\Splitter Configuration;        Filename: rundll32.exe; Parameters: """{app}\x86\LAVSplitter.ax"",OpenConfiguration"; WorkingDir: {app}\x86; IconFilename: {app}\x86\LAVSplitter.ax; IconIndex: 0; Tasks: icons; Components: lavsplitter32
Name: {group}\Splitter Configuration;        Filename: rundll32.exe; Parameters: """{app}\x64\LAVSplitter.ax"",OpenConfiguration"; WorkingDir: {app}\x64; IconFilename: {app}\x64\LAVSplitter.ax; IconIndex: 0; Tasks: icons; Components: lavsplitter64 AND NOT lavsplitter32
Name: {group}\Audio Configuration;           Filename: rundll32.exe; Parameters: """{app}\x86\LAVAudio.ax"",OpenConfiguration"; WorkingDir: {app}\x86; IconFilename: {app}\x86\LAVAudio.ax; IconIndex: 0; Tasks: icons; Components: lavaudio32
Name: {group}\Audio Configuration;           Filename: rundll32.exe; Parameters: """{app}\x64\LAVAudio.ax"",OpenConfiguration"; WorkingDir: {app}\x64; IconFilename: {app}\x64\LAVAudio.ax; IconIndex: 0; Tasks: icons; Components: lavaudio64 AND NOT lavaudio32
Name: {group}\Video Configuration;           Filename: rundll32.exe; Parameters: """{app}\x86\LAVVideo.ax"",OpenConfiguration"; WorkingDir: {app}\x86; IconFilename: {app}\x86\LAVVideo.ax; IconIndex: 0; Tasks: icons; Components: lavvideo32
Name: {group}\Video Configuration;           Filename: rundll32.exe; Parameters: """{app}\x64\LAVVideo.ax"",OpenConfiguration"; WorkingDir: {app}\x64; IconFilename: {app}\x64\LAVVideo.ax; IconIndex: 0; Tasks: icons; Components: lavvideo64 AND NOT lavvideo32
Name: {group}\Uninstall libde265 Filters;    Filename: {uninstallexe}; Tasks: icons

[Registry]
Root: HKCU; Subkey: Software\libde265;                  Flags: uninsdeletekeyifempty
Root: HKCU; Subkey: Software\libde265\Audio;            Flags: uninsdeletekey; Components: lavaudio32 lavaudio64
Root: HKCU; Subkey: Software\libde265\Splitter;         Flags: uninsdeletekey; Components: lavsplitter32 lavsplitter64
Root: HKCU; Subkey: Software\libde265\Splitter\Formats; Flags: uninsdeletekey; Components: lavsplitter32 lavsplitter64
Root: HKCU; Subkey: Software\libde265\Video;            Flags: uninsdeletekey; Components: lavvideo32 lavvideo64
Root: HKCU; Subkey: Software\libde265\Video\Formats;    Flags: uninsdeletekey; Components: lavvideo32 lavvideo64
Root: HKCU; Subkey: Software\libde265\Video\Output;     Flags: uninsdeletekey; Components: lavvideo32 lavvideo64

[Run]
Description: "Open Splitter Configuration"; Filename: rundll32.exe; Parameters: """{app}\x86\LAVSplitter.ax"",OpenConfiguration"; WorkingDir: {app}\x86; Components: lavsplitter32; Flags: postinstall nowait unchecked
Description: "Open Splitter Configuration"; Filename: rundll32.exe; Parameters: """{app}\x64\LAVSplitter.ax"",OpenConfiguration"; WorkingDir: {app}\x64; Components: lavsplitter64 AND NOT lavsplitter32; Flags: postinstall nowait unchecked
Description: "Open Audio Configuration";    Filename: rundll32.exe; Parameters: """{app}\x86\LAVAudio.ax"",OpenConfiguration"; WorkingDir: {app}\x86; Components: lavaudio32; Flags: postinstall nowait unchecked
Description: "Open Audio Configuration";    Filename: rundll32.exe; Parameters: """{app}\x64\LAVAudio.ax"",OpenConfiguration"; WorkingDir: {app}\x64; Components: lavaudio64 AND NOT lavaudio32; Flags: postinstall nowait unchecked
Description: "Open Video Configuration";    Filename: rundll32.exe; Parameters: """{app}\x86\LAVVideo.ax"",OpenConfiguration"; WorkingDir: {app}\x86; Components: lavvideo32; Flags: postinstall nowait unchecked
Description: "Open Video Configuration";    Filename: rundll32.exe; Parameters: """{app}\x64\LAVVideo.ax"",OpenConfiguration"; WorkingDir: {app}\x64; Components: lavvideo64 AND NOT lavvideo32; Flags: postinstall nowait unchecked

[Code]
type
  Format = record
             id: String;
             name: String;
             default: Boolean;
             subtype: String;
             asyncSource: Boolean;
             protocol: Boolean;
             extensions: Array of String;
             chkbytes: Array of String;
           end;

const
  NumFormatsMinusOne = 20;
  LavGUID = '{B98D13E7-55DB-4385-A33D-09FD1BA26338}';
  StreamGUID = '{E436EB83-524F-11CE-9F53-0020AF0BA770}';
  LavSplitterFormatsReg = 'Software\libde265\Splitter\Formats';

var
  SplitterPage: TInputOptionWizardPage;
  SplitterFormats: Array [0..NumFormatsMinusOne] of Format;

function SettingsExistCheck(): Boolean;
begin
  if RegKeyExists(HKCU, 'Software\libde265') then
    Result := True
  else
    Result := False;
end;

function IsUpdate(): Boolean;
var
  sPrevPath: String;
begin
  sPrevPath := WizardForm.PrevAppDir;
  Result := (sPrevPath <> '');
end;

procedure FR(var f: Format; const id, desc: String; const default: Boolean; const extensions: Array of String);
begin
  f.id         := id;
  f.name       := desc;
  f.default    := default;
  f.extensions := extensions;
  f.subtype    := '';
  f.chkbytes   := [''];
  f.protocol   := False;
end;

procedure FP(var f: Format; const id, desc: String; const default: Boolean; const extensions: Array of String);
begin
  FR(f, id, desc, default, extensions);
  f.protocol := True;
end;

procedure FS(var f: Format; const subtype: String; const chkbytes : Array of String; UseAsync: Boolean);
begin
  f.subtype     := subtype;
  f.chkbytes    := chkbytes;
  f.asyncSource := UseAsync;
end;

procedure InitFormats();
begin
  FR(SplitterFormats[0], 'matroska', 'Matroska/WebM (with H.265/HEVC support)', True, ['mkv','mka', 'mks', 'webm', '']);
  FS(SplitterFormats[0], '{1AC0BEBD-4D2B-45ad-BCEB-F2C41C5E3788}', ['0,4,,1A45DFA3', ''], True);
  FR(SplitterFormats[1], 'avi', 'AVI', False, ['avi','divx', 'vp6', 'amv', '']);
  FS(SplitterFormats[1], '{e436eb88-524f-11ce-9f53-0020af0ba770}', ['0,4,,52494646,8,4,,41564920', '0,4,,52494646,8,4,,41564958', '0,4,,52494646,8,4,,414D5620', ''], True);
  FR(SplitterFormats[2], 'mp4', 'MP4/MOV', False, ['mp4', 'mov', '3gp', '3ga', 'm4v', 'qt', '']);
  FS(SplitterFormats[2], '{08E22ADA-B715-45ed-9D20-7B87750301D4}', ['4,4,,66747970', '4,4,,6d6f6f76', '4,4,,6d646174', '4,4,,736b6970', '4,4,,75647461',
                                                                    '4,12,ffffffff00000000ffffffff,77696465000000006d646174', '4,12,ffffffff00000000ffffffff,776964650000000066726565',
                                                                    '4,12,ffffffff00000000ffffffff,6672656500000000636D6F76', '4,12,ffffffff00000000ffffffff,66726565000000006D766864',
                                                                    '4,14,ffffffff000000000000ffffffff,706E6F7400000000000050494354', ''], True);
  FR(SplitterFormats[3], 'mpegts', 'MPEG-TS', False, ['ts', 'm2ts', 'mts', 'tp', '']);
  FS(SplitterFormats[3], '{e06d8023-db46-11cf-b4d1-00805f6cbbea}', ['0,1,,47,188,1,,47,376,1,,47', '4,1,,47,196,1,,47,388,1,,47', '0,4,,54467263,1660,1,,47', ''], True);
  FR(SplitterFormats[4], 'mpeg', 'MPEG-PS/VOB/EVO', False, ['mpg', 'mpeg', 'vob', 'evo', '']);
  FS(SplitterFormats[4], '{e06d8022-db46-11cf-b4d1-00805f6cbbea}', ['0,5,FFFFFFFFC0,000001BA40', ''], True);
  FR(SplitterFormats[5], 'bluray', 'Blu-ray', False, ['bdmv', 'mpls', '']);
  FS(SplitterFormats[5], '{20884BC2-629F-45EA-B1C5-FA4FFA438250}', ['0,4,,494E4458', '0,4,,4D4F424A', '0,4,,4D504C53', ''], False);
  FR(SplitterFormats[6], 'flv', 'FLV', False, ['flv', '']);
  FS(SplitterFormats[6], '{F2FAC0F1-3852-4670-AAC0-9051D400AC54}', ['0,4,,464C5601', ''], True);
  FR(SplitterFormats[7], 'ogg', 'Ogg/OGM', False, ['ogg', 'ogv', 'ogm', '']);
  FS(SplitterFormats[7], '{D2855FA9-61A7-4db0-B979-71F297C17A04}', ['0,4,,4F676753', ''], True);
  FR(SplitterFormats[8], 'rm', 'RealMedia (rm/rmvb)', False, ['rm', 'rmvb', '']);
  FR(SplitterFormats[9], 'wtv', 'Windows Television (wtv)', False, ['wtv', '']);
  FR(SplitterFormats[10], 'asf', 'WMV / ASF / DVR-MS', False, ['wmv', 'asf', 'dvr-ms', '']);
  FR(SplitterFormats[11], 'mxf', 'MXF (Material Exchange Format)', False, ['mxf', '']);
  FR(SplitterFormats[12], 'bink', 'Bink', False, ['bik', '']);

  FR(SplitterFormats[13], 'avisynth', 'AviSynth scripts', False, ['avs', '']);

  FP(SplitterFormats[14], 'rtsp', 'RTSP Streaming Protocol', False, ['rtsp', '']);
  FP(SplitterFormats[15], 'rtp', 'RTP Streaming Protocol', False, ['rtp', '']);
  FP(SplitterFormats[16], 'mms', 'MMS Streaming Protocol', False, ['mms', 'mmsh', 'mmst', '']);

  FR(SplitterFormats[17], 'dts', 'DTS Audio', False, ['dts', 'dtshd', '']);
  FR(SplitterFormats[18], 'ac3', 'AC3 Audio', False, ['ac3', 'eac3', '']);
  FR(SplitterFormats[19], 'aac', 'AAC Audio', False, ['aac', '']);
  FR(SplitterFormats[20], 'mp3', 'MP3 Audio', False, ['mp3', '']);
  FR(SplitterFormats[21], 'flac', 'FLAC Audio', False, ['flac', '']);
end;

procedure RegisterSourceFormatGUIDs(f: Format);
var
  i: Integer;
  source: String;
begin
  i := 0;
  if Length(f.subtype) > 0 then
    begin
      if f.asyncSource then
        source := '{e436ebb5-524f-11ce-9f53-0020af0ba770}'
      else
        source := LavGUID;
      if IsComponentSelected('lavsplitter32') then
        RegWriteStringValue(HKCR32, 'Media Type\' + StreamGUID + '\' + f.subtype, 'Source Filter', source);
      if IsComponentSelected('lavsplitter64') then
        RegWriteStringValue(HKCR64, 'Media Type\' + StreamGUID + '\' + f.subtype, 'Source Filter', source);
    end;

  while Length(f.chkbytes[i]) > 0 do
    begin
      if IsComponentSelected('lavsplitter32') then
        RegWriteStringValue(HKCR32, 'Media Type\' + StreamGUID + '\' + f.subtype, IntToStr(i), f.chkbytes[i]);
      if IsComponentSelected('lavsplitter64') then
        RegWriteStringValue(HKCR64, 'Media Type\' + StreamGUID + '\' + f.subtype, IntToStr(i), f.chkbytes[i]);

      i := i+1;
    end;
end;

procedure UnregisterSourceFormatGUIDs(f: Format);
var
  source: String;
begin
  if not f.asyncSource then
    begin
      if RegQueryStringValue(HKCR32, 'Media Type\' + StreamGUID + '\' + f.subtype, 'Source Filter', source) then begin
        if CompareText(source, LavGUID) = 0 then
          RegDeleteKeyIncludingSubkeys(HKCR32, 'Media Type\' + StreamGUID + '\' + f.subtype);
      end;
      if IsWin64 then begin
        if RegQueryStringValue(HKCR64, 'Media Type\' + StreamGUID + '\' + f.subtype, 'Source Filter', source) then begin
          if CompareText(source, LavGUID) = 0 then
            RegDeleteKeyIncludingSubkeys(HKCR64, 'Media Type\' + StreamGUID + '\' + f.subtype);
        end;
      end;
    end;
end;

procedure RegisterSourceFormatExtensions(f: Format);
var
  i: Integer;
begin
  i := 0;
  while Length(f.extensions[i]) > 0 do
    begin
      if f.protocol then begin
        RegWriteStringValue(HKCR, f.extensions[i], 'Source Filter', LavGUID);
      end else begin
        if IsComponentSelected('lavsplitter32') then begin
          RegWriteStringValue(HKCR32, 'Media Type\Extensions\.' + f.extensions[i], 'Source Filter', LavGUID);
          RegWriteStringValue(HKCR32, 'Media Type\Extensions\.' + f.extensions[i], 'Media Type', StreamGUID);
          if Length(f.subtype) > 0 then
            RegWriteStringValue(HKCR32, 'Media Type\Extensions\.' + f.extensions[i], 'SubType', f.subtype);
          if IsTaskSelected('associate_wmp') then begin
            RegWriteStringValue(HKCR32, '.' + f.extensions[i], '', 'WMP.PlayMedia');
            RegWriteDWordValue(HKLM32, 'SOFTWARE\Microsoft\Multimedia\WMPlayer\Extensions\.' + f.extensions[i], 'Permissions', 15);
            RegWriteDWordValue(HKLM32, 'SOFTWARE\Microsoft\Multimedia\WMPlayer\Extensions\.' + f.extensions[i], 'Runtime', 7);
          end;
        end;
        if IsComponentSelected('lavsplitter64') then begin
          RegWriteStringValue(HKCR64, 'Media Type\Extensions\.' + f.extensions[i], 'Source Filter', LavGUID);
          RegWriteStringValue(HKCR64, 'Media Type\Extensions\.' + f.extensions[i], 'Media Type', StreamGUID);
          if Length(f.subtype) > 0 then
            RegWriteStringValue(HKCR64, 'Media Type\Extensions\.' + f.extensions[i], 'SubType', f.subtype);
          if IsTaskSelected('associate_wmp') then begin
            RegWriteStringValue(HKCR64, '.' + f.extensions[i], '', 'WMP.PlayMedia');
            RegWriteDWordValue(HKLM64, 'SOFTWARE\Microsoft\Multimedia\WMPlayer\Extensions\.' + f.extensions[i], 'Permissions', 15);
            RegWriteDWordValue(HKLM64, 'SOFTWARE\Microsoft\Multimedia\WMPlayer\Extensions\.' + f.extensions[i], 'Runtime', 7);
          end;
        end;
      end;

      i := i+1;
    end;
end;

procedure UnregisterSourceFormatExtensions(f: Format);
var
  source: String;
  i: Integer;
begin
  i := 0;
  while Length(f.extensions[i]) > 0 do
    begin
      if f.protocol then begin
        if RegQueryStringValue(HKCR, f.extensions[i], 'Source Filter', source) then begin
          if CompareText(source, LavGUID) = 0 then begin
            RegDeleteValue(HKCR, f.extensions[i], 'Source Filter');
            RegDeleteKeyIfEmpty(HKCR, f.extensions[i]);
          end;
        end;
      end else begin
        if RegQueryStringValue(HKCR32, 'Media Type\Extensions\.' + f.extensions[i], 'Source Filter', source) then begin
          if CompareText(source, LavGUID) = 0 then
            RegDeleteKeyIncludingSubkeys(HKCR32, 'Media Type\Extensions\.' + f.extensions[i]);
          RegDeleteKeyIncludingSubkeys(HKCR32, '.' + f.extensions[i]);
          RegDeleteKeyIncludingSubkeys(HKLM32, 'SOFTWARE\Microsoft\Multimedia\WMPlayer\Extensions\.' + f.extensions[i]);
        end;
        if IsWin64 then begin
          if RegQueryStringValue(HKCR64, 'Media Type\Extensions\.' + f.extensions[i], 'Source Filter', source) then begin
            if CompareText(source, LavGUID) = 0 then
              RegDeleteKeyIncludingSubkeys(HKCR64, 'Media Type\Extensions\.' + f.extensions[i]);
            RegDeleteKeyIncludingSubkeys(HKCR64, '.' + f.extensions[i]);
            RegDeleteKeyIncludingSubkeys(HKLM64, 'SOFTWARE\Microsoft\Multimedia\WMPlayer\Extensions\.' + f.extensions[i]);
          end;
        end;
      end;

      i := i+1;
    end;
end;

function GetDefaultFormatSetting(f: Format): Boolean;
var
  value: Cardinal;
begin
  if RegQueryDWordValue(HKCU, LavSplitterFormatsReg, f.id, value) then begin
    Result := value > 0;
  end else begin
    Result := f.default;
  end
end;

procedure ResetSettings();
begin
  RegDeleteKeyIncludingSubkeys(HKCU, 'Software\libde265');
end;

procedure CurStepChanged(CurStep: TSetupStep);
var
  i: Integer;
begin
  if (CurStep = ssPostInstall) then begin
    if IsTaskSelected('reset_settings') then
      ResetSettings();

    if IsComponentSelected('lavsplitter32') or IsComponentSelected('lavsplitter64') then
      begin
        for i := 0 to NumFormatsMinusOne do
          begin
            if SplitterPage.Values[i] then begin
              RegisterSourceFormatGUIDs(SplitterFormats[i]);
              RegisterSourceFormatExtensions(SplitterFormats[i]);
            end else begin
              UnregisterSourceFormatGUIDs(SplitterFormats[i]);
              UnregisterSourceFormatExtensions(SplitterFormats[i]);
            end;
            RegWriteDWordValue(HKCU, LavSplitterFormatsReg, SplitterFormats[i].id, Ord(SplitterPage.Values[i]));
          end;
      end;
  end;
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
var
  i: Integer;
begin
  if (CurUninstallStep = usUninstall) then begin
    for i := 0 to NumFormatsMinusOne do
      begin
        UnregisterSourceFormatGUIDs(SplitterFormats[i]);
        UnregisterSourceFormatExtensions(SplitterFormats[i]);
      end;
  end;
end;

function ShouldSkipPage(PageID: Integer): Boolean;
begin
  Result := False;
  if PageID = SplitterPage.ID then begin
    if not (IsComponentSelected('lavsplitter32') or IsComponentSelected('lavsplitter64')) then
      Result := True;
  end;
end;

function InitializeSetup(): Boolean;
begin
  InitFormats;
  Result := True;
end;

function InitializeUninstall(): Boolean;
begin
  InitFormats;
  Result := True;
end;

procedure InitializeWizard();
var
  i: Integer;
begin
  SplitterPage := CreateInputOptionPage(wpSelectTasks,
    'Splitter Formats',
    'Select which formats libde265 Splitter should be setup to handle',
    'Select for which formats the splitter should be setup to be the Source Filter.'#10'Note: These are only the file formats for the splitter, audio and video codecs are configured separately.',
    False, False);

  for i := 0 to NumFormatsMinusOne do
    begin
      SplitterPage.Add(SplitterFormats[i].name);
      SplitterPage.Values[i] := GetDefaultFormatSetting(SplitterFormats[i]);
    end;

  // Adjust tasks page
  WizardForm.SelectTasksLabel.Hide;
  WizardForm.TasksList.Top    := 0;
  WizardForm.TasksList.Height := PageFromID(wpSelectTasks).SurfaceHeight;
end;
