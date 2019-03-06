module Styles = {
  open Css;
  let project =
    style([
      display(`flex),
      flexDirection(column),
      alignItems(center),
      justifyContent(center),
      minHeight(px(300)),
      minWidth(px(400)),
      marginBottom(px(200)),
      boxShadow(rgba(0, 0, 0, 0.75), ~x=px(7), ~y=px(7), ~blur=px(27), ~spread=px(-2)),
      color(hex("232c33")),
    ]);
};
let component = ReasonReact.statelessComponent("Project");

let make = (_children, ~title) => {
  ...component,
  render: _self => {
    <div className=Styles.project> <h1> {ReasonReact.string(title)} </h1> </div>;
  },
};
