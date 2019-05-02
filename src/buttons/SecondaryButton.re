type color =
  | Primary
  | Secondary;

module Styles = {
  open Css;
  let buttonBorder =
    style([
      margin(px(10)),
      backgroundImage(Theme.buttonGradient),
      padding(px(4)),
      borderColor(transparent),
      borderRadius(px(25)),
    ]);
  let button =
    style([
      padding4(~top=px(6), ~left=px(46), ~right=px(46), ~bottom=px(6)),
      borderRadius(px(25)),
      fontSize(rem(1.1)),
      fontWeight(bold),
      backgroundColor(white),
      fontFamily(Theme.sansSerif),
    ]);
  let buttonText =
    style([
      color(orange),
      background(Theme.buttonGradient),
      unsafe("-webkit-background-clip", "text"),
      unsafe("background-clip", "text"),
      unsafe("-webkit-text-fill-color", "transparent"),
    ]);
};
let component = ReasonReact.statelessComponent("Button");

let make = (~className="", ~disabled=false, ~type_="button", children) => {
  ...component,
  render: _self =>
    <button disabled type_ className={className ++ " " ++ Styles.buttonBorder}>
      <div className=Styles.button> <div className=Styles.buttonText> ...children </div> </div>
    </button>,
};
