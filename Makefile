all: orc2zip zip2orc

orc2zip: orc2zip.c
	gcc -o $@ $@.c `pkg-config --libs --cflags gio-2.0` `pkg-config --libs --cflags glib-2.0`

zip2orc: zip2orc.c
	gcc -o $@ $@.c `pkg-config --libs --cflags gio-2.0` `pkg-config --libs --cflags glib-2.0`

