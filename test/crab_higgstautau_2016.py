from WMCore.Configuration import Configuration
config = Configuration()
config.section_('General')
config.General.transferOutputs = True
config.General.workArea='July08_Data_80X'
config.section_('JobType')
config.JobType.psetName = '/afs/cern.ch/work/a/adewit/private/CMSSW_8_0_9/src/UserCode/ICHiggsTauTau/test/higgstautau_cfg_80X_Apr16.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['EventTree.root']
#config.JobType.inputFiles = ['Spring16_25nsV3_DATA.db']
config.JobType.pyCfgParams = ['release=80XMINIAOD','isData=1','doHT=0', 'globalTag=80X_dataRun2_Prompt_ICHEP16JEC_v0']
config.section_('Data')
#config.Data.inputDataset = 'DUMMY'
config.Data.unitsPerJob = 30000 
#config.Data.unitsPerJob = 1
config.Data.splitting = 'EventAwareLumiBased'
config.Data.publication = False
config.Data.ignoreLocality= True
config.Data.outLFNDirBase='/store/user/adewit/July08_Data_80X/'
config.section_('User')
config.section_('Site')
config.Site.whitelist = ['T2_UK_London_IC', 'T2_CH_CERN', 'T2_FR_GRIF_LLR', 'T2_UK_SGrid_Bristol', 'T3_US_FNALLPC', 'T2_DE_DESY', 'T2_IT_Bari', 'T2_BE_IIHE', 'T2_US_UCSD', 'T2_US_MIT', 'T2_US_Wisconsin', 'T2_US_Florida', 'T2_IT_Rome','T2_FR_IPHC','T2_UK_London_Brunel']
config.Site.storageSite = 'T2_UK_London_IC'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################

    tasks=list()

    tasks.append(('SingleElectronB-v2','/SingleElectron/Run2016B-PromptReco-v2/MINIAOD'))
    tasks.append(('SingleMuonB-v2','/SingleMuon/Run2016B-PromptReco-v2/MINIAOD'))
    tasks.append(('TauB-v2','/Tau/Run2016B-PromptReco-v2/MINIAOD'))
    tasks.append(('MuonEGB-v2','/MuonEG/Run2016B-PromptReco-v2/MINIAOD'))
    tasks.append(('SingleElectronC-v2','/SingleElectron/Run2016C-PromptReco-v2/MINIAOD'))
    tasks.append(('SingleMuonC-v2','/SingleMuon/Run2016C-PromptReco-v2/MINIAOD'))
    tasks.append(('TauC-v2','/Tau/Run2016C-PromptReco-v2/MINIAOD'))
    tasks.append(('MuonEGC-v2','/MuonEG/Run2016C-PromptReco-v2/MINIAOD'))
    tasks.append(('SingleElectronD','/SingleElectron/Run2016D-PromptReco-v2/MINIAOD'))
    tasks.append(('SingleMuonD','/SingleMuon/Run2016D-PromptReco-v2/MINIAOD'))
    tasks.append(('TauD','/Tau/Run2016D-PromptReco-v2/MINIAOD'))
    tasks.append(('MuonEGD','/MuonEG/Run2016D-PromptReco-v2/MINIAOD'))

    for task in tasks:
        print task[0]
        config.General.requestName = task[0]
        config.Data.inputDataset = task[1]
        submit(config)


