# Microsoft Developer Studio Generated NMAKE File, Based on comm.dsp
!IF "$(CFG)" == ""
CFG=comm - Win32 Debug
!MESSAGE No configuration specified. Defaulting to comm - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "comm - Win32 Release" && "$(CFG)" != "comm - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "comm.mak" CFG="comm - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "comm - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "comm - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "comm - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\outp\comm.dll"


CLEAN :
	-@erase "$(INTDIR)\comm.obj"
	-@erase "$(INTDIR)\comm.pch"
	-@erase "$(INTDIR)\comm.res"
	-@erase "$(INTDIR)\Crc32Static.obj"
	-@erase "$(INTDIR)\IniFile.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\comm.exp"
	-@erase "$(OUTDIR)\comm.lib"
	-@erase "..\outp\comm.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp1 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\comm.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\comm.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\comm.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\comm.pdb" /machine:I386 /def:".\comm.def" /out:"..\outp\comm.dll" /implib:"$(OUTDIR)\comm.lib" 
DEF_FILE= \
	".\comm.def"
LINK32_OBJS= \
	"$(INTDIR)\comm.obj" \
	"$(INTDIR)\Crc32Static.obj" \
	"$(INTDIR)\IniFile.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\comm.res"

"..\outp\comm.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "comm - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\outp\comm.dll"


CLEAN :
	-@erase "$(INTDIR)\comm.obj"
	-@erase "$(INTDIR)\comm.pch"
	-@erase "$(INTDIR)\comm.res"
	-@erase "$(INTDIR)\Crc32Static.obj"
	-@erase "$(INTDIR)\IniFile.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\comm.exp"
	-@erase "$(OUTDIR)\comm.lib"
	-@erase "$(OUTDIR)\comm.pdb"
	-@erase "..\..\outp\comm.dll"
	-@erase "..\..\outp\comm.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp1 /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\comm.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\comm.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\comm.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\comm.pdb" /debug /machine:I386 /def:".\comm.def" /out:"c:\work\outp\comm.dll" /implib:"$(OUTDIR)\comm.lib" /pdbtype:sept 
DEF_FILE= \
	".\comm.def"
LINK32_OBJS= \
	"$(INTDIR)\comm.obj" \
	"$(INTDIR)\Crc32Static.obj" \
	"$(INTDIR)\IniFile.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\comm.res"

"..\..\outp\comm.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
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
!IF EXISTS("comm.dep")
!INCLUDE "comm.dep"
!ELSE 
!MESSAGE Warning: cannot find "comm.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "comm - Win32 Release" || "$(CFG)" == "comm - Win32 Debug"
SOURCE=.\comm.cpp

"$(INTDIR)\comm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\comm.pch"


SOURCE=.\comm.rc

"$(INTDIR)\comm.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\utillib\Crc32Static.cpp

"$(INTDIR)\Crc32Static.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\comm.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\IniFile.cpp

"$(INTDIR)\IniFile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\comm.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "comm - Win32 Release"

CPP_SWITCHES=/nologo /Zp1 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\comm.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\comm.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "comm - Win32 Debug"

CPP_SWITCHES=/nologo /Zp1 /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\comm.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\comm.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

