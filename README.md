SPACAL
=======

Code for SPACAL analysis (test beam)

instruction for download and compiling:

	git clone git@github.com:lbrianza/SPACAL.git
	source thisroot.sh
	sh compile.sh

..and start to use it!

------------------------------------------------------
Main codes:

1- dumper: 	
		read the raw data and produce a file with a reco tree. A cfg file should be given in input, with a row for each run:
		1) run number 2) energy 3) xTable position 4) yTable Position 5) Planacon HV

--> usage:      python python/dumper.py
--> example:    python python/dumper.py -cfg cfg/Fibre1.cfg -n Fibre

(for the list of options, look inside the python)	
