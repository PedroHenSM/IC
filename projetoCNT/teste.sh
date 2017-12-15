#!/bin/bash
criticals=(0.1 0.3 0.5 1 2)
#seeds=(1 1479667867 1479677816)
seeds25=(1479657997 1479667867 1479677816 1479687750 1479736734 1480381788 1480386446 1480391005 1480395518 1480400006 1480458958 1480464940  1480470929 1480476938 1480482935 1480488930 1480494933 1480500927 1480506922 1480542709 1480547314 1480551920 1480556530 1480561144 1480565757 1480570378 1480575003 1480579632 1480584250 1) # seeds para a floresta de densidade 25 
totalSeeds=30
totalCriticals=5
#/home/pedro/Área\ de\ Trabalho/Diversos/CNT/projetoCNT/exec "-d" 25 "-s" ${seeds[0]} "-c" 0.5
#/home/pedro/Área\ de\ Trabalho/Diversos/CNT/projetoCNT/exec "-d" 25 "-s" ${seeds[1]} "-c" 0.5
s=0
while(($s<$totalSeeds))
do
	c=0
	while(($c<$totalCriticals))
	do
		/home/pedro/Área\ de\ Trabalho/Diversos/CNT/projetoCNT/exec "-d" 25 "-s" ${seeds25[s]} "-c" ${criticals[c]}
		((c=$c+1))
	done
	((s=$s+1))
done
	
