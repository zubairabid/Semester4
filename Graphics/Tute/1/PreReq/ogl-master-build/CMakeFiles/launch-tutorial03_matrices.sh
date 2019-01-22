#!/bin/sh
bindir=$(pwd)
cd /home/zubair/Documents/Acads/Sem4/Graphics/Tute/1/PreReq/ogl-master/tutorial03_matrices/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/zubair/Documents/Acads/Sem4/Graphics/Tute/1/PreReq/ogl-master-build/tutorial03_matrices 
	else
		"/home/zubair/Documents/Acads/Sem4/Graphics/Tute/1/PreReq/ogl-master-build/tutorial03_matrices"  
	fi
else
	"/home/zubair/Documents/Acads/Sem4/Graphics/Tute/1/PreReq/ogl-master-build/tutorial03_matrices"  
fi
