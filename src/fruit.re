open Reprocessing;
open World;

type t = {
  imageResourceIndex: int,
  position: (float, float),
  velocity: (float, float),
};

let make = () => {
  let px = Random.float(float_of_int(width));
  let position = (px, 1.2);
  let velocity = (
    Random.float(4.) *. (px < float_of_int(width) /. 2. ? 1. : (-1.)),
    18. +. Random.float(5.),
  );
  let imageResourceIndex = Random.int(List.length(Resources.fruitsPaths));

  {imageResourceIndex, position, velocity};
};

let reinitIfOuntOfFrame = ({position: (px, py)} as fruit: t) =>
  switch (px, py) {
  | (x, y)
      when
        x >= 0.
        && y >= 0.
        && x <= float_of_int(World.width)
        && y <= float_of_int(World.height) => fruit
  | _ => make()
  };

let draw = (env, fruitsImages, {position, imageResourceIndex}) =>
  Draw.image(
    List.nth(fruitsImages, imageResourceIndex),
    ~pos=Helpers.(position |> mapCoordonates |> int_of_floats_tuples),
    ~width=60,
    ~height=60,
    env,
  );