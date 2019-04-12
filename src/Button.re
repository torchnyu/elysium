module Styles = {
  open Css;
  let button =
    style([
      padding(px(10)),
      borderRadius(px(5)),
      fontSize(rem(1.1)),
      fontFamily("Source Sans Pro, sans-serif"),
      `transition("background-color 0.4s, color 0.4s"),
      transitionTimingFunction(easeIn),
      hover([backgroundColor(Theme.lightBlue), color(white)]),
    ]);
};
let component = ReasonReact.statelessComponent("Button");

let make = (~className="", ~disabled=false, ~type_="button", children) => {
  ...component,
  render: _self => <button disabled type_ className={className ++ " " ++ Styles.button}> ...children </button>,
};
