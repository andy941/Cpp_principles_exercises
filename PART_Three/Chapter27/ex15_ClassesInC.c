
#include <stdio.h>

struct Shape;

struct vtable {
  void (*draw)(struct Shape *);
};

struct Shape {
  struct vtable vtbl;
  char *name;
};

void draw_shape(struct Shape *);
// struct vtable shape_vtbl = {&draw_shape};

void init_shape(struct Shape *shape) {
  shape->vtbl.draw = &draw_shape;
  shape->name = "Shape";
}

void draw_shape(struct Shape *s) {
  printf("draw called for %s\n", s->name);
} // virtual

void draw(struct Shape *s) { (s->vtbl.draw)(s); } // virtual function call

void rotate(struct Shape *s) {
  printf("rotate called for %s\n", s->name);
} // not virtual

// Square derivation ------------------------------------------
struct Square;

struct Square {
  struct Shape shape;
  char *derived_name;
};

void draw_override(struct Shape *);

void init_square(struct Square *square) {
  init_shape((struct Shape *)square);
  square->shape.vtbl.draw = &draw_override;
  square->derived_name = "Square";
}

void draw_override(struct Shape *s) {
  struct Square *sq = (struct Square *)s;
  printf("draw called for %s\n", sq->derived_name);
} // virtual

int main() {
  struct Shape shape;
  struct Square square;
  init_shape(&shape);
  init_square(&square);
  printf("%s\n", shape.name);
  draw(&shape);
  draw(&square);
  rotate(&shape);  // not virtual
  rotate(&square); // works anyway with risky type punning
}
