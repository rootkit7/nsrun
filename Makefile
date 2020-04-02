
nsrun: nsrun.c
	gcc -o nsrun nsrun.c

clean: nsrun
	rm nsrun

install: nsrun
	@echo "INFO:Group nsrun needs to exist:"
	@echo "\tsudo groupadd -r nsrun\n"
	install -g nsrun -o root -m 4754 nsrun /usr/local/bin/nsrun
