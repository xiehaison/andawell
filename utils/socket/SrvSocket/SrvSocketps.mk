
SrvSocketps.dll: dlldata.obj SrvSocket_p.obj SrvSocket_i.obj
	link /dll /out:SrvSocketps.dll /def:SrvSocketps.def /entry:DllMain dlldata.obj SrvSocket_p.obj SrvSocket_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del SrvSocketps.dll
	@del SrvSocketps.lib
	@del SrvSocketps.exp
	@del dlldata.obj
	@del SrvSocket_p.obj
	@del SrvSocket_i.obj
