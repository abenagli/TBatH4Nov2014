if [ -n "${SPACAL}" ] ; then
echo "already set"
else
export THISDIR=`pwd`
export SPACAL=${THISDIR}/
export PATH=${THISDIR}/bin:${PATH}
export LD_LIBRARY_PATH=${THISDIR}/lib:${LD_LIBRARY_PATH}
fi
