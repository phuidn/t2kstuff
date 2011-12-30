----------> uses
# use oaEvent * 
#   use nd280Policy * 
#   use ROOT * 
#     use EXTERN * 
#     use MYSQL * 
#       use EXTERN * 
#   use testBase * 
#     use nd280Policy * 
# use oaAnalysis * 
#   use oaEvent * 
#   use oaUtility * 
#     use oaEvent * 
#     use magnetCalib * 
#       use oaEvent * 
#       use oaSlowControlDatabase * 
#         use nd280Policy * 
#         use MYSQL * 
#         use ROOT * 
#         use oaEvent * 
#         use oaRawEvent * 
#           use nd280Policy * 
#           use ROOT * 
#           use oaEvent * 
#         use oaRuntimeParameters * 
#           use ROOT * 
#           use oaEvent * 
#       use oaRuntimeParameters * 
#       use oaOfflineDatabase * 
#         use nd280Policy * 
#         use MinosDBI * 
#           use nd280Policy * 
#           use ROOT * 
#           use oaEvent * 
#         use oaEvent * 
#   use oaRecPack * 
#     use RECPACK * 
#       use EXTERN * 
#       use nd280Policy * 
#       use CLHEP * 
#         use EXTERN * 
#       use ROOT * 
#     use oaGeomInfo * 
#       use oaEvent * 
#       use oaUtility * 
#     use magnetCalib * 
#   use oaGeomInfo * 
#   use oaBeamData * 
#     use nd280Policy * 
#     use ROOT * 
#     use oaEvent * 
#     use oaRawEvent * 
#   use oaDataQuality * 
#     use nd280Policy * 
#   use oaCalib * 
#     use fgdRawData * 
#       use oaEvent * 
#       use oaRawEvent * 
#       use oaRuntimeParameters * 
#       use oaOfflineDatabase * 
#       use oaSlowControlDatabase * 
#       use oaUnpack * 
#         use nd280Policy * 
#         use oaRawEvent * 
#         use oaEvent * 
#       use oaChanInfo * 
#         use ROOT * 
#         use oaEvent * 
#         use oaOfflineDatabase * 
#     use tfbApplyCalib * 
#       use oaEvent * 
#       use oaOfflineDatabase * 
#       use oaSlowControlDatabase * 
#       use oaRuntimeParameters * 
#     use oaRuntimeParameters * 
#     use oaSlowControlDatabase * 
#     use oaOfflineDatabase * 
#     use oaChanInfo * 
#     use oaGeomInfo * 
#     use oaApplyAlign * 
#       use oaEvent * 
#       use oaRuntimeParameters * 
#       use oaGeomInfo * 
#       use oaOfflineDatabase * 
#     use oaUnpack * 
#   use oaRecon * 
#     use trackerRecon * 
#       use oaRuntimeParameters * 
#       use oaGeomInfo * 
#       use tpcRecon * 
#         use sbcat * 
#           use CLHEP * 
#           use oaEvent * 
#           use oaGeomInfo * 
#           use oaUtility * 
#         use oaEvent * 
#         use oaUtility * 
#         use oaRecPack * 
#         use oaRuntimeParameters * 
#         use oaCalib * 
#         use magnetCalib * 
#       use fgdRecon * 
#         use tpcRecon * 
#         use oaRuntimeParameters * 
#         use fgdRawData * 
#     use ecalRecon * 
#       use oaEvent * 
#       use oaGeomInfo * 
#       use oaRuntimeParameters * 
#       use oaRecPack * 
#       use oaChanInfo * 
#       use tfbApplyCalib * 
#       use oaUtility * 
#     use p0dRecon * 
#       use oaEvent * 
#       use oaUtility * 
#       use oaGeomInfo * 
#       use oaRuntimeParameters * 
#     use p0decalRecon * 
#       use oaEvent * 
#       use oaUtility * 
#       use oaGeomInfo * 
#       use oaRuntimeParameters * 
#       use oaRecPack * 
#       use oaChanInfo * 
#       use ecalRecon * 
#     use smrdRecon * 
#       use CLHEP * 
#       use RECPACK * 
#       use oaRecPack * 
#       use ROOT * 
#       use smrdCalib * 
#         use oaEvent * 
#         use oaGeomInfo * 
#         use oaChanInfo * 
#         use oaUtility * 
#         use oaRuntimeParameters * 
#       use oaCalib * 
#       use oaEvent * 
#       use oaUtility * 
#       use oaRuntimeParameters * 
#       use oaGeomInfo * 
#       use tpcRecon * 
# use ROOT * 
#
# Selection :
use CMT v1r20p20081118 (/storage/epp2/t2k/software)
use EXTERN v3r5  (/storage/epp2/t2k/software/ND280/v9r7p9)
use CLHEP v2r0p4n05  (/storage/epp2/t2k/software/ND280/v9r7p9)
use MYSQL v5r051an01  (/storage/epp2/t2k/software/ND280/v9r7p9)
use ROOT v5r28p00n01  (/storage/epp2/t2k/software/ND280/v9r7p9)
use nd280Policy v2r35  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaDataQuality v1r5p1  (/storage/epp2/t2k/software/ND280/v9r7p9)
use RECPACK v1r17p1  (/storage/epp2/t2k/software/ND280/v9r7p9)
use testBase v1r13  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaEvent v8r5p1  (/storage/epp2/t2k/software/ND280/v9r7p9)
use MinosDBI v1r1  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaOfflineDatabase v1r5  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaChanInfo v1r9p1  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaRuntimeParameters v0r5  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaRawEvent v3r19  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaUnpack v3r3  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaBeamData v0r11  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaSlowControlDatabase v1r5  (/storage/epp2/t2k/software/ND280/v9r7p9)
use tfbApplyCalib v2r3p3  (/storage/epp2/t2k/software/ND280/v9r7p9)
use fgdRawData v1r21  (/storage/epp2/t2k/software/ND280/v9r7p9)
use magnetCalib v3r7  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaUtility v4r9p5  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaGeomInfo v4r5  (/storage/epp2/t2k/software/ND280/v9r7p9)
use smrdCalib v1r13  (/storage/epp2/t2k/software/ND280/v9r7p9)
use p0dRecon v7r3p9  (/storage/epp2/t2k/software/ND280/v9r7p9)
use sbcat v4r13p1  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaApplyAlign v0r5  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaCalib v2r17p5  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaRecPack v2r25p9  (/storage/epp2/t2k/software/ND280/v9r7p9)
use ecalRecon v8r7p7  (/storage/epp2/t2k/software/ND280/v9r7p9)
use p0decalRecon v0r19  (/storage/epp2/t2k/software/ND280/v9r7p9)
use tpcRecon v5r17p1  (/storage/epp2/t2k/software/ND280/v9r7p9)
use smrdRecon v3r3p3  (/storage/epp2/t2k/software/ND280/v9r7p9)
use fgdRecon v3r5p1  (/storage/epp2/t2k/software/ND280/v9r7p9)
use trackerRecon v0r15p9  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaRecon v3r5p5  (/storage/epp2/t2k/software/ND280/v9r7p9)
use oaAnalysis v4r37p5  (/storage/epp2/t2k/software/ND280/v9r7p9)
----------> tags
CMTv1 (from CMTVERSION)
CMTr20 (from CMTVERSION)
CMTp20081118 (from CMTVERSION)
Linux (from uname) package CMT implies [Unix]
x86_64 (from HOSTTYPE)
amd64_linux26 (from CMTCONFIG)
ND280_config (from PROJECT) excludes [ND280_no_config]
ND280_root (from PROJECT) excludes [ND280_no_root]
ND280_cleanup (from PROJECT) excludes [ND280_no_cleanup]
ND280_prototypes (from PROJECT) excludes [ND280_no_prototypes]
ND280_without_installarea (from PROJECT) excludes [ND280_with_installarea]
ND280_with_version_directory (from PROJECT) excludes [ND280_without_version_directory]
suse113 (from package CMT)
gcc450 (from package CMT)
Unix (from package CMT) excludes [WIN32 Win32]
----------> CMTPATH
# Add path /storage/epp2/t2k/software/ND280/v9r7p9 from initialization
