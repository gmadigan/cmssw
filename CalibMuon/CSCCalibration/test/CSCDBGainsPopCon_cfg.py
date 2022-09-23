# The following comments couldn't be translated into the new config version:

# Database output service

import FWCore.ParameterSet.Config as cms

process = cms.Process("ProcessOne")
#PopCon config
process.load("CondCore.CondDB.CondDB_cfi")
process.CondDB.connect = cms.string("sqlite_file:DBGains.db")
#process.CondDB.connect = cms.string("oracle://cms_orcoff_prep/CMS_COND_CSC")
process.CondDB.DBParameters.authenticationPath = '/afs/cern.ch/cms/DB/conddb'

process.MessageLogger = cms.Service("MessageLogger",
    cerr = cms.untracked.PSet(
        enable = cms.untracked.bool(False)
    ),
    cout = cms.untracked.PSet(
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        enable = cms.untracked.bool(True)
    )
)

process.source = cms.Source("EmptyIOVSource",
    lastValue = cms.uint64(1),
    timetype = cms.string('runnumber'),
    #change the firstRun if you want a different IOV
    firstValue = cms.uint64(1),
    interval = cms.uint64(1)
)

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
    process.CondDB,
    logconnect = cms.untracked.string('sqlite_file:gainslog.db'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string('CSCDBGainsRcd'),
        tag = cms.string('CSCDBGains_Testing_Sep_2022')
    ))
)

process.WriteGainsWithPopCon = cms.EDAnalyzer("CSCGainsPopConAnalyzer",
    SinceAppendMode = cms.bool(True),
    record = cms.string('CSCDBGainsRcd'),
    loggingOn = cms.untracked.bool(True),
    Source = cms.PSet(

    )
)

process.p = cms.Path(process.WriteGainsWithPopCon)
#process.CondDB.connect = 'oracle://cms_orcoff_prep/CMS_COND_CSC'



