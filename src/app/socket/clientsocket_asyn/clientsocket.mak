# Microsoft Developer Studio Generated NMAKE File, Based on clientsocket.dsp
!IF "$(CFG)" == ""
CFG=clientsocket - Win32 Debug
!MESSAGE No configuration specified. Defaulting to clientsocket - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "clientsocket - Win32 Debug" && "$(CFG)" != "clientsocket - Win32 Unicode Debug" && "$(CFG)" != "clientsocket - Win32 Release MinSize" && "$(CFG)" != "clientsocket - Win32 Release MinDependency" && "$(CFG)" != "clientsocket - Win32 Unicode Release MinSize" && "$(CFG)" != "clientsocket - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "clientsocket.mak" CFG="clientsocket - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "clientsocket - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clientsocket - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clientsocket - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clientsocket - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clientsocket - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clientsocket - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "clientsocket - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\outp\clientsocket.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\clientsocket.obj"
	-@erase "$(INTDIR)\clientsocket.pch"
	-@erase "$(INTDIR)\clientsocket.res"
	-@erase "$(INTDIR)\CltSock.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\clientsocket.exp"
	-@erase "$(OUTDIR)\clientsocket.lib"
	-@erase "$(OUTDIR)\clientsocket.pdb"
	-@erase "..\outp\clientsocket.dll"
	-@erase "..\outp\clientsocket.ilk"
	-@erase ".\clientsocket.h"
	-@erase ".\clientsocket.tlb"
	-@erase ".\clientsocket_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\clientsocket.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\clientsocket.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\clientsocket.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\clientsocket.pdb" /debug /machine:I386 /def:".\clientsocket.def" /out:"../outp/clientsocket.dll" /implib:"$(OUTDIR)\clientsocket.lib" /pdbtype:sept 
DEF_FILE= \
	".\clientsocket.def"
LINK32_OBJS= \
	"$(INTDIR)\clientsocket.obj" \
	"$(INTDIR)\CltSock.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\clientsocket.res"

"..\outp\clientsocket.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=\work\outp\clientsocket.dll
InputPath=\work\outp\clientsocket.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "clientsocket - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\clientsocket.dll" ".\clientsocket.tlb" ".\clientsocket.h" ".\clientsocket_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\clientsocket.obj"
	-@erase "$(INTDIR)\clientsocket.pch"
	-@erase "$(INTDIR)\clientsocket.res"
	-@erase "$(INTDIR)\CltSock.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\clientsocket.dll"
	-@erase "$(OUTDIR)\clientsocket.exp"
	-@erase "$(OUTDIR)\clientsocket.ilk"
	-@erase "$(OUTDIR)\clientsocket.lib"
	-@erase "$(OUTDIR)\clientsocket.pdb"
	-@erase ".\clientsocket.h"
	-@erase ".\clientsocket.tlb"
	-@erase ".\clientsocket_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\clientsocket.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\clientsocket.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\clientsocket.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\clientsocket.pdb" /debug /machine:I386 /def:".\clientsocket.def" /out:"$(OUTDIR)\clientsocket.dll" /implib:"$(OUTDIR)\clientsocket.lib" /pdbtype:sept 
DEF_FILE= \
	".\clientsocket.def"
LINK32_OBJS= \
	"$(INTDIR)\clientsocket.obj" \
	"$(INTDIR)\CltSock.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\clientsocket.res"

"$(OUTDIR)\clientsocket.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\clientsocket.dll
InputPath=.\DebugU\clientsocket.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "clientsocket - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\clientsocket.dll" ".\clientsocket.tlb" ".\clientsocket.h" ".\clientsocket_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\clientsocket.obj"
	-@erase "$(INTDIR)\clientsocket.pch"
	-@erase "$(INTDIR)\clientsocket.res"
	-@erase "$(INTDIR)\CltSock.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\clientsocket.dll"
	-@erase "$(OUTDIR)\clientsocket.exp"
	-@erase "$(OUTDIR)\clientsocket.lib"
	-@erase ".\clientsocket.h"
	-@erase ".\clientsocket.tlb"
	-@erase ".\clientsocket_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\clientsocket.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\clientsocket.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\clientsocket.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\clientsocket.pdb" /machine:I386 /def:".\clientsocket.def" /out:"$(OUTDIR)\clientsocket.dll" /implib:"$(OUTDIR)\clientsocket.lib" 
DEF_FILE= \
	".\clientsocket.def"
LINK32_OBJS= \
	"$(INTDIR)\clientsocket.obj" \
	"$(INTDIR)\CltSock.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\clientsocket.res"

