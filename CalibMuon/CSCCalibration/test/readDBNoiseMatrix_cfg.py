# The following comments couldn't be translated into the new config version:

# Configuration file for EventSetupTest_t

import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.PoolDBESSource = cms.ESSource("PoolDBESSource",
    loadAll = cms.bool(True),
    #read from database
    #string connect = "frontier://FrontierDev/CMS_COND_CSC"
    timetype = cms.string('runnumber'),
    toGet = cms.VPSet(cms.PSet(
        record = cms.string('CSCDBNoiseMatrixRcd'),
        tag = cms.string('CSCDBNoiseMatrix_ungangedME11A_v1_hlt')
    )),
    #read from sqlite file
    connect=cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
    DBParameters = cms.PSet(
        authenticationPath = cms.untracked.string('/afs/cern.ch/cms/DB/conddb'),
        authenticationMethod = cms.untracked.uint32(1)
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)
process.source = cms.Source("EmptySource",
    firstRun = cms.untracked.uint32(1)
)

process.prod = cms.EDAnalyzer("CSCNoiseMatrixDBReadAnalyzer")

process.output = cms.OutputModule("AsciiOutputModule")

process.p = cms.Path(process.prod)
process.ep = cms.EndPath(process.output)

