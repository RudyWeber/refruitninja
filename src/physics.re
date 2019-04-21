let gravity = 0.5;

let apply = fruits =>
  fruits
  |> List.map(({position: (px, py), velocity: (vx, vy)} as fruit: Fruit.t) =>
       {
         ...fruit,
         position: (px +. vx, py +. vy -. gravity),
         velocity: (vx, vy -. gravity),
       }
     );