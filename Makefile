#touch this Makefile to bypass folder is up to date
backuplab1x1: lab1x Makefile
	cp -R lab1x backup/lab1x1_$$(date +20\%y\%m\%d_\%H\%M\%S)
backuplab1x6: lab1x6 Makefile
	cp -R lab1x6 backup/lab1x6_$$(date +20\%y\%m\%d_\%H\%M\%S)
