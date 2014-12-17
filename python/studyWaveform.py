#!/usr/bin/python

import sys
import os
import commands
import datetime
import string
import argparse
from commands import getstatusoutput

if __name__ == '__main__':
    parser = argparse.ArgumentParser (description = 'studyWaveform: study pedestals')
    parser.add_argument ("-cfg", "--cfg" , default = 'cfg/studyWaveform.cfg' , help='list of run')
    parser.add_argument ('-u', '--dirUnpacked' , default = '/afs/cern.ch/user/a/abenagli/eos/cms/store/user/abenagli/TBatH4Nov2014/unpacked', help='directory containing unpacked data')
    parser.add_argument ('-d', '--dirDQM' , default = '/afs/cern.ch/user/a/abenagli/eos/cms/store/user/abenagli/TBatH4Nov2014/DQM', help='directory containing DQM data')
    parser.add_argument ('-l', '--label' , default = 'test', help='suffix of reco output file')
    parser.add_argument ('-n', '--entry' , default = '0', help='max number of entries to process')
    args = parser.parse_args ()
    os.system('./bin/studyWaveform.exe '+args.cfg+' '+args.dirUnpacked+' '+args.dirDQM+' '+args.label+' '+args.entry)
