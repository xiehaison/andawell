# Microsoft Developer Studio Generated NMAKE File, Based on SrvSocket.dsp
!IF "$(CFG)" == ""
CFG=SrvSocket - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SrvSocket - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SrvSocket - Win32 Debug" && "$(CFG)" != "SrvSocket - Win32 Unicode Debug" && "$(CFG)" != "SrvSocket - Win32 Release MinSize" && "$(CFG)" != "SrvSocket - Win32 Release MinDependency" && "$(CFG)" != "SrvSocket - Win32 Unicode Release MinSize" && "$(CFG)" != "SrvSocket - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SrvSocket.mak" CFG="SrvSocket - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SrvSocket - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SrvSocket - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SrvSocket - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SrvSocket - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SrvSocket - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SrvSocket - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "SrvSocket - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\outp\SrvSocket.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CommSocket.obj"
	-@erase "$(INTDIR)\LsnSocket.obj"
	-@erase "$(INTDIR)\SrvSocket.obj"
	-@erase "$(INTDIR)\SrvSocket.pch"
	-@erase "$(INTDIR)\SrvSocket.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SrvSocket.exp"
	-@erase "$(OUTDIR)\SrvSocket.lib"
	-@erase "$(OUTDIR)\SrvSocket.pdb"
	-@erase "..\outp\SrvSocket.dll"
	-@erase "..\outp\SrvSocket.ilk"
	-@erase ".\SrvSocket.h"
	-@erase ".\SrvSocket.tlb"
	-@erase ".\SrvSocket_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\SrvSocket.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\SrvSocket.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SrvSocket.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\SrvSocket.pdb" /debug /machine:I386 /def:".\SrvSocket.def" /out:"../outp/SrvSocket.dll" /implib:"$(OUTDIR)\SrvSocket.lib" /pdbtype:sept 
DEF_FILE= \
	".\SrvSocket.def"
LINK32_OBJS= \
	"$(INTDIR)\CommSocket.obj" \
	"$(INTDIR)\LsnSocket.obj" \
	"$(INTDIR)\SrvSocket.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SrvSocket.res"

"..\outp\SrvSocket.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=\work\outp\SrvSocket.dll
InputPath=\work\outp\SrvSocket.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "SrvSocket - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\SrvSocket.dll" ".\SrvSocket.tlb" ".\SrvSocket.h" ".\SrvSocket_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CommSocket.obj"
	-@erase "$(INTDIR)\LsnSocket.obj"
	-@erase "$(INTDIR)\SrvSocket.obj"
	-@erase "$(INTDIR)\SrvSocket.pch"
	-@erase "$(INTDIR)\SrvSocket.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SrvSocket.dll"
	-@erase "$(OUTDIR)\SrvSocket.exp"
	-@erase "$(OUTDIR)\SrvSocket.ilk"
	-@erase "$(OUTDIR)\SrvSocket.lib"
	-@erase "$(OUTDIR)\SrvSocket.pdb"
	-@erase ".\SrvSocket.h"
	-@erase ".\SrvSocket.tlb"
	-@erase ".\SrvSocket_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\SrvSocket.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\SrvSocket.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SrvSocket.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\SrvSocket.pdb" /debug /machine:I386 /def:".\SrvSocket.def" /out:"$(OUTDIR)\SrvSocket.dll" /implib:"$(OUTDIR)\SrvSocket.lib" /pdbtype:sept 
DEF_FILE= \
	".\SrvSocket.def"
LINK32_OBJS= \
	"$(INTDIR)\CommSocket.obj" \
	"$(INTDIR)\LsnSocket.obj" \
	"$(INTDIR)\SrvSocket.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SrvSocket.res"

"$(OUTDIR)\SrvSocket.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\SrvSocket.dll
InputPath=.\DebugU\SrvSocket.dll
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
	

!ELSEIF  "$(CFG)" == "SrvSocket - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\SrvSocket.dll" ".\SrvSocket.tlb" ".\SrvSocket.h" ".\SrvSocket_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CommSocket.obj"
	-@erase "$(INTDIR)\LsnSocket.obj"
	-@erase "$(INTDIR)\SrvSocket.obj"
	-@erase "$(INTDIR)\SrvSocket.pch"
	-@erase "$(INTDIR)\SrvSocket.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SrvSocket.dll"
	-@erase "$(OUTDIR)\SrvSocket.exp"
	-@erase "$(OUTDIR)\SrvSocket.lib"
	-@erase ".\SrvSocket.h"
	-@erase ".\SrvSocket.tlb"
	-@erase ".\SrvSocket_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\SrvSocket.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\SrvSocket.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SrvSocket.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\SrvSocket.pdb" /machine:I386 /def:".\SrvSocket.def" /out:"$(OUTDIR)\SrvSocket.dll" /implib:"$(OUTDIR)\SrvSocket.lib" 
DEF_FILE= \
	".\SrvSocket.def"
LINK32_OBJS= \
	"$(INTDIR)\CommSocket.obj" \
	"$(INTDIR)\LsnSocket.obj" \
	"$(INTDIR)\SrvSocket.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SrvSocket.res"

"$(OUTDIR)\SrvSocket.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\SrvSocket.dll
InputPath=.\ReleaseMinSize\SrvSocket.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "SrvSocket - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\SrvSocket.dll" ".\SrvSocket.tlb" ".\SrvSocket.h" ".\SrvSocket_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CommSocket.obj"
	-@erase "$(INTDIR)\LsnSocket.obj"
	-@erase "$(INTDIR)\SrvSocket.obj"
	-@erase "$(INTDIR)\SrvSocket.pch"
	-@erase "$(INTDIR)\SrvSocket.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SrvSocket.dll"
	-@erase "$(OUTDIR)\SrvSocket.exp"
	-@erase "$(OUTDIR)\SrvSocket.lib"
	-@erase ".\SrvSocket.h"
	-@erase ".\SrvSocket.tlb"
	-@erase ".\SrvSocket_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\SrvSocket.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\SrvSocket.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SrvSocket.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\SrvSocket.pdb" /machine:I386 /def:".\SrvSocket.def" /out:"$(OUTDIR)\SrvSocket.dll" /implib:"$(OUTDIR)\SrvSocket.lib" 
