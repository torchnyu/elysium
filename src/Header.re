module Styles = {
  open Css;
  let header =
    style([
      display(`flex),
      flexDirection(column),
      alignItems(flexStart),
      width(vw(100.0)),
      fontFamily("mr-eaves-xl-modern, sans-serif"),
      paddingLeft(vw(10.0)),
    ]);
};

let component = ReasonReact.statelessComponent("App");

let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,

  render: _self => {
    <div className=Styles.header> <h1> {ReasonReact.string("Elysium")} </h1> </div>;
  },
};
