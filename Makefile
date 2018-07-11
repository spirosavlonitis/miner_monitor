default:
	gcc *.c -o miner_monitor.out

run: default
	./miner_monitor.out

temp:
	gcc *.c -o fork.out
