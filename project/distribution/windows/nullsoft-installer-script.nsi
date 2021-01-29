!include x64.nsh
Name "the planets"
    Unicode True 
    ManifestDPIAware true
    OutFile "theplanets.exe"
    SetCompressor lzma
    InstallDir "$PROGRAMFILES64\theplanets"
    ;InstallDirRegKey HKLM "SOFTWARE\theplanets" "installdir"
    LoadLanguageFile "${NSISDIR}\Contrib\Language files\German.nlf" 
    Page directory
    Page instfiles    
 Section
    SetOutPath $INSTDIR
    File /r "..\theplanets"
    WriteRegStr HKLM "SOFTWARE\theplanets" "installdir" "$INSTDIR"      
    

    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\theplanets" "DisplayName" "theplanets"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\theplanets" "UninstallString" '"$INSTDIR\uninstall.exe"'
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\theplanets" "NoModify" 1
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\theplanets" "NoRepair" 1
    WriteUninstaller "$INSTDIR\uninstall.exe"   
SectionEnd   

Section "Desktop Shortcut" SHORTCUT
    SetOutPath $INSTDIR\theplanets
    CreateShortCut "$DESKTOP\theplanets.lnk" "$OUTDIR\dieplaneten.exe" "-fullscreen" "$OUTDIR\theplanets.ico" 0 SW_SHOWMAXIMIZED
SectionEnd
    ;Function .onGUIInit    
    ;   BgImage::SetBg /GRADIENT 0 0x80 0 0x80 0 0
    ;   BgImage::AddImage c:\temp\DGO4\Installationsscreen.bmp 0 0   
    ;   BgImage::Redraw
    ;FunctionEnd

 
 
Section "Start Menu Shortcuts"
  CreateDirectory "$SMPROGRAMS\theplanets"
  CreateShortcut "$SMPROGRAMS\theplanets\Uninstall.lnk" "$INSTDIR\uninstall.exe"
SectionEnd
 
 
Section "Uninstall"
  
    ; Remove registry keys
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\theplanets"
    DeleteRegKey HKLM "SOFTWARE\theplanets"

    ; Remove files and uninstaller  
    Delete $INSTDIR\uninstall.exe

    ; Remove shortcuts, if any
    Delete "$DESKTOP\theplanets.lnk"  
    Delete "$SMPROGRAMS\theplanets\uninstall.lnk"
    RMDir  "$SMPROGRAMS\theplanets"

    ; Remove directories
    RMDir /r $INSTDIR/theplanets
    RMDir /r $INSTDIR 

SectionEnd
