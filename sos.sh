#!/bin/bash	
InPath='./output/08_MOD09A1_EVI8D_Texas_sub'; # 输入路径/ input path	
OuPath='./output/09_MOD09EVI_SOS_Texas';	# 输出路径 output path
	
	
#rm -rf   $OuPath/	
mkdir -p $OuPath/	

	
for InName in $(ls $InPath/*tif); do	
  InFile=$(echo $InName | awk -F/ '{print $NF}');	
  OuFile=$(echo $InFile | sed 's/Sin/WGS/g') ;	
  OuName=$OuPath/$OuFile'_EOS.tif';	
  	
 			
  echo $InName #  print InName	
  ./open_MP_SOS $InName $OuName  #run program  (must install C++ and gdal)	
	
	
done	
wait	
