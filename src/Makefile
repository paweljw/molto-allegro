C++ := g++
ALLEGRO := -lallegro -lallegro_primitives -lallegro_ttf -lallegro_font

all:
	$(C++) -Wall -c molto-allegro.cpp
	ar -cvq libmoltoallegro.a molto-allegro.o
	cp libmoltoallegro.a ../bin/

	$(C++) -Wall -c allegro5_renderer.cpp -o ma_render_a5.o
	ar -cvq libma_render_a5.a ma_render_a5.o
	cp libma_render_a5.a ../bin/

clean: dirclean
	rm -f ../bin/*.a

dirclean:
	rm -f *.o
	rm -f *.a
