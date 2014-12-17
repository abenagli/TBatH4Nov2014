#!/usr/bin/python

import sys
import os
import commands
import datetime
import string
import argparse
from commands import getstatusoutput

if __name__ == '__main__':
    parser = argparse.ArgumentParser (description = 'studyProfiles: analyze reco trees')
    parser.add_argument ("--inputList" , default = 'cfg/list_studyProfiles.txt' , help='list of run')
    parser.add_argument ('-l', '--label' , default = 'test', help='suffix of reco output file')
    parser.add_argument ('-n', '--entriesMax' , default = '-1', help='max number of entries to process')
    args = parser.parse_args ()
    os.system('./bin/studyProfiles.exe '+args.inputList+' '+args.label+' '+args.entriesMax)
