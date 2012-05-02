PROJ = hax
#include $(PROJ)/Makefile

#touch this Makefile to bypass "hax" is up to date
backup: $(PROJ) Makefile
	cp -R $(PROJ) backup/$(PROJ)_$$(date +20\%y\%m\%d_\%H\%M\%S)

