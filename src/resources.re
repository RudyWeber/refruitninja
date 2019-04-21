open Reprocessing;

type t = {fruitsImages: list(imageT)};

let fruitsPaths = [
  "/Users/rudyweber/dev/reasonconf2k19/fruitninja/assets/apple.png",
  "/Users/rudyweber/dev/reasonconf2k19/fruitninja/assets/banana.png",
  "/Users/rudyweber/dev/reasonconf2k19/fruitninja/assets/coconut.png",
  "/Users/rudyweber/dev/reasonconf2k19/fruitninja/assets/orange.png",
  "/Users/rudyweber/dev/reasonconf2k19/fruitninja/assets/pineapple.png",
  "/Users/rudyweber/dev/reasonconf2k19/fruitninja/assets/watermelon.png",
];

let load = env => {
  fruitsImages:
    fruitsPaths |> List.map(path => Draw.loadImage(~filename=path, env)),
};