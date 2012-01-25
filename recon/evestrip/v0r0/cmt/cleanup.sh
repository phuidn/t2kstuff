if test "${CMTROOT}" = ""; then
  CMTROOT=/storage/epp2/t2k/software/CMT/v1r20p20081118; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=myND280 -version=v0r0 -path=/storage/epp2/phseaj/t2kwork $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

