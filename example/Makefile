ALLEGRO := -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf
LIBCAT := -L../bin/
MA := -lmoltoallegro -lma_render_a5

all:
	g++ main.cpp -o example $(ALLEGRO) $(LIBCAT) $(MA)

clean:
	rm -f *.o
	rm -f example
