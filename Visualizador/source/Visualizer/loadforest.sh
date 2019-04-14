#!/bin/bash

makefileDir="$(pwd)"
echo $makefileDir

if [ "$1" = "rebuild" ] || [ "$1" = "build" ] 
then
	ulimit -Sv 2000000
	if [ "$1" = "rebuild" ] 
	then
		echo "$1"
		make clean
	fi
	echo "make"
	if [ "$2" = "release" ]
	then
		make -j4 release
	fi
	if [ "$2" = "debug" ]
	then
		make -j4 debug
	fi

else


	mainDir="$(pwd)"
	# getting the main directory by getting the parent dir twice.
	mainDir="$(dirname "$mainDir")"
	mainDir="$(dirname "$mainDir")"
	executionFile=$mainDir/build/Debug/Visualizer
	
	echo "mainDir" $mainDir
	echo "exec   " $executionFile

	density=5
	seed=1479660410
	critical=0.3
	method=DIRECT

	loadFile=forest_solution_$seed\_de_$critical\_30_$density\_10.txt

	#LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.:$mainDir:/home/liliane/Documentos/Libs/glew-2.1.0/build/cmake/build/install/lib:/home/liliane/Documentos/SVN/Nanotubos/gcgtube2/lib:/home/liliane/Documentos/Libs/glfw-3.2.1/build/install/lib $executionFile m $density $seed 10 $critical $method

	#l 5 1479660410 10 forest_solution_1479660410_de_0.3_30_5_10.txt
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.:"$(pwd)":/home/liliane/Documentos/Libs/glew-2.1.0/build/cmake/build/install/lib:/home/liliane/Documentos/Libs/glfw-3.2.1/build/install/lib:$mainDir/lib $executionFile l $density $seed 10 $loadFile

fi

