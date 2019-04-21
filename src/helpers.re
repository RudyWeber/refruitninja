let mapCoordonates = ((px, py)) => (
  float_of_int(World.width) -. px,
  float_of_int(World.height) -. py,
);

let int_of_floats_tuples = ((a, b)) => (int_of_float(a), int_of_float(b));
let float_of_ints_tuples = ((a, b)) => (float_of_int(a), float_of_int(b));