type color =
  | Primary
  | Secondary;

module Styles = {
  open Css;
  let button = {
    let buttonTheme = Theme.primaryButtonStyles;
    style([
      padding4(~top=px(10), ~left=px(50), ~right=px(50), ~bottom=px(10)),
      marginRight(px(10)),
      borderRadius(px(25)),
      fontSize(rem(1.1)),
      fontWeight(bold),
      borderColor(transparent),
      fontFamily(Theme.sansSerif),
      ...buttonTheme,
    ]);
  };
};
let component = ReasonReact.statelessComponent("Button");

let make = (~className="", ~disabled=false, ~type_="button", ~color=Primary, children) => {
  ...component,
  render: _self =>
    switch (color) {
    | Primary => <button disabled type_ className={className ++ " " ++ Styles.button}> ...children </button>
    | Secondary => <SecondaryButton disabled type_ className> ...children </SecondaryButton>
    },
};