DEF_FILE= \
	".\SrvSocket.def"
LINK32_OBJS= \
	"$(INTDIR)\CommSocket.obj" \
	"$(INTDIR)\LsnSocket.obj" \
	"$(INTDIR)\SrvSocket.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SrvSocket.res"

"$(OUTDIR)\SrvSocket.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\SrvSocket.dll
InputPath=.\ReleaseMinDependency\SrvSocket.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "SrvSocket - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\SrvSocket.dll" ".\SrvSocket.tlb" ".\SrvSocket.h" ".\SrvSocket_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CommSocket.obj"
	-@erase "$(INTDIR)\LsnSocket.obj"
	-@erase "$(INTDIR)\SrvSocket.obj"
	-@erase "$(INTDIR)\SrvSocket.pch"
	-@erase "$(INTDIR)\SrvSocket.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SrvSocket.dll"
	-@erase "$(OUTDIR)\SrvSocket.exp"
	-@erase "$(OUTDIR)\SrvSocket.lib"
	-@erase ".\SrvSocket.h"
	-@erase ".\SrvSocket.tlb"
	-@erase ".\SrvSocket_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\SrvSocket.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\SrvSocket.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SrvSocket.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\SrvSocket.pdb" /machine:I386 /def:".\SrvSocket.def" /out:"$(OUTDIR)\SrvSocket.dll" /implib:"$(OUTDIR)\SrvSocket.lib" 
DEF_FILE= \
	".\SrvSocket.def"
LINK32_OBJS= \
	"$(INTDIR)\CommSocket.obj" \
	"$(INTDIR)\LsnSocket.obj" \
	"$(INTDIR)\SrvSocket.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SrvSocket.res"

"$(OUTDIR)\SrvSocket.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\SrvSocket.dll
InputPath=.\ReleaseUMinSize\SrvSocket.dll
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
	

!ELSEIF  "$(CFG)" == "SrvSocket - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\SrvSocket.dll" ".\SrvSocket.tlb" ".\SrvSocket.h" ".\SrvSocket_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CommSocket.obj"
	-@erase "$(INTDIR)\LsnSocket.obj"
	-@erase "$(INTDIR)\SrvSocket.obj"
	-@erase "$(INTDIR)\SrvSocket.pch"
	-@erase "$(INTDIR)\SrvSocket.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SrvSocket.dll"
	-@erase "$(OUTDIR)\SrvSocket.exp"
	-@erase "$(OUTDIR)\SrvSocket.lib"
	-@erase ".\SrvSocket.h"
	-@erase ".\SrvSocket.tlb"
	-@erase ".\SrvSocket_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\SrvSocket.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\SrvSocket.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SrvSocket.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\SrvSocket.pdb" /machine:I386 /def:".\SrvSocket.def" /out:"$(OUTDIR)\SrvSocket.dll" /implib:"$(OUTDIR)\SrvSocket.lib" 
DEF_FILE= \
	".\SrvSocket.def"
LINK32_OBJS= \
	"$(INTDIR)\CommSocket.obj" \
	"$(INTDIR)\LsnSocket.obj" \
	"$(INTDIR)\SrvSocket.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SrvSocket.res"

"$(OUTDIR)\SrvSocket.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\SrvSocket.dll
InputPath=.\ReleaseUMinDependency\SrvSocket.dll
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
!IF EXISTS("SrvSocket.dep")
!INCLUDE "SrvSocket.dep"
!ELSE 
!MESSAGE Warning: cannot find "SrvSocket.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SrvSocket - Win32 Debug" || "$(CFG)" == "SrvSocket - Win32 Unicode Debug" || "$(CFG)" == "SrvSocket - Win32 Release MinSize" || "$(CFG)" == "SrvSocket - Win32 Release MinDependency" || "$(CFG)" == "SrvSocket - Win32 Unicode Release MinSize" || "$(CFG)" == "SrvSocket - Win32 Unicode Release MinDependency"
SOURCE=.\CommSocket.cpp

"$(INTDIR)\CommSocket.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SrvSocket.pch"


SOURCE=.\LsnSocket.cpp

"$(INTDIR)\LsnSocket.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SrvSocket.pch"


SOURCE=.\SrvSocket.cpp

"$(INTDIR)\SrvSocket.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SrvSocket.pch" ".\SrvSocket.h" ".\SrvSocket_i.c"


SOURCE=.\SrvSocket.idl
MTL_SWITCHES=/tlb ".\SrvSocket.tlb" /h "SrvSocket.h" /iid "SrvSocket_i.c" /Oicf 

".\SrvSocket.tlb"	".\SrvSocket.h"	".\SrvSocket_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\SrvSocket.rc

"$(INTDIR)\SrvSocket.res" : $(SOURCE) "$(INTDIR)" ".\SrvSocket.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SrvSocket - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\SrvSocket.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SrvSocket.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SrvSocket - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\SrvSocket.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SrvSocket.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SrvSocket - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\SrvSocket.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SrvSocket.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SrvSocket - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\SrvSocket.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SrvSocket.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SrvSocket - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\SrvSocket.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SrvSocket.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SrvSocket - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\SrvSocket.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SrvSocket.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

