#!/bin/sh
bindir=$(pwd)
cd /home/zubair/Documents/Acads/Sem4/Graphics/Tute/1/PreReq/ogl-master/tutorial18_billboards_and_particles/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/zubair/Documents/Acads/Sem4/Graphics/Tute/1/PreReq/ogl-master-build/tutorial18_particles 
	else
		"/home/zubair/Documents/Acads/Sem4/Graphics/Tute/1/PreReq/ogl-master-build/tutorial18_particles"  
	fi
else
	"/home/zubair/Documents/Acads/Sem4/Graphics/Tute/1/PreReq/ogl-master-build/tutorial18_particles"  
fi
