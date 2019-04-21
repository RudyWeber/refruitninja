open Reprocessing;
open World;

let setup = env => {
  Env.size(~width, ~height, env);

  let initialState: Store.state = {
    resources: {
      fruitsImages: [],
    },
    fruits: [],
    mousePressed: false,
  };

  Store.reduceMany(
    initialState,
    [LOAD_RESOURCES(env), ADD_FRUIT, ADD_FRUIT, ADD_FRUIT],
  );
};

let mouseDown = (state, _env) =>
  Store.reduce(state, SET_MOUSE_PRESSED(true));

let mouseUp = (state, _env) =>
  Store.reduce(state, SET_MOUSE_PRESSED(false));

let draw = ({resources: {fruitsImages}, fruits} as state: Store.state, env) => {
  Draw.background(backgroundColor, env);

  fruits |> List.iter(Fruit.draw(env, fruitsImages));

  let newState =
    if (state.mousePressed) {
      Draw.stroke(Utils.color(~r=255, ~g=255, ~b=255, ~a=255), env);
      Draw.strokeWeight(5, env);
      Draw.line(~p1=Env.mouse(env), ~p2=Env.pmouse(env), env);
      Store.reduce(
        state,
        CHECK_COLLISIONS(
          Helpers.int_of_floats_tuples @@
          Helpers.mapCoordonates(
            Helpers.float_of_ints_tuples(Env.pmouse(env)),
          ),
          Helpers.int_of_floats_tuples @@
          Helpers.mapCoordonates(
            Helpers.float_of_ints_tuples(Env.mouse(env)),
          ),
        ),
      );
    } else {
      state;
    };

  Store.reduceMany(newState, [APPLY_PHYSICS, REINIT_OUT_OF_FRAME_FRUITS]);
};

run(~setup, ~draw, ~mouseDown, ~mouseUp, ());