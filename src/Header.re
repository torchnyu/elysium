module Styles = {
  open Css;
  let header =
    style([
      position(fixed),
      display(`flex),
      top(px(0)),
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
    <Link href="/" className=Styles.header> <h1> {ReasonReact.string("Elysium")} </h1> </Link>;
  },
};
