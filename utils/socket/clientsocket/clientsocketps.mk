
clientsocketps.dll: dlldata.obj clientsocket_p.obj clientsocket_i.obj
	link /dll /out:clientsocketps.dll /def:clientsocketps.def /entry:DllMain dlldata.obj clientsocket_p.obj clientsocket_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del clientsocketps.dll
	@del clientsocketps.lib
	@del clientsocketps.exp
	@del dlldata.obj
	@del clientsocket_p.obj
	@del clientsocket_i.obj
