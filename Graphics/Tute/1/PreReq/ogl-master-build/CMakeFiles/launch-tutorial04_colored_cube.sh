#!/bin/sh
bindir=$(pwd)
cd /home/zubair/Documents/Acads/Sem4/Graphics/Tute/1/PreReq/ogl-master/tutorial04_colored_cube/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/zubair/Documents/Acads/Sem4/Graphics/Tute/1/PreReq/ogl-master-build/tutorial04_colored_cube 
	else
		"/home/zubair/Documents/Acads/Sem4/Graphics/Tute/1/PreReq/ogl-master-build/tutorial04_colored_cube"  
	fi
else
	"/home/zubair/Documents/Acads/Sem4/Graphics/Tute/1/PreReq/ogl-master-build/tutorial04_colored_cube"  
fi
