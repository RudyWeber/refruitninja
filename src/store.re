type position = (int, int);

type action =
  | ADD_FRUIT
  | APPLY_PHYSICS
  | CHECK_COLLISIONS(position, position)
  | LOAD_RESOURCES(Reprocessing.glEnvT)
  | REINIT_OUT_OF_FRAME_FRUITS
  | SET_MOUSE_PRESSED(bool);

type state = {
  resources: Resources.t,
  fruits: list(Fruit.t),
  mousePressed: bool,
};

let reduce = (state, action) =>
  switch (action) {
  | ADD_FRUIT => {...state, fruits: [Fruit.make(), ...state.fruits]}
  | APPLY_PHYSICS => {...state, fruits: Physics.apply(state.fruits)}
  | CHECK_COLLISIONS((px, py), (x, y)) => {
      ...state,
      fruits:
        state.fruits
        |> List.map((fruit: Fruit.t) =>
             if (Reprocessing.Utils.intersectRectRect(
                   ~rect1Pos=fruit.position,
                   ~rect1W=60.,
                   ~rect1H=60.,
                   ~rect2Pos=(
                     float_of_int(px) |> abs_float,
                     float_of_int(py) |> abs_float,
                   ),
                   ~rect2W=5.,
                   ~rect2H=5.,
                 )
                 && abs_float(
                      Reprocessing.Utils.dist(~p1=(px, py), ~p2=(x, y)),
                    )
                 > 2.) {
               Fruit.make();
             } else {
               fruit;
             }
           ),
    }
  | LOAD_RESOURCES(env) => {...state, resources: Resources.load(env)}
  | REINIT_OUT_OF_FRAME_FRUITS => {
      ...state,
      fruits: state.fruits |> List.map(Fruit.reinitIfOuntOfFrame),
    }
  | SET_MOUSE_PRESSED(mousePressed) => {...state, mousePressed}
  };

let reduceMany = (state, actions) =>
  actions |> List.fold_left(reduce, state);