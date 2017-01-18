#
# Makefile
# zhangyule, 2017-01-18 11:31
#

all:
	@echo "Makefile needs your attention"

lint:
	python third_party/cpplint.py ./*

test:
	./test/channel_test
# vim:ft=make
#
