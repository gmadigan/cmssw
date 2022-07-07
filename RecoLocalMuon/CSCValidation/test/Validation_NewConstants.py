import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

#process.load("Configuration/StandardSequences/Geometry_cff")
process.load("Configuration/StandardSequences/GeometryDB_cff")
process.load("Configuration/StandardSequences/MagneticField_cff")
process.load("Configuration/StandardSequences/FrontierConditions_GlobalTag_cff")
process.load("Configuration/StandardSequences/RawToDigi_Data_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")


process.load('Configuration.StandardSequences.EndOfProcess_cff')

#process.GlobalTag.globaltag = 'GR_P_V39::All'
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.GlobalTag.globaltag = '74X_dataRun2_Prompt_v1'

process.load("CondCore.DBCommon.CondDBCommon_cfi")
from CondCore.DBCommon.CondDBSetup_cfi import *
process.cscConditions = cms.ESSource("PoolDBESSource",
                           DBParameters = cms.PSet(messageLevel = cms.untracked.int32(0)),
                           timetype = cms.string('runnumber'),
                           toGet = cms.VPSet(
                                             cms.PSet(record = cms.string('CSCDBGainsRcd'),
                                                      tag = cms.string('CSCDBGains_Oct_2015')),
                                             cms.PSet(record = cms.string('CSCDBNoiseMatrixRcd'),
                                                      tag = cms.string('CSCDBNoiseMatrix_Oct_2015')),
                                             cms.PSet(record = cms.string('CSCDBCrosstalkRcd'),
                                                      tag = cms.string('CSCDBCrosstalk_Oct_2015')),
                                             cms.PSet(record = cms.string('CSCDBPedestalsRcd'),
                                                      tag = cms.string('CSCDBPedestals_Oct_2015'))
                                             ), 
                           connect = cms.string('sqlite_file:NewConstantsTest.db')
                           )
process.es_prefer_cscConditions = cms.ESPrefer("PoolDBESSource","cscConditions")

#process.cscConditions.connect='sqlite_file:NewConstantsTest.db'
#process.cscConditions.toGet = cms.VPSet(
#              cms.PSet(record = cms.string('CSCDBGainsRcd'),
#                       tag = cms.string('CSCDBGains_Oct_2015')),
#              cms.PSet(record = cms.string('CSCDBNoiseMatrixRcd'),
#                       tag = cms.string('CSCDBNoiseMatrix_Oct_2015')),
#              cms.PSet(record = cms.string('CSCDBCrosstalkRcd'),
#                       tag = cms.string('CSCDBCrosstalk_Oct_2015')),
#              cms.PSet(record = cms.string('CSCDBPedestalsRcd'),
#                       tag = cms.string('CSCDBPedestals_Oct_2015'))
#      )
#      
#process.es_prefer_cscConditions = cms.ESPrefer("PoolDBESSource","cscConditions")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.options = cms.untracked.PSet( SkipEvent = cms.untracked.vstring('ProductNotFound') )
#process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring("/store/data/Run2012D/SingleMu/RAW/v1/000/208/307/FE4830E1-C93A-E211-BDBC-00237DDBE0E2.root"))
process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring( "/store/data/Run2015D/SingleMuon/RAW/v1/000/256/675/00000/48FABF11-E95C-E511-83AF-02163E014590.root"))


####   START OF EXPLICIT POSTLS1 CONFIGURATION    #####

process.load("CalibMuon.CSCCalibration.CSCChannelMapper_cfi")
process.load("CalibMuon.CSCCalibration.CSCIndexer_cfi")
process.CSCIndexerESProducer.AlgoName = cms.string("CSCIndexerPostls1")
process.CSCChannelMapperESProducer.AlgoName = cms.string("CSCChannelMapperPostls1")

# ME1/1A is unganged
process.CSCGeometryESModule.useGangedStripsInME1a = False
process.idealForDigiCSCGeometry.useGangedStripsInME1a = False

# Turn off some flags for CSCRecHitD that are turned ON in default config
process.csc2DRecHits.readBadChannels = cms.bool(False)
process.csc2DRecHits.CSCUseGasGainCorrections = cms.bool(False)
# Already defaults OFF...
## process.csc2DRecHits.CSCUseTimingCorrections = cms.bool(False)

####   END OF EXPLICIT POSTLS1 CONFIGURATION    #####



process.MessageLogger = cms.Service("MessageLogger",
    cout = cms.untracked.PSet(
        default = cms.untracked.PSet( limit = cms.untracked.int32(0) ),
        FwkJob = cms.untracked.PSet( limit = cms.untracked.int32(0) )
    ),
    categories = cms.untracked.vstring('FwkJob'),
    destinations = cms.untracked.vstring('cout')
)


