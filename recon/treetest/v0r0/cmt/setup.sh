# echo "Setting myND280 v0r0 in /home/physics/phuidn/epp/exercise/recon"

if test "${CMTROOT}" = ""; then
  CMTROOT=/storage/epp2/t2k/software/CMT/v1r20p20081118; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh

tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=myND280 -version=v0r0 -path=/home/physics/phuidn/epp/exercise/recon  -no_cleanup $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

