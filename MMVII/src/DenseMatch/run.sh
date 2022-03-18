## bash on macosx doesnt understand ${mm3dBin: : -9}
###### !/usr/bin/env bash

# using zsh to interpret that command
#!/bin/zsh

######### SET-UP
mm3dBin=$(which MMVII)
#DenseMDir=${mm3dBin::(-9)}"src/DenseMatch/"
DenseMDir=`echo "${mm3dBin: : -9}"`
DenseMDir=$DenseMDir"src/DenseMatch/"
echo $DenseMDir
CodeDir=${DenseMDir}"PSMNet/"

#virtual env psmnet
if [ "$EnvName" == "" ]; then
    EnvName=psmnet_env
fi

# path to your trained model
#MODELPATH=${CodeDir}"models/finetune_PSMnet.tar"
MODELPATH=${MODELPATH}
if [ "$MODELPATH" == "" ]; then
    MODELPATH=${CodeDir}"models/finetune_PSMnet.tar"
fi

if [ ! -e MODELPATH ]; then
    echo model "$MODELPATH" does not exist on disk. Exiting
    exit 1
fi

# disparity scale of the trained model
DISPSCALE=-256.0
########


# enter virtual env
source ${DenseMDir}python_env/${EnvName}/bin/activate

# run image matching
python3 ${CodeDir}Test_img.py --loadmodel ${MODELPATH} "$@"

# de-normalise disparities
mv ${6} ${6}_unnorm.tif
mm3d Nikrup "/ ${6}_unnorm.tif ${DISPSCALE}" ${6}


# quit virtual env
deactivate
