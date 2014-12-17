. /afs/cern.ch/sw/lcg/external/gcc/4.7/x86_64-slc6/setup.sh

export ROOTSYS=/afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.18/x86_64-slc6-gcc47-opt/root/

if [[ $PATH == *${ROOTSYS}/bin* ]]
then
echo "root PATH already defined"
else
export PATH=${ROOTSYS}/bin:${PATH}
fi

if [[ $LD_LIBRARY_PATH == *${ROOTSYS}/lib* ]]
then
echo "root LD_LIBRARY_PATH already defined"
else
export LD_LIBRARY_PATH=${ROOTSYS}/lib:${LD_LIBRARY_PATH}
fi

alias root='root -l'
