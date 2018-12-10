all:
	./build-linux --config-fragment 'data/myconfig'

run:
	./run  --eval-after-init 'insmod /hello.ko'

.PHONY: run
