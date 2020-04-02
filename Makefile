
nsrun: nsrun.c
	gcc -o nsrun nsrun.c


clean: nsrun
	rm nsrun

fixperm: nsrun
	sudo chown root nsrun
	sudo chmod 4755 nsrun
