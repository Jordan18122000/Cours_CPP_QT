; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

; Ce script va installer l'app dans un sous-r�pertoire du genre "Neogy\Hycore_Supervisor_v3"
; donc ce sous-r�pertoire changera � chaque changement de version majeure de l'app.

;Version YNOV
#define MyAppInstallImageFile "ynov"
; Site web de la soci�t�   
#define MyAppPublisher "ynov"
; Nom de la soci�t�  
#define MyAppURL "https://ynov-bordeaux.com/"         

; Nom de l'application (sans le num�ro de version)
#define MyAppName "EMBEDDED_CPP_QT"
; Nom de l'app sans caract�re sp�cial
#define MyAppNameNoSpace "EMBEDDED_CPP_QT"
; Num�ro de version majeur
#define MyAppVmaj "2"
; Num�ro de version mineur
#define MyAppVmin "1"

; Num�ro de version complet. Exemple: "3.1"
#define MyAppVersion MyAppVmaj+"."+MyAppVmin
; Nom d'app affich� pour les raccourcis dans le menu D�marrer, la barre de
; lancement rapide et le Bureau
; Exemple: "Hycore Supervisor v3"
#define MyShortlinkAppName MyAppName+" v"+MyAppVmaj
; Nom de r�pertoires pour l'emplacements d'installation et les emplacements
; des raccourcis.
; Exemple: "Hycore_Supervisor_v3"
#define MyAppSubdirName MyAppNameNoSpace+"_v"+MyAppVmaj
; R�pertoire d'install dans Program files. Exemple: "Neogy\Hycore_Supervisor_v3"
#define MyAppFolderName MyAppPublisher+"\"+MyAppSubdirName
; R�pertoire du menu D�marrer. Exemple: "Neogy\Hycore_Supervisor_v3"
#define MyAppGroupName MyAppPublisher+"\"+MyAppSubdirName
; Nom de l'exe. Exemple: Hycore_Supervisor.exe
#define MyAppExeName MyAppNameNoSpace+".exe"
; Nom du fichier setup (sans l'extension). Exemple: Hycore_Supervisor_v3.1_setup
#define MyOutputBaseFilename MyAppNameNoSpace+"_v"+MyAppVersion+"_setup"
	
; Pour deboguer les constanates utilisateur, cette ligne permet d'enregistrer
; dans un fichier le script g�n�r� par le pr�processeur de Inno Setup.
;#define DebugConstants



[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; L'AppId va donc changer � chaque num�ro de version majeure, la version pr�c�dente sera donc conserv�e
AppId="{#MyAppFolderName}"
AppName="{#MyAppName}"
AppVersion="{#MyAppVersion}"
;inutile si AppVersion est d�fini : AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher="{#MyAppPublisher}"
AppPublisherURL="{#MyAppURL}"
AppSupportURL="{#MyAppURL}"
AppUpdatesURL="{#MyAppURL}"   
; R�pertoire d'install dans Program files
DefaultDirName="{pf}\{#MyAppFolderName}"
; R�pertoire du menu D�marrer
DefaultGroupName="{#MyAppGroupName}"
AllowNoIcons=yes
OutputDir=.     
OutputBaseFilename="{#MyOutputBaseFilename}" 
Compression=lzma
SolidCompression=yes
WizardImageFile={#MyAppInstallImageFile}_install.bmp
WizardSmallImageFile={#MyAppInstallImageFile}.bmp

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
; Copie tous les fichiers et r�pertoires du dossier bin/release dans le r�pertoire d'install
Source: "..\bin\release\*"; Excludes: "*.json, hw_test_var.ini"; DestDir: "{app}\bin"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyShortlinkAppName}"; Filename: "{app}\bin\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyShortlinkAppName}}"; Filename: "{uninstallexe}"
; {userdesktop} & {commondesktop} : The path to the desktop folder.
Name: "{commondesktop}\{#MyShortlinkAppName}"; Filename: "{app}\bin\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyShortlinkAppName}"; Filename: "{app}\bin\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]    
Filename: "{app}\bin\{#MyAppExeName}"; Description: "Launch the {#MyShortlinkAppName} application"; Flags: unchecked nowait postinstall skipifsilent runascurrentuser