"$(OUTDIR)\clientsocket.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\clientsocket.dll
InputPath=.\ReleaseMinSize\clientsocket.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "clientsocket - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\clientsocket.dll" ".\clientsocket.tlb" ".\clientsocket.h" ".\clientsocket_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\clientsocket.obj"
	-@erase "$(INTDIR)\clientsocket.pch"
	-@erase "$(INTDIR)\clientsocket.res"
	-@erase "$(INTDIR)\CltSock.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\clientsocket.dll"
	-@erase "$(OUTDIR)\clientsocket.exp"
	-@erase "$(OUTDIR)\clientsocket.lib"
	-@erase ".\clientsocket.h"
	-@erase ".\clientsocket.tlb"
	-@erase ".\clientsocket_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\clientsocket.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\clientsocket.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\clientsocket.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\clientsocket.pdb" /machine:I386 /def:".\clientsocket.def" /out:"$(OUTDIR)\clientsocket.dll" /implib:"$(OUTDIR)\clientsocket.lib" 
DEF_FILE= \
	".\clientsocket.def"
LINK32_OBJS= \
	"$(INTDIR)\clientsocket.obj" \
	"$(INTDIR)\CltSock.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\clientsocket.res"

"$(OUTDIR)\clientsocket.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\clientsocket.dll
InputPath=.\ReleaseMinDependency\clientsocket.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "clientsocket - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\clientsocket.dll" ".\clientsocket.tlb" ".\clientsocket.h" ".\clientsocket_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\clientsocket.obj"
	-@erase "$(INTDIR)\clientsocket.pch"
	-@erase "$(INTDIR)\clientsocket.res"
	-@erase "$(INTDIR)\CltSock.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\clientsocket.dll"
	-@erase "$(OUTDIR)\clientsocket.exp"
	-@erase "$(OUTDIR)\clientsocket.lib"
	-@erase ".\clientsocket.h"
	-@erase ".\clientsocket.tlb"
	-@erase ".\clientsocket_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\clientsocket.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\clientsocket.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\clientsocket.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\clientsocket.pdb" /machine:I386 /def:".\clientsocket.def" /out:"$(OUTDIR)\clientsocket.dll" /implib:"$(OUTDIR)\clientsocket.lib" 
DEF_FILE= \
	".\clientsocket.def"
LINK32_OBJS= \
	"$(INTDIR)\clientsocket.obj" \
	"$(INTDIR)\CltSock.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\clientsocket.res"

"$(OUTDIR)\clientsocket.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\clientsocket.dll
InputPath=.\ReleaseUMinSize\clientsocket.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "clientsocket - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\clientsocket.dll" ".\clientsocket.tlb" ".\clientsocket.h" ".\clientsocket_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\clientsocket.obj"
	-@erase "$(INTDIR)\clientsocket.pch"
	-@erase "$(INTDIR)\clientsocket.res"
	-@erase "$(INTDIR)\CltSock.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\clientsocket.dll"
	-@erase "$(OUTDIR)\clientsocket.exp"
	-@erase "$(OUTDIR)\clientsocket.lib"
	-@erase ".\clientsocket.h"
	-@erase ".\clientsocket.tlb"
	-@erase ".\clientsocket_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\clientsocket.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\clientsocket.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\clientsocket.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\clientsocket.pdb" /machine:I386 /def:".\clientsocket.def" /out:"$(OUTDIR)\clientsocket.dll" /implib:"$(OUTDIR)\clientsocket.lib" 
DEF_FILE= \
	".\clientsocket.def"
LINK32_OBJS= \
	"$(INTDIR)\clientsocket.obj" \
	"$(INTDIR)\CltSock.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\clientsocket.res"

"$(OUTDIR)\clientsocket.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\clientsocket.dll
InputPath=.\ReleaseUMinDependency\clientsocket.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("clientsocket.dep")
!INCLUDE "clientsocket.dep"
!ELSE 
!MESSAGE Warning: cannot find "clientsocket.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "clientsocket - Win32 Debug" || "$(CFG)" == "clientsocket - Win32 Unicode Debug" || "$(CFG)" == "clientsocket - Win32 Release MinSize" || "$(CFG)" == "clientsocket - Win32 Release MinDependency" || "$(CFG)" == "clientsocket - Win32 Unicode Release MinSize" || "$(CFG)" == "clientsocket - Win32 Unicode Release MinDependency"
SOURCE=.\clientsocket.cpp

"$(INTDIR)\clientsocket.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\clientsocket.pch" ".\clientsocket.h" ".\clientsocket_i.c"


SOURCE=.\clientsocket.idl
MTL_SWITCHES=/tlb ".\clientsocket.tlb" /h "clientsocket.h" /iid "clientsocket_i.c" /Oicf 

".\clientsocket.tlb"	".\clientsocket.h"	".\clientsocket_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\clientsocket.rc

"$(INTDIR)\clientsocket.res" : $(SOURCE) "$(INTDIR)" ".\clientsocket.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CltSock.cpp

"$(INTDIR)\CltSock.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\clientsocket.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "clientsocket - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\clientsocket.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\clientsocket.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "clientsocket - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\clientsocket.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\clientsocket.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "clientsocket - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\clientsocket.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\clientsocket.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "clientsocket - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\clientsocket.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\clientsocket.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "clientsocket - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\clientsocket.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\clientsocket.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "clientsocket - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\clientsocket.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\clientsocket.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