process.cscValidation = cms.EDAnalyzer("CSCValidation",
    rootFileName = cms.untracked.string("NEWConstants_validationHists_global.root"),
    isSimulation = cms.untracked.bool(False),
    writeTreeToFile = cms.untracked.bool(True),
    useDigis = cms.untracked.bool(True),
    detailedAnalysis = cms.untracked.bool(False),
    useTriggerFilter = cms.untracked.bool(False),
    useQualityFilter = cms.untracked.bool(False),
    makeStandalonePlots = cms.untracked.bool(False),
    makeTimeMonitorPlots = cms.untracked.bool(True),
    rawDataTag = cms.InputTag("rawDataCollector"),
    alctDigiTag = cms.InputTag("muonCSCDigis","MuonCSCALCTDigi"),
    clctDigiTag = cms.InputTag("muonCSCDigis","MuonCSCCLCTDigi"),
    corrlctDigiTag = cms.InputTag("muonCSCDigis","MuonCSCCorrelatedLCTDigi"),
    stripDigiTag = cms.InputTag("muonCSCDigis","MuonCSCStripDigi"),
    wireDigiTag = cms.InputTag("muonCSCDigis","MuonCSCWireDigi"),
    compDigiTag = cms.InputTag("muonCSCDigis","MuonCSCComparatorDigi"),
    cscRecHitTag = cms.InputTag("csc2DRecHits"),
    cscSegTag = cms.InputTag("cscSegments"),
    saMuonTag = cms.InputTag("standAloneMuons"),
    l1aTag = cms.InputTag("gtDigis"),
    hltTag = cms.InputTag("TriggerResults::HLT"),
    makeHLTPlots = cms.untracked.bool(True),
    simHitTag = cms.InputTag("g4SimHits", "MuonCSCHits")
)

process.load("L1Trigger.CSCTriggerPrimitives.cscTriggerPrimitiveDigis_cfi")
process.cscTriggerPrimitiveDigis.CSCComparatorDigiProducer = "muonCSCDigis:MuonCSCComparatorDigi"
process.cscTriggerPrimitiveDigis.CSCWireDigiProducer = "muonCSCDigis:MuonCSCWireDigi"
process.cscTriggerPrimitiveDigis.tmbParam.mpcBlockMe1a = 0
process.load("L1TriggerConfig.L1CSCTPConfigProducers.L1CSCTriggerPrimitivesConfig_cff")
process.l1csctpconf.alctParamMTCC2.alctNplanesHitPretrig = 3
process.l1csctpconf.alctParamMTCC2.alctNplanesHitAccelPretrig = 3
process.l1csctpconf.clctParam.clctNplanesHitPretrig = 3
process.l1csctpconf.clctParam.clctHitPersist = 4

process.lctreader = cms.EDAnalyzer("CSCTriggerPrimitivesReader",
    debug = cms.untracked.bool(False),
    dataLctsIn = cms.bool(True),
    emulLctsIn = cms.bool(True),
    isMTCCData = cms.bool(False),
    printps = cms.bool(False),
    CSCLCTProducerData = cms.untracked.string("muonCSCDigis"),
    CSCLCTProducerEmul = cms.untracked.string("cscTriggerPrimitiveDigis"),
    CSCSimHitProducer = cms.InputTag("g4SimHits", "MuonCSCHits"),  # Full sim.
    CSCComparatorDigiProducer = cms.InputTag("simMuonCSCDigis","MuonCSCComparatorDigi"),
    CSCWireDigiProducer = cms.InputTag("simMuonCSCDigis","MuonCSCWireDigi")
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('TPEHists.root'),
                                   closeFileFast = cms.untracked.bool(True)
			           )

# Original
#process.p = cms.Path(process.gtDigis * process.muonCSCDigis * process.csc2DRecHits * process.cscSegments * process.cscTriggerPrimitiveDigis * process.lctreader * process.cscValidation)

# From RECO
# process.p = cms.Path(process.cscValidation)
# From RAW
process.p = cms.Path(process.muonCSCDigis * process.csc2DRecHits * process.cscSegments * process.cscValidation)


# Path and EndPath definitions
##process.raw2digi_step = cms.Path(process.RawToDigi)
##process.reconstruction_step = cms.Path(process.reconstruction)
##process.cscvalidation_step = cms.Path(process.cscValidation)
process.endjob_step = cms.EndPath(process.endOfProcess)

# Schedule definition
##process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.cscvalidation_step,process.endjob_step)
process.schedule = cms.Schedule(process.p,process.endjob_step)

