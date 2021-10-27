#include <stdio.h>

#define DRAW void (*draw)(struct Shape *)

struct Shape;

struct vtable {
  DRAW;
};

typedef struct Shape {
  struct vtable vtbl;
  char *name;
} Shape;

void draw_shape(Shape *);
// vtable shape_vtbl = {&draw_shape};

void init_shape(Shape *shape) {
  shape->vtbl.draw = &draw_shape;
  shape->name = "Shape";
}

void draw_shape(Shape *s) {
  printf("draw called for %s\n", s->name);
} // virtual

void draw(Shape *s) { (s->vtbl.draw)(s); } // virtual function call

void rotate(Shape *s) {
  printf("rotate called for %s\n", s->name);
} // not virtual

// Square derivation ------------------------------------------
struct Square;

typedef struct Square {
  Shape shape;
  char *derived_name;
} Square;

void draw_override(Shape *);

void init_square(Square *square) {
  init_shape((Shape *)square);
  square->shape.vtbl.draw = &draw_override;
  square->derived_name = "Square";
}

void draw_override(Shape *s) {
  Square *sq = (Square *)s;
  printf("draw called for %s\n", sq->derived_name);
} // virtual

int main() {
  Shape shape;
  Square square;
  init_shape(&shape);
  init_square(&square);
  printf("%s\n", shape.name);
  draw(&shape);
  draw(&square);
  rotate(&shape);  // not virtual
  rotate(&square); // works anyway with risky type punning
}
