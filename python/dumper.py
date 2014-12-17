#!/usr/bin/python

import sys
import os
import commands
import datetime
import string
import argparse
from commands import getstatusoutput

if __name__ == '__main__':
    parser = argparse.ArgumentParser (description = 'dumper: create reco tree from raw data')
    parser.add_argument ("-cfg", "--cfg" , default = 'cfg/dumper.cfg' , help='list of run')
    parser.add_argument ('-u', '--dirUnpacked' , default = '/afs/cern.ch/user/a/abenagli/eos/cms/store/user/abenagli/TBatH4Nov2014/unpacked', help='directory containing unpacked data')
    parser.add_argument ('-d', '--dirDQM' , default = '/afs/cern.ch/user/a/abenagli/eos/cms/store/user/abenagli/TBatH4Nov2014/DQM', help='directory containing DQM data')
    parser.add_argument ('-l', '--label' , default = 'test', help='suffix of reco output file')
    parser.add_argument ('-n', '--entriesMax' , default = '-1', help='max number of entries to process')
    parser.add_argument ('--saveWaveforms' , default = '0', help='save a few waveforms')
    args = parser.parse_args ()
    os.system('./bin/dumper.exe '+args.cfg+' '+args.dirUnpacked+' '+args.dirDQM+' '+args.label+' '+args.entriesMax+' '+args.saveWaveforms)
