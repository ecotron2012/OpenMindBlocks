; OpenMindBlocks.iss — instalador Inno Setup (por-usuario, sin admin)

[Setup]
AppId={{3112F31B-25A0-48B5-B753-BBABC94124C0}}
AppName=OpenMindBlocks
AppVersion=1.0.0
AppPublisher=Cristóbal Carreño
DefaultDirName={userappdata}\Programs\OpenMindBlocks
DefaultGroupName=OpenMindBlocks
DisableDirPage=yes
DisableProgramGroupPage=yes
OutputDir=.
OutputBaseFilename=OpenMindBlocks-Setup
Compression=lzma2
SolidCompression=yes
PrivilegesRequired=lowest
ArchitecturesInstallIn64BitMode=x64compatible
ArchitecturesAllowed=x64compatible
UninstallDisplayIcon={app}\AppIcon.ico
SetupIconFile=AppIcon.ico
WizardStyle=modern

[Languages]
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Tasks]
Name: "desktopicon"; Description: "Crear acceso directo en el escritorio"; GroupDescription: "Accesos directos:"; Flags: unchecked

[Files]
Source: "dist\release\*"; DestDir: "{app}"; Flags: recursesubdirs createallsubdirs ignoreversion

[Icons]
Name: "{group}\OpenMindBlocks"; Filename: "{app}\launcher.exe"; WorkingDir: "{app}"; IconFilename: "{app}\frontend.exe"
Name: "{userdesktop}\OpenMindBlocks"; Filename: "{app}\launcher.exe"; WorkingDir: "{app}"; IconFilename: "{app}\frontend.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\launcher.exe"; Description: "Ejecutar OpenMindBlocks ahora"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: filesandordirs; Name: "{app}\logs"

[Code]
var
  ResultCode: Integer;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
begin
  if CurUninstallStep = usUninstall then
  begin
    { Intenta cerrar backend.exe si quedó ejecutándose }
    Exec(ExpandConstant('{cmd}'), '/C taskkill /IM backend.exe /F', '', SW_HIDE, ewWaitUntilTerminated, ResultCode);
  end;
end;
