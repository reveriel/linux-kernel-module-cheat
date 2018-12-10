SUBDIRS := interactive arch/$(ARCH)/

OUTS := test_one.out ksmtrace.out

$(OUT_DIR)/ksmtrace.out: ksm-test/ksmtrace.c
	$(CC) $(CFLAGS) -o $@ $< -I./ksm-test

$(OUT_DIR)/test_one.out: ksm-test/test_one.c ksm-test/bk.c
	$(CC) $(CFLAGS) -o $@ ksm-test/test_one.c ksm-test/bk.c  -I./ksm-test
